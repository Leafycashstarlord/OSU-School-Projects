; Author: Jackson E. Rollins
; Last Modified: 1/31/2021
; OSU email address: rollijac@oregonstate.edu
; Course number/section: CS 271
; Assignment Number: 3                 Due Date: 1/31/2021
; Description: This program will take any amount of negative numbers that the user inputs, validates that each is a negative number, and the proceedes to calculate and print out the sum and average of all the given numbers.

INCLUDE Irvine32.inc

lLimit = -100

.data
	intro1		BYTE	"Welcome to the Integer Accumulator by Jackson E. Rollins", 0
	prompt1		BYTE	"What's your name? ", 0
	prompt2		BYTE	"Enter a number: ", 0
	instruct1	BYTE	"Please enter numbers in the range of [-100, -1].", 0
	instruct2	BYTE	"Enter a non-negative number when  you are finished to see the results.", 0
	error		BYTE	"Invalid number, please enter numbers in the range of [-100, -1].", 0
	amount1		BYTE	"You entered ", 0
	amount2		BYTE	" valid numbers.", 0
	result1		BYTE	"The sum of your valid numbers is ", 0
	result2		BYTE	"The rounded average of your valid numbers is ", 0
	greeting	BYTE	"Hello, ", 0
	outro1		BYTE	"Thank you for playing Integer Accumulator!", 0
	outro2		BYTE	"Goodbye, ", 0
	uName		BYTE	100 DUP(0)
	counter		DWORD	0
	sumNum		DWORD	0
	avgNum		DWORD	?

.code
main PROC

;Introduces programmer and program title
	mov		edx, OFFSET intro1
	call	WriteString
	call	Crlf

;Prompts the user for their name, and greets them
	mov		edx, OFFSET prompt1
	call	WriteString
	mov		edx, OFFSET uName
	mov		ecx, SIZEOF uName
	call	ReadString
	mov		edx, OFFSET greeting
	call	WriteString
	mov		edx, OFFSET uName
	call	WriteString
	call	Crlf
	call	Crlf

;Tells the user the instructions for the program inputs
	mov		edx, OFFSET instruct1
	call	WriteString
	call	Crlf
	mov		edx, OFFSET instruct2
	call	WriteString
	call	Crlf

;Prompts the user for a negative number
getNum:
	mov		edx, OFFSET prompt2
	call	WriteString
	call	ReadInt
	jmp		validate

;Validates that the number is negative or not
validate:
	cmp		eax, -1
	jg		calcAvg
	cmp		eax, lLimit
	jl		invalid
	add		counter, 1
	add		sumNum, eax
	jmp		getNum

;Prompts an error message telling the user they input an invalid number
invalid:
	mov		edx, OFFSET error
	call	WriteString
	call	Crlf
	jmp		getNum

;Calculates the average of all the numbers the user inputs
calcAvg:
	mov		edx, 0
	mov		eax, sumNum
	cdq
	idiv	counter
	mov		avgNum, eax
	mov		eax, edx
	neg		eax
	mov		edx, 2
	mul		edx
	cmp		eax, counter
	jge		roundAvg
	jmp		printNums

;Rounds the average if needed
roundAvg:
	sub		avgNum, 1
	jmp		printNums

;Prints out the amount of numbers the user input, as well as the sum and average of all the numbers
printNums:
	mov		edx, OFFSET amount1
	call	WriteString
	mov		eax, counter
	call	WriteDec
	mov		edx, OFFSET amount2
	call	WriteString
	call	Crlf
	mov		edx, OFFSET result1
	call	WriteString
	mov		eax, sumNum
	call	WriteInt
	call	Crlf
	mov		edx, OFFSET result2
	call	WriteString
	mov		eax, avgNum
	call	WriteInt
	jmp		goodBye

;Prints out the goodbye message to the user
goodBye:
	call	Crlf
	mov		edx, OFFSET outro1
	call	WriteString
	call	Crlf
	mov		edx, OFFSET outro2
	call	WriteString
	mov		edx, OFFSET uName
	call	WriteString
	call	Crlf

	exit
main ENDP

END main
