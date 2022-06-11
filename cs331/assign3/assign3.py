#Names: Jackson Rollins & Nat Bourassa
#Date: 5/29/2022

import sys
import re
from math import log

def buildVocab(vocabList):
    fp = open('trainingSet.txt')
    lines = fp.readlines()
    fp.close()

    for line in lines:
        line = line.strip()
        line = re.sub(r'[^\w\s]', '', line)
        line = line.lower()
        line = line[:-1]
        tmpList = line.split()
        for element in tmpList:
            if element not in vocabList and not element.isnumeric():
                vocabList.append(element)
            else:
                pass
    vocabList.sort()

def featureList(file, vocabList):
    fp = open(file, 'r')
    lines = fp.readlines()
    fp.close()

    data = []
    for line in lines:
        line = line.strip()
        line = re.sub(r'[^\w\s]', '', line)
        classLabel = line[-1]
        line = line[:-1]
        tmpList = line.split()

        list = []
        for element in vocabList:
            if element in tmpList:
                list.append(1)
            else:
                list.append(0)
        list.append(int(classLabel))
        data.append(list)
    
    return data

def preProcessedOutput(trainingData, testData, vocabList):
    trainFP = open('preprocessed_train.txt', 'w')
    testFP = open('preprocessed_test.txt', 'w')

    for element in vocabList:
        trainFP.write(element + ', ')
        testFP.write(element + ', ')
    trainFP.write('classlabel\n')
    testFP.write('classlabel\n')

    for i in range(len(trainingData)):
        for j in range(len(trainingData[i])):
            if j != len(trainingData[i]) - 1:
                trainFP.write(str(trainingData[i][j]) + ', ')
            else:
                trainFP.write(str(trainingData[i][j]))
        trainFP.write('\n')
    
    for i in range(len(testData)):
        for j in range(len(testData[i])):
            if j != len(testData[i]) - 1:
                testFP.write(str(testData[i][j]) + ', ')
            else:
                testFP.write(str(testData[i][j]))
        testFP.write('\n')
    
    trainFP.close()
    testFP.close()

def get_prob(class_num, test_num,train_data,test_data):
    class_same = 0
    inter_sum =0
    total = 1
    for j in range(len(test_data[test_num])-1):
        for i in range(len(train_data)):
            if j == 0 and class_num == train_data[i][-1]:
                class_same+=1
            if train_data[i][j] == test_data[test_num][j] and class_num == train_data[i][-1]:
                inter_sum +=1
        total *= inter_sum
        inter_sum = 0
    total *= class_same
    return total
        

def get_result(data, train):
    correct = 0
    prediction = -1
    for i in range(len(data)):
        trueth = get_prob(1,i,train,data)
        falseth = get_prob(0,i,train,data)
        if trueth>falseth:
            prediction = 1
        else: 
            prediction = 0
        if data[i][-1] == prediction:
            correct +=1
    accuracy = correct / len(data)
    return accuracy

def progThree():
    outFP = open('results.txt', 'w')
    vocabList = []
    buildVocab(vocabList)

    trainingData = featureList(training_file, vocabList)
    testData = featureList(test_file, vocabList)
    preProcessedOutput(trainingData, testData, vocabList)

    accuracy1 = get_result(trainingData, trainingData)
    accuracy2 = get_result(testData, trainingData)

    outFP.write("Training filename: " + training_file + "\nTest filename: " + training_file + "\n\tAccuracy: %" + str(accuracy1*100) + "\n")
    outFP.write("Training filename: " + training_file + "\nTest filename: " + test_file + "\n\tAccuracy: %" + str(accuracy2*100) + "\n")

    outFP.close()

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Invalid amount of arguments!")
    else:
        training_file = sys.argv[1]
        test_file = sys.argv[2]
        progThree()