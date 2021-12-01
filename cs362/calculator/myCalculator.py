def main():
    x = uInput("Please enter your first number. Integer values only: ", 0)
    y = uInput("Please enter your second number. Integer values only: ", 0)
    print("What do you want to do with your numbers?")
    print("1. Add")
    print("2. Subtract")
    print("3. Multiply")
    print("4. Divide")
    z = uInput("Make your choice: ", 1)
    answer = calculate(x, y, z)
    print("Answer: ", answer)

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
                if((z < 1) or (z > 4)):
                    raise ValueError
                break
            except ValueError:
                print("Invalid input!")
    return z

def calculate(x, y, z):
    if(z == 1):
        return x + y
    elif(z == 2):
        return x - y
    elif(z == 3):
        return x * y
    elif(z == 4):
        return x / y

if __name__ == '__main__':
    main()