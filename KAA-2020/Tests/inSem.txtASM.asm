.586
.model flat, stdcall
includelib userlib.lib
includelib kernel32.lib
includelib libucrt.lib

ExitProcess PROTO : DWORD
strl PROTO : DWORD
random PROTO : DWORD
outstr PROTO : DWORD
outbool PROTO : DWORD
outchar PROTO : DWORD
outuint PROTO : DWORD
outint PROTO : SDWORD
strcon PROTO : DWORD, : DWORD 
intToUint PROTO : SDWORD
uintToInt PROTO : DWORD
.stack 4096
.const
	overflow db 'ERROR: VARIABLE OVERFLOW', 0 
	null_division db 'ERROR: DIVISION BY ZERO', 0
	l0 SDWORD 1
	l1 SDWORD 1
	l2 SDWORD 4
	l3 SDWORD 0
.data
	factorialresult SDWORD 0
	for_0iter SDWORD 0
	mainfactorial SDWORD 0
.code

factorial1_proc PROC, factoriala : SDWORD
	push factoriala
	pop factorialresult
	push l0
	pop for_0iter
	metkafor_0iter:
	push factorialresult
	push for_0iter
	pop eax
	pop ebx
	imul eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop factorialresult
	push for_0iter
	push l1
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	 pop for_0iter
	push for_0iter
	pop ebx
	push factoriala
	pop eax
	 cmp ebx, eax
	jb  metkafor_0iter
	push factorialresult

	jmp EXIT
	EXIT_DIV_ON_NULL:
	push offset null_division
	call outstr
	push - 1
	call ExitProcess

	EXIT_OVERFLOW:
	push offset overflow
	call outstr
	push - 2
	call ExitProcess

	EXIT:
	pop eax
	ret 4

factorial1_proc ENDP

main PROC
	push l2
	pop mainfactorial
	push mainfactorial
	call outint


	jmp EXIT
	EXIT_DIV_ON_NULL:
	push offset null_division
	call outstr
	push - 1
	call ExitProcess

	EXIT_OVERFLOW:
	push offset overflow
	call outstr
	push - 2
	call ExitProcess

	EXIT:
	push 0
	call ExitProcess

main ENDP
end main