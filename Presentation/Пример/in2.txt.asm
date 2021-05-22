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
	l2 SDWORD -6
	l3 DWORD 96
	l4 SDWORD 2
	l10 BYTE "|h a=", 0
	l11 BYTE "|e|h b(16)=", 0
	l12 BYTE "|e|b b(2)=", 0
	l13 BYTE "|e|o b(8)=", 0
	l14 BYTE "|e|d b(10)=", 0
	l20 BYTE "|e a=-3; |e b=(uint)a; |e b равно: ", 0
	l21 DWORD 96
	l22 BYTE "|e b=96; |e a=(uint)b; |e a равно: ", 0
	l23 SDWORD 2
	l24 BYTE "|f a/2 =", 0
	l30 SDWORD 2
	l31 SDWORD 2
	l32 SDWORD 10
	l33 BYTE "|f a * 2 + 2 - 10 =", 0
	l34 SDWORD 4
	l40 BYTE "|f result1 >> 4 =", 0
	l41 SDWORD 2
	l42 BYTE "|f result2 << 2 =", 0
	l43 SDWORD 0
	l44 SDWORD 0
	l100 SDWORD 0
	l101 SDWORD 0
	l102 SDWORD 3
	l103 SDWORD 1
	l104 SDWORD 1
	l110 BYTE "|e 1-resulting =", 0
	l111 SDWORD 0
	l112 SDWORD 2
	l113 SDWORD 1
	l114 SDWORD 1
	l120 BYTE "|e|t 2-resulting =", 0
	l121 SDWORD 0
	l122 SDWORD 1
	l123 SDWORD 1
	l124 SDWORD 1
	l130 BYTE "|e|t|t 3-resulting =", 0
	l131 SDWORD 0
.data
	powresult SDWORD 0
	for_0i SDWORD 0
	maina SDWORD 0
	mainb DWORD 0
	mainl SDWORD 0
	mainresult1 SDWORD 0
	mainresult2 SDWORD 0
	mainresult3 SDWORD 0
	mainresult4 SDWORD 0
	main1_resulting SDWORD 0
	main2_resulting SDWORD 0
	main3_resulting SDWORD 0
	for_1iter SDWORD 0
	for_2iter SDWORD 0
	for_3iter SDWORD 0
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

main PROC
	push l2
	pop maina
	push l3
	pop mainb
	push l4
	pop mainl
	push offset l10
	call outstr
	push maina
	call outint
	push offset l11
	call outstr
	push mainb
	call outuint
	push offset l12
	call outstr
	push mainb
	call outuint
	push offset l13
	call outstr
	push mainb
	call outuint
	push offset l14
	call outstr
	push mainb
	call outuint
	push maina
	call intToUint 
	push eax
	pop mainb
	push offset l20
	call outstr
	push mainb
	call outuint
	push l21
	pop mainb
	push mainb
	call uintToInt 
	push eax
	pop maina
	push offset l22
	call outstr
	push maina
	call outint
	push maina
	push l23
	pop ebx
	pop eax
	test ebx,ebx
	jz EXIT_DIV_ON_NULL
	cdq
	idiv ebx
	push eax
	pop mainresult1
	push offset l24
	call outstr
	push mainresult1
	call outint
	push maina
	push l30
	pop eax
	pop ebx
	imul eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push l31
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push l32
	pop ebx
	pop eax
	sub eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop mainresult2
	push offset l33
	call outstr
	push mainresult2
	call outint
	push mainresult1
	push l34
	pop ecx
	pop eax
	sar  eax, cl
	jo EXIT_OVERFLOW
	push eax
	pop mainresult3
	push offset l40
	call outstr
	push mainresult3
	call outint
	push mainresult2
	push l41
	pop ecx
	pop eax
	sal eax, cl
	jo EXIT_OVERFLOW
	push eax
	pop mainresult4
	push offset l42
	call outstr
	push mainresult4
	call outint
	push l43
	pop main1_resulting
	push l44
	pop main2_resulting
	push l100
	pop main3_resulting
	push l101
	pop for_1iter
	metkafor_1iter:
	push main1_resulting
	push l104
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop main1_resulting
	push offset l110
	call outstr
	push main1_resulting
	call outint
	push l111
	pop for_2iter
	metkafor_2iter:
	push main2_resulting
	push l114
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop main2_resulting
	push offset l120
	call outstr
	push main2_resulting
	call outint
	push l121
	pop for_3iter
	metkafor_3iter:
	push main3_resulting
	push l124
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop main3_resulting
	push offset l130
	call outstr
	push main3_resulting
	call outint
	push for_1iter
	push l103
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push for_2iter
	push l113
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push for_3iter
	push l123
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	 pop for_3iter
	push for_1iter
	push for_2iter
	push for_3iter
	pop ebx
	push l102
	push l112
	push l122
	pop eax
	 cmp ebx, eax
	jb  metkafor_3iter
	push for_1iter
	push l103
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push for_2iter
	push l113
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	 pop for_2iter
	push for_1iter
	push for_2iter
	pop ebx
	push l102
	push l112
	pop eax
	 cmp ebx, eax
	jb  metkafor_2iter
	push for_1iter
	push l103
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	 pop for_1iter
	push for_1iter
	pop ebx
	push l102
	pop eax
	 cmp ebx, eax
	jb  metkafor_1iter

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