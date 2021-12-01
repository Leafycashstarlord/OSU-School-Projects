def main():
    list_length = uInput("How big do you want the list? Positive integer value only: ", 1)
    my_list = []
    for i in range(0, list_length):
        my_list.insert(i, uInput("Enter a number to add to the list. Integer value only: ", 0))
    answer = calculateAvg(my_list)
    print("Average of the list: ", answer)

def uInput(x, y):
    if(y == 0):
        while True:
            try:
                z = int(input(x))
                break
            except ValueError:
                print("Invalid input!")
    elif(y == 1):
        while True:
            try:
                z = int(input(x))
                if(z < 1):
                    raise ValueError
                break
            except ValueError:
                print("Invalid input!")
    return z

def calculateAvg(x):
    listAvg = sum(x)/len(x)
    return listAvg

if __name__ == '__main__':
    main()