; Author: Jackson E. Rollins
; Last Modified: 2/14/2021
; OSU email address: rollijac@oregonstate.edu
; Course number/section: CS 271
; Assignment Number: #4                Due Date: 2/14/2021
; Description: This program asks the user for a number between 1-300 inclusive, and then prints out a spreadsheet of composite numbers in the amount requested by the user.

INCLUDE Irvine32.inc

uLimit = 300

.data
	intro1		BYTE	"Welcome to the Composite Number Spreadsheet", 0
	intro2		BYTE	"Programmed by Jackson E. Rollins", 0
	instruct1	BYTE	"This program is capable of generating a list of composite numbers.", 0
	instruct2	BYTE	"Simply let me know how many you would like to see.", 0
	instruct3	BYTE	"I'll accept order for up to 300 composites.", 0
	prompt		BYTE	"How many composites do you want to view? [1 .. 300]: ", 0
	error		BYTE	"Out of range. Please try again.", 0
	goodbye		BYTE	"Thanks for using my program!", 0
	spaces		BYTE	"   ", 0
	uInput		DWORD	?
	counter		DWORD	0
	compNum		DWORD	?

.code
intro PROC

;Introduces programmer, program, and instructions
	mov		edx, OFFSET intro1
	call	WriteString
	call	Crlf
	mov		edx, OFFSET intro2
	call	WriteString
	call	Crlf
	mov		edx, OFFSET instruct1
	call	WriteString
	call	Crlf
	mov		edx, OFFSET instruct2
	call	WriteString
	call	Crlf
	mov		edx, OFFSET instruct3
	call	WriteString
	call	Crlf
	call	Crlf

	ret
intro ENDP

validate PROC

;Validates that the number is within the allowed range
	cmp		eax, 1
	jl		verror
	cmp		eax, uLimit
	jg		verror
	jmp		vend

verror:
	mov		eax, -1

;End the proc
vend:
	ret
validate ENDP

getUserData PROC

;Prompts the user and then retrieves the inputted data
retrieve:
	mov		edx, OFFSET prompt
	call	WriteString
	call	ReadInt
	call	validate
	cmp		eax, 0
	jl		inputerror
	mov		uInput, eax
	jmp		gend

;Prompts the error messgae if the input isn't valid
inputerror:
	mov		edx, OFFSET error
	call	WriteString
	call	Crlf
	jmp		retrieve

;end the proc
gend:
	ret
getUserData ENDP

isComposite PROC

;Checks if current number is composite by dividing and comparing the modulus to 0
iLoop:
	cmp		ebx, eax
	je		zeroComp
	cdq
	div		ebx
	cmp		edx, 0
	je		yComp
	jne		nComp

;If the number isn't composite to start, increment the number and reset the divisor
zeroComp:
	inc		compNum
	mov		eax, compNum
	mov		ebx, 2
	jmp		iLoop

;If a number is composite, end the proc
yComp:
	ret

;If a number isn't composite with divisor, increment the number and reset the divisor
nComp:
	mov		eax, compNum
	inc		ebx
	jmp		iLoop

isComposite ENDP

showComposites PROC

	mov		ecx, uInput
	mov		eax, 4
	mov		compNum, eax
	mov		ebx, 2

;Prints every composite number up to the amount requested by the user
sLoop:
	call	isComposite
	mov		eax, compNum
	call	WriteDec
	inc		compNum
	inc		counter
	mov		eax, counter
	mov		ebx, 10
	cdq
	div		ebx
	cmp		edx, 0
	je		newLine
	mov		edx, OFFSET spaces
	call	WriteString
	jmp		send

;Printes out a new row/line for the numbers
newLine:
	call	Crlf
	jmp		send

;loop back with a new number, or end the proc
send:
	mov		ebx, 2
	mov		eax, compNum
	loop	sLoop

	ret
showComposites ENDP

outro PROC

;Prints out the goodbye message to the user
	call	Crlf
	mov		edx, OFFSET goodbye
	call	WriteString

	ret
outro ENDP

main PROC

;Main procedure that runs the program
	call	intro
	call	getUserData
	call	showComposites
	call	outro

	exit
main ENDP

END main
