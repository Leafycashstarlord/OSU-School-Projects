; Author: Jackson E. Rollins
; Last Modified: 1/17/2021
; OSU email address: rollijac@oregonstate.edu
; Course number/section: CS271
; Assignment Number: #1                Due Date: 1/17/2021
; Description: The program takes two integers that the user inputs and performs a series of simple algebraic equations to them - addition, subtraction, multiplication, and division. The results are then printed to the user.

INCLUDE Irvine32.inc

.data

	intro1		BYTE	"Elementary Arithmetic by Jackson E. Rollins", 0
	intro2		BYTE	"**EC: Program verifies the second number to be less than the first.", 0
	intro3		BYTE	"**EC: Program displays the squares of each number.", 0
	intro4		BYTE	"Enter 2 numbers, and I'll show you the sum, difference, product, quotient, and remainder.", 0
	prompt_1	BYTE	"First Number?: ",0 
	prompt_2	BYTE	"Second Number?: ", 0
	err_prompt	BYTE	"The second number must be less than the first!", 0
	num1		DWORD	?	;First number entered by user
	num2		DWORD	?	;Second number entered by user
	sum			DWORD	?	;Sum of num1 and num2
	dif			DWORD	?	;Difference of num1 and num2
	pro			DWORD	?	;Product of num1 and num2
	quo			DWORD	?	;Quotiant of num1 and num2
	remain		DWORD	?	;Remainder
	sqr1		DWORD	?	;Square of the first number
	sqr2		DWORD	?	;Square of the second number
	signSum	BYTE	" + ", 0
	signDif	BYTE	" - ", 0
	signPro	BYTE	" * ", 0
	signQuo	BYTE	" / ", 0
	wordRem	BYTE	" remainder ", 0
	signEqu	BYTE	" = ", 0
	wordSqr	BYTE	"Square of ", 0
	goodBye		BYTE	"Goodbye, thanks for playing!", 0


.code
main PROC

;//0. Introduce programmer and program details
	mov		edx, OFFSET intro1 
	call	WriteString
	call	Crlf
	mov		edx, OFFSET intro2 
	call	WriteString
	call	Crlf
	mov		edx, OFFSET intro3 
	call	WriteString
	call	Crlf
	mov		edx, OFFSET intro4 
	call	WriteString
	call	Crlf
	call	Crlf
	
L2:

;Gets the two numbers from the user
	mov		edx, OFFSET prompt_1
	call	WriteString
	call	ReadInt
	mov		num1, eax
	mov		edx, OFFSET prompt_2
	call	WriteString
	call	ReadInt
	mov		num2, eax
	call	CrLf
	

;Checks to see if the num2 is bigger than num1, and repromts the user for new numbers if so
	cmp		eax, num1
	jg		L1
	jl		L3

L1:

;Gives an error message if the second number is greater than the first
	mov		edx, OFFSET err_prompt 
	call	WriteString
	call	Crlf
	call	Crlf
	jmp		L2


L3:

;Calcualte the sum, and print it
	mov		eax, num1
	mov		ebx, num2
	add		eax, ebx
	mov		sum, eax

	mov		eax, num1
	call	WriteDec
	mov		edx, OFFSET signSum
	call	WriteString
	mov		eax, num2
	call	WriteDec
	mov		edx, OFFSET signEqu
	call	WriteString
	mov		eax, sum
	call	WriteDec
	call	CrLf



;Calculate the difference and print it
	mov		eax, num1
	mov		ebx, num2
	sub		eax, ebx
	mov		dif, eax

	mov		eax, num1
	call	WriteDec
	mov		edx, OFFSET signDif
	call	WriteString
	mov		eax, num2
	call	WriteDec
	mov		edx, OFFSET signEqu
	call	WriteString
	mov		eax, dif
	call	WriteDec
	call	CrLf


;Calculate the product and print it
	mov		eax, num1
	mov		ebx, num2
	mul		ebx
	mov		pro, eax

	mov		eax, num1
	call	WriteDec
	mov		edx, OFFSET signPro
	call	WriteString
	mov		eax, num2
	call	WriteDec
	mov		edx, OFFSET signEqu
	call	WriteString
	mov		eax, pro
	call	WriteDec
	call	CrLf


;Calculate the quotient and remainder and print it
	mov		eax, num1
	mov		ebx, num2
	mov		edx, 0
	div		ebx
	mov		quo, eax
	mov		remain, edx

	mov		eax, num1
	call	WriteDec
	mov		edx, OFFSET signEqu
	call	WriteString
	mov		eax, num2
	call	WriteDec
	mov		edx, OFFSET signEqu
	call	WriteString
	mov		eax, quo
	call	WriteDec
	mov		edx, OFFSET wordRem
	call	WriteString
	mov		eax, remain
	call	WriteDec
	call	CrLf


;Calculate the square of the first number and print it
	mov		eax, num1
	mov		ebx, num1
	mul		ebx
	mov		sqr1, eax

	mov		edx, OFFSET wordSqr
	call	WriteString
	mov		eax, num1
	call	WriteDec
	mov		edx, OFFSET signEqu
	call	WriteString
	mov		eax, sqr1
	call	WriteDec
	call	CrLf


;Calculate the square of the second number and print it
	mov		eax, num2
	mov		ebx, num2
	mul		ebx
	mov		sqr2, eax

	mov		edx, OFFSET wordSqr
	call	WriteString
	mov		eax, num2
	call	WriteDec
	mov		edx, OFFSET signEqu
	call	WriteString
	mov		eax, sqr2
	call	WriteDec
	call	CrLf

;Say goodbye to the user
	call	Crlf
	mov		edx, OFFSET goodBye
	call	WriteString
	call	Crlf
	

	exit
main ENDP

END main