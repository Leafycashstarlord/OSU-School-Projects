; Author: Jackson E. Rollins
; Last Modified: 3/17/2021
; OSU email address: rollijac@oregonstate.edu
; Course number/section: CS 271
; Assignment Number: Final Project                Due Date: 3/17/20201
; Description:

INCLUDE Irvine32.inc

.data

.code
main PROC

	exit
main ENDP

;Takes in the parameters that have been pushed from the main PROC and decides to either encrypt, decrypt, or decoy calculation based off of the parameters
compute PROC
	push	ebp
	mov		ebp, esp
	mov		eax, [ebp + 8]
	mov		eax, [eax]

	cmp		eax, -1
	je		encryption
	cmp		eax, -2
	je		decryption
	jmp		decoys

;Pushes all the parameters into the decoy PROC and then sends the program to complete the decoy calculation before returning to the main PROC
decoys:
	push	[ebp + 14]
	push	[ebp + 12]
	push	[ebp + 8]
	call	decoy
	pop		ebp
	ret		12

;Pushes all the parameters into the encryption PROC and then sends the program to complete the encryption before returning to the main PROC
encryption:
	push	[ebp + 16]
	push	[ebp + 12]
	push	[ebp + 8]
	call	encrypt
	pop ebp
	ret 12

;Pushes all the parameters into the decryption PROC and then sends the program to complete the decryption before returning to the main PROC
decryption:
	push	[ebp + 16]
	push	[ebp + 12]
	push	[ebp + 8]
	call	decrypt
	pop ebp
	ret 12

compute ENDP

;Takes in the parameters that have been pushed from the compute PROC. Adds the two WORD values before putting them into the DWORD value.
decoy PROC
	push	ebp
	mov		ebp, esp

	mov		ax, [ebp + 14]
	mov		bx, [ebp + 12]
	mov		edi, [ebp + 8]
	add		ax, bx
	cwd
	mov		[edi], ax

	pop		ebp
	ret		12
decoy ENDP

;Takes in the parameters that have been pushed from the compute PROC. Uses the BYTE key parameter to encrypt the BYTE message parameter.
encrypt PROC
	push	ebp
	mov		ebp, esp
	mov		esi, [ebp + 16]
	mov		edi, [ebp + 12]
	xor		eax, eax

;Loops through the message, encrypting it based on the key
eloop:
	mov		al, [edi]
	cmp		al, 0
	je		equit
	cmp		al, 97
	jl		eiterate
	cmp		al, 122
	jg		eiterate
	sub		al, 97
	mov		bl, [esi + eax]
	mov		[edi], bl
	jmp		eiterate

;Iterates the loop
eiterate:
	inc		edi
	jmp		eloop

;Ends the encrypt code and returns to compute
equit:
	pop		ebp
	ret		12

encrypt ENDP

;Takes in the parameters that have been pushed from the compute PROC. Uses the BYTE key parameter to decrypt the BYTE message parameter. This implementation isn't fully working.
decrypt PROC
	push	ebp
	mov		ebp, esp
	mov		esi, [ebp + 16]
	mov		edi, [ebp + 12]
	xor		eax, eax

;Loops through the message, decryptin git based on the key
dloop:
	mov		al, [edi]
	cmp		al, 0
	je		dquit
	cmp		al, 97
	jl		diterate
	cmp		al, 122
	jg		diterate
	
	;iterate through key until you find the right letter (code inserted here)
	
	mov		bl, [esi + eax]
	mov		[edi], bl

	jmp		diterate

;Iterate the loop
diterate:
	inc		edi
	jmp		dloop

;Ends the decrypt code and returns to compute
dquit:
	pop		ebp
	ret		12
decrypt ENDP

END main
