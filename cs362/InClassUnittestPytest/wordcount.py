def main():
    sentence = input("Enter a sentence of any length: ")
    wordCount = countWords(sentence);
    print("Number of words in sentence: ", wordCount)

def countWords(sentence):
    counter = 1
    for i in range(len(sentence)):
        if(sentence[i] == ' ' or sentence =='\n' or sentence == '\t'):
            counter+=1
    return counter

if __name__ == '__main__':
    main()