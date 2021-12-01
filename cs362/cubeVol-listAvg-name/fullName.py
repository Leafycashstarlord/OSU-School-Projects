def main():
    fName = uInput("What is your first name: ")
    lName = uInput("What is your last name: ")
    fullName = makeName(fName, lName)
    print("Full Name: ", fullName)

def uInput(x):
    return input(x)

def makeName(x, y):
    return x + " " + y

if __name__ == '__main__':
    main()