def main():
     x = uInput("Enter the number representing the length/width/depth of the cube. Positive integer value only: ")
     answer = calculateVol(x)
     print("Volume of the Cube: ",answer)

def uInput(x):
    while True:
        try:
            z = int(input(x))
            if(z < 1):
                raise ValueError
            break
        except ValueError:
            print("Invalid input!")
    return z

def calculateVol(x):
    return x**3

if __name__ == '__main__':
    main()