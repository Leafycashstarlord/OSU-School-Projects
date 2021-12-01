def main():
    word = input("Enter a string, any string: ")
    result = calcPalindrome(word)
    if(result == True):
        print("Given string is a palindrome!")
    else:
        print ("Given string is not a palindrome.")

def calcPalindrome(word):
    if(word == word[::-1]):
        return True
    else:
        return False

if __name__ == '__main__':
    main()