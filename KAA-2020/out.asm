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
	l0 SDWORD 0
	l1 SDWORD 1
	l2 SDWORD 1
	l3 SDWORD 1
	l4 SDWORD -6
	l10 DWORD 3
	l11 SDWORD 2
	l12 BYTE 1
	l13 BYTE 0
	l14 BYTE "Факториал 6 равен ", 0
	l20 BYTE "Сумма переменных a и b равна", 0
	l21 BYTE 103
	l22 BYTE " - ", 0
	l23 BYTE "a=", 0
	l24 BYTE "b=", 0
	l30 BYTE "c=", 0
	l31 BYTE "d=", 0
	l32 BYTE "сумма строк e и g=", 0
	l33 BYTE "b=3; b=(uint) a; b равно:", 0
	l34 BYTE "Длина строки e", 0
	l40 DWORD 100
	l41 BYTE "Случайное число", 0
	l42 SDWORD 2
	l43 BYTE "a/2=", 0
	l44 SDWORD 2
	l100 SDWORD 2
	l101 SDWORD 10
	l102 BYTE " a * 2 + 2 - 10=", 0
	l103 SDWORD 4
	l104 BYTE " result1 >> 4 =", 0
	l110 SDWORD 2
	l111 BYTE "result2 << 2=", 0
	l112 BYTE "3 в степени", 0
	l113 SDWORD 3
	l114 SDWORD 3
	l120 SDWORD 0
.data
	powresult SDWORD 0
	for_0i SDWORD 0
	factorialresult SDWORD 0
	for_1iter SDWORD 0
	maina SDWORD 0
	mainb DWORD 0
	mainl SDWORD 0
	mainc BYTE 0
	maind BYTE 0
	maine DWORD ?
	mainf DWORD ?
	maing BYTE 0
	mainstrSum DWORD ?
	mainfact SDWORD 0
	mainlength SDWORD 0
	mainparm DWORD 0
	mainnumber DWORD 0
	mainresult1 SDWORD 0
	mainresult2 SDWORD 0
	mainresult3 SDWORD 0
	mainresult4 SDWORD 0
.code

pow11_proc PROC, pownumber : SDWORD, powpower : SDWORD
	push pownumber
	pop powresult
	push l0
	pop for_0i
	metkafor_0i:
	push powresult
	push pownumber
	pop eax
	pop ebx
	imul eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop powresult
	push for_0i
	push l1
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	 pop for_0i
	push for_0i
	pop ebx
	push powpower
	pop eax
	 cmp ebx, eax
	jb  metkafor_0i
	push powresult

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
	ret 8

pow11_proc ENDP

factorial1_proc PROC, factoriala : SDWORD
	push factoriala
	pop factorialresult
	push l2
	pop for_1iter
	metkafor_1iter:
	push factorialresult
	push for_1iter
	pop eax
	pop ebx
	imul eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop factorialresult
	push for_1iter
	push l3
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	 pop for_1iter
	push for_1iter
	pop ebx
	push factoriala
	pop eax
	 cmp ebx, eax
	jb  metkafor_1iter
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
	push l4
	pop maina
	push l10
	pop mainb
	push l11
	pop mainl
	push offset l12
	pop dword ptr mainc
	push offset l13
	pop dword ptr maind
	 mov maine,offset l14
	 mov mainf,offset l20
	push offset l21
	pop ecx
	pop eax
	sar  eax, cl
	jo EXIT_OVERFLOW
	push eax
	pop dword ptr maing
	push dword ptr maine
	push offset l22
	call strcon
	jo EXIT_OVERFLOW
	push eax
	push dword ptr mainf
	call strcon
	jo EXIT_OVERFLOW
	push eax
	pop mainstrSum
	push offset l23
	call outstr

	push maina
	call outint

	push offset l24
	call outstr

	push mainb
	call outuint

	push offset l30
	call outstr

	push offset mainc
	call outbool

	push offset l31
	call outstr

	push offset maind
	call outbool

	push offset l32
	call outstr

	push dword ptr mainstrSum
	call outstr

	push mainl
	call factorial1_proc
	push eax
	pop mainfact
	push dword ptr maine
	call outstr

	push mainfact
	call outint

	push maina
	call intToUint 
	push eax
	pop mainb
	push offset l33
	call outstr

	push mainb
	call outuint

	push dword ptr maine
	call strl
	push eax
	pop mainlength
	push offset l34
	call outstr

	push mainlength
	call outint

	push l40
	pop mainparm
	push mainparm
	call random
	push eax
	pop mainnumber
	push offset l41
	call outstr

	push mainnumber
	call outuint

	push maina
	push l42
	pop ebx
	pop eax
	test ebx,ebx
	jz EXIT_DIV_ON_NULL
	cdq
	idiv ebx
	push eax
	pop mainresult1
	push offset l43
	call outstr

	push mainresult1
	call outint

	push maina
	push l44
	pop eax
	pop ebx
	imul eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push l100
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push l101
	pop eax
	neg eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop mainresult2
	push offset l102
	call outstr

	push mainresult2
	call outint

	push mainresult1
	push l103
	pop ecx
	pop eax
	sar  eax, cl
	jo EXIT_OVERFLOW
	push eax
	pop mainresult3
	push offset l104
	call outstr

	push mainresult3
	call outint

	push mainresult2
	push l110
	pop ecx
	pop eax
	sal eax, cl
	jo EXIT_OVERFLOW
	push eax
	pop mainresult4
	push offset l111
	call outstr

	push mainresult4
	call outint

	push offset l112
	call outstr

	push l113
	push l114
	call pow11_proc
	push eax
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