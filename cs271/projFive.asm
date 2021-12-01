; Author: Jackson E. Rollins
; Last Modified: 2/28/2021
; OSU email address: rollijac@oregonstate.edu
; Course number/section: CS 271
; Assignment Number: #5                Due Date: 2/28/2021
; Description: This program asks the user for a number and generates random numbers up to the requested amount. It then displays the list, sorts its, finds the median value, and then prints the median value and sorted list.

INCLUDE Irvine32.inc

MIN = 100
MAX = 999
LIST_MIN = 15
LIST_MAX = 200

.data
	intro1		BYTE	"Sorting Random Integers", 0
	intro2		BYTE	"Programmed by Jackson E. Rollins", 0
	instruct1	BYTE	"This program generates random numbers in the range [100 .. 999],", 0
	instruct2	BYTE	"displays the original list, sorts the list, and calculates the", 0
	instruct3	BYTE	"median value. Finally, it displays the list sorted in descending order.", 0
	prompt		BYTE	"How many numbers should be generated? [15 .. 200]: ", 0
	error		BYTE	"Invalid Input", 0
	list1		BYTE	"The unsorted random numbers: ", 0
	list2		BYTE	"The sorted list: ", 0
	medLine		BYTE	"The median is ", 0
	goodbye		BYTE	"Thanks for using my program!", 0
	spaces		BYTE	"   ", 0
	numlist		DWORD	MAX	DUP(?)
	uInput		DWORD	?
	genNum		DWORD	0

.code
intro PROC

;Introduces the user to the program and prints out the instructions
	push	ebp
	mov		ebp, esp
	mov		edx, [ebp + 8]
	call	WriteString
	call	Crlf
	mov		edx, [ebp + 12]
	call	WriteString
	call	Crlf
	mov		edx, [ebp + 16]
	call	WriteString
	call	Crlf
	mov		edx, [ebp + 20]
	call	WriteString
	call	Crlf
	mov		edx, [ebp + 24]
	call	WriteString
	call	Crlf
	call	Crlf
	pop		ebp

	ret	8
intro ENDP

getData PROC
	
;Asks the user for how many numbers they want in the list
	push	ebp
	mov		ebp, esp
	mov		ebx, [esp + 16]

;Asks the user
reqUser:
	mov		edx, [ebp+ 8]
	call	WriteString
	call	ReadInt
	cmp		eax, LIST_MIN
	jl		gerror
	cmp		eax, LIST_MAX
	jg		gerror
	jmp		gend

;Prints out an error message if the requested amount is out of scope
gerror:
	mov		edx, [ebp + 12]
	call	WriteString
	call	Crlf
	jmp		reqUser

;Ends the procedure
gend:
	mov		[ebx], eax
	pop		ebp
	ret		4
getData ENDP

fillArray PROC

;Randomly chooses numbers between 100 and 999 to fill the list
	push	ebp
	mov		ebp, esp
	mov		edi, [ebp + 12]
	mov		ecx, [ebp + 8]
	call	Randomize

;Adds the number to the list
fill:
	mov		eax, MAX
	sub		eax, MIN
	inc		eax
	call	RandomRange
	add		eax, MIN
	mov		[edi], eax
	add		edi, 4
	loop	fill

	pop		ebp
	ret		8
fillArray ENDP

displayList PROC

;Prints out every number in the given list
	push	ebp
	mov		ebp, esp
	mov		esi, [ebp + 8]
	mov		ecx, [ebp + 12]
	mov		edx, [ebp + 16]
	mov		genNum, 0
	call	Crlf
	call	WriteString
	call	Crlf

;Prints the next number in the list
print:
	mov		eax, [esi]
	call	WriteDec
	inc		genNum
	mov		edx, OFFSET spaces
	call	WriteString

	mov		edx, 0
	mov		eax, genNum
	mov		ebx, 10
	div		ebx
	cmp		edx, 0
	je		newLine
	jmp		skipLine

;Makes a new line in the printed list
newLine:
	call	Crlf

;Either loops back to print numbers or stops printing
skipLine:
	add		esi, 4
	loop	print

	call	Crlf

	pop		ebp
	ret		12

displayList ENDP

sortList PROC

;Takes the unsorted list and sorts it from greatest to least
	push	ebp
	mov		ebp, esp
	mov		ecx, [ebp + 8]
	mov		esi, [ebp + 12]
	dec		ecx


oLoop:
	mov		eax, [esi]
	mov		edx, esi
	push	ecx

iLoop:
	mov		ebx, [esi + 4]
	mov		eax, [edx]
	cmp		eax, ebx
	jge		noSwap
	add		esi, 4
	push	esi
	push	edx
	push	ecx
	call	exchange
	sub		esi, 4

noSwap:
	add		esi, 4
	loop	iLoop

	pop		ecx
	mov		esi, edx
	add		esi, 4
	loop	oLoop

	pop		ebp
	ret		8
sortList ENDP

exchange PROC

;Exchanges the array locations of two valaues within the list
	push	ebp
	mov		ebp, esp
	pushad
	mov		eax, [ebp + 16]
	mov		ebx, [ebp + 12]
	mov		edx, eax
	sub		edx, ebx
	mov		esi, ebx
	mov		ecx, [ebx]
	mov		eax, [eax]
	mov		[esi], eax
	add		esi, edx
	mov		[esi], ecx
	popad
	pop		ebp
	ret		12
exchange ENDP

displayMed PROC

;Calculates the median of all the values in the list and prints it to the user
	pushad
	mov		ebp, esp
	mov		edi, [ebp + 44]
	mov		edx, [ebp + 36]
	call	WriteString
	mov		eax, [ebp + 40]
	cdq
	mov		ebx, 2
	div		ebx
	shl		eax, 2
	add		edi, eax
	cmp		edx, 0
	je		disEven
	jmp		disOdd

;If the resulting calculation is even
disEven:
	mov		eax, [edi]
	add		eax, [edi - 4]
	cdq
	mov		ebx, 2
	div		ebx
	call	WriteDec
	call	Crlf
	jmp		dend

;If the resulting calculation is odd
disOdd:
	mov		eax, [edi]
	call	WriteDec
	call	Crlf
	jmp		dend

dend:
	popad
	ret		12
displayMed ENDP

outro PROC

;Prints out the goodbye message to the user
	call	Crlf
	mov		edx, OFFSET goodbye
	call	WriteString
	call	Crlf
	call	Crlf
	call	Crlf
outro ENDP

main PROC

;Main Procedure that runs the program

;Runs the intro procedure
	push	OFFSET instruct3
	push	OFFSET instruct2
	push	OFFSET instruct1
	push	OFFSET intro2
	push	OFFset intro1
	call	intro

;Runs the getData procedure
	push	OFFSET uInput
	push	OFFSET error
	push	OFFSET prompt
	call	getData

;Runs the fillArray procedure
	push	OFFSET numlist
	push	uInput
	call	fillArray

;Runs the displayList procedure for the unorganized list
	push	OFFSET list1
	push	uInput
	push	OFFSET numList
	call	displayList

;Runs the sortList procedure
	push	OFFSET numList
	push	uInput
	call	sortList

;Runs the displayMed procedure
	push	OFFSET numList
	push	uInput
	push	OFFSET medLine
	call	displayMed

;Runs the displayList procedure for the organized list
	push	OFFSET list2
	push	uInput
	push	OFFSET numList
	call	displayList

;Runs the outro procedure
	call	outro

	exit
main ENDP

END main
