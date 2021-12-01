; Author: Jackson E. Rollins
; Last Modified: 1/24/2021
; OSU email address: rollijac@oregonstate.edu
; Course number/section: CS271
; Assignment Number: #2                Due Date: 1/24/2021
; Description: The program will take an integer from 1 to 46 that the user inputs, validates that the input is an integer, and the procedes to calculate and print all the numbers of the fibonacci sequence up to the given number

INCLUDE Irvine32.inc

uLimit = 46
lLimit = 1

.data

	intro1		BYTE	"Fibonacci Numbers", 0
	intro2		BYTE	"Programmed by Jackson E. Rollins", 0
	greeting	BYTE	"Hello, ", 0
	prompt1		BYTE	"What's your name? ", 0
	prompt2		BYTE	"How many Fibonacci terms do you want? ", 0
	instruct1	BYTE	"Enter the number of Fibonacci terms to be displayed.", 0
	instruct2	BYTE	"Provide the number as an integer in the range of [1 .. 46].", 0
	error		BYTE	"Out of range. Enter a number in the range of [1 .. 46].", 0
	outro1		BYTE	"Results certified by Jackson E. Rollins."
	outro2		BYTE	"Goodbye, ", 0
	spaces		BYTE	"     ", 0
	uName		BYTE	100 DUP(0)
	numTerm		DWORD	?	;Number of termss that the user asks for
	fibOne		DWORD	1	;A number of the sequence, starts at 1
	fibTwo		DWORD	1	;Another number of the sequence, starts at 1
	totalTerm	DWORD	1	;Total terms on the line, starts at 1


.code
main PROC

;Introduce programmer and program title
	mov		edx, OFFSET intro1
	call	WriteString
	call	Crlf
	mov		edx, OFFSET intro2
	call	WriteString
	call	Crlf

;Prompts the user for their name
	mov		edx, OFFSET prompt1
	call	WriteString
	mov		edx, OFFSET uName
	mov		ecx, SIZEOF	uName
	call	ReadString
	mov		edx, OFFSET greeting
	call	WriteString
	mov		edx, OFFSET uName
	call	WriteString
	call	Crlf

;Tells the user the instructions for Sequence term inputs
	mov		edx, OFFSET instruct1
	call	Writestring
	call	Crlf
	mov		edx, OFFSET instruct2
	call	Writestring
	call	Crlf

;Retrieves the quested term from the user
getNum:
	mov		edx, OFFSET prompt2
	call	WriteString
	call	ReadInt
	mov		numTerm, eax
	jmp		validate

;Validates that the user's number is between 1 and 46 inclusive
validate:
	cmp		eax, uLimit
	jg		invalid
	cmp		eax, lLimit
	jl		invalid
	mov		ecx, numTerm
	jmp		firstTwo

;Prompts an error messages and reprompts for a new number if the initial number given by the user is out of bounds
invalid:
	mov		edx, OFFSET error
	call	WriteString
	call	Crlf
	jmp		getNum

;Prints the first two numbers of the sequence
firstTwo:
	mov		eax, fibOne
	call	WriteDec
	cmp		ecx, 1
	je		goodBye
	dec		ecx
	mov		edx, OFFSET spaces
	call	WriteString
	mov		eax, fibTwo
	call	WriteDec
	cmp		ecx, 1
	je		goodBye
	dec		ecx
	call	WriteString
	jmp		calcNums

;Calculates the next number in the sequence
calcNums:
	mov		eax, fibOne
	mov		ebx, fibTwo
	add		eax, ebx
	mov		fibOne, ebx
	mov		fibTwo, eax
	inc		totalTerm
	jmp		display

;Displays the new number in the sequence after checking to see if a new line needs to be made
display:
	mov		edx, totalTerm
	cmp		edx, 4
	je		makeNewLine
	mov		eax, fibTwo
	call	WriteDec
	mov		edx, OFFSET spaces
	call	WriteString
	inc		ebp
	loop	calcNums

;Makes a new line if so needed
makeNewLine:
	call	Crlf
	mov		totalTerm, 0
	jecxz	goodBye
	jmp		display

;Says goodbye to the user and closes the program
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
