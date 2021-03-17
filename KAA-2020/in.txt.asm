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
	l10 DWORD 58
	l11 SDWORD 2
	l12 BYTE 1
	l13 BYTE 0
	l14 BYTE "|e Факториал 6 равен: ", 0
	l20 BYTE "|e Сумма переменных a и b равна: ", 0
	l21 BYTE "Строка 1 ", 0
	l22 BYTE "Строка 2", 0
	l23 BYTE 103
	l24 BYTE " и ", 0
	l30 BYTE "|h a=", 0
	l31 BYTE "|e|h b(16)=", 0
	l32 BYTE "|e|b b(2)=", 0
	l33 BYTE "|e  c=", 0
	l34 BYTE "|e |d d=", 0
	l40 BYTE "|e Cумма строк oneStr и twoStr: |e |t ", 0
	l41 BYTE "|e b=3; |e b=(uint)a; |e b равно: ", 0
	l42 BYTE "|f Длина строки e:", 0
	l43 DWORD 100
	l44 BYTE "|fCлучайное число:", 0
	l100 SDWORD 2
	l101 BYTE "|f a/2 =", 0
	l102 SDWORD 2
	l103 SDWORD 2
	l104 SDWORD 10
	l110 BYTE "|f a * 2 + 2 - 10 =", 0
	l111 SDWORD 4
	l112 BYTE "|f result1 >> 4 =", 0
	l113 SDWORD 2
	l114 BYTE "|f result2 << 2 =", 0
	l120 SDWORD 5
	l121 SDWORD 2
	l122 SDWORD 2
	l123 SDWORD 3
	l124 BYTE "|f 5/2 (2)== 2*3(6):", 0
	l130 SDWORD 95
	l131 SDWORD 5
	l132 SDWORD 2
	l133 SDWORD 4
	l134 SDWORD 5
	l140 SDWORD 3
	l141 SDWORD 3
	l142 SDWORD 6
	l143 BYTE "|f (95 / 5) << 2 (79) != (4-5) *3 / 3*6(0):", 0
	l144 SDWORD 5
	l200 SDWORD 2
	l201 SDWORD 2
	l202 SDWORD 3
	l203 BYTE "|f 5/2 (2) < 2*3(6): ", 0
	l204 SDWORD 4
	l210 SDWORD 5
	l211 SDWORD 3
	l212 SDWORD 3
	l213 SDWORD 6
	l214 SDWORD 95
	l220 SDWORD 5
	l221 SDWORD 2
	l222 BYTE "|f (4-5) *3 / 3*6 (-6) < (95 / 5) << 2 (79):", 0
	l223 BYTE "|d 3 в степени: ", 0
	l224 SDWORD 3
	l230 SDWORD 3
	l231 SDWORD 0
	l232 SDWORD 0
	l233 SDWORD 0
	l234 SDWORD 0
	l240 SDWORD 3
	l241 SDWORD 1
	l242 SDWORD 1
	l243 BYTE "|e 1-resulting =", 0
	l244 SDWORD 0
	l300 SDWORD 2
	l301 SDWORD 1
	l302 SDWORD 1
	l303 BYTE "|e|t 2-resulting =", 0
	l304 SDWORD 0
	l310 SDWORD 1
	l311 SDWORD 1
	l312 SDWORD 1
	l313 BYTE "|e|t|t 3-resulting =", 0
	l314 SDWORD 0
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
	mainoneStr DWORD ?
	maintwoStr DWORD ?
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
	mainlogic_1 BYTE 0
	mainlogic_2 BYTE 0
	mainlogic_3 BYTE 0
	mainlogic_4 BYTE 0
	main1_resulting SDWORD 0
	main2_resulting SDWORD 0
	main3_resulting SDWORD 0
	for_2iter SDWORD 0
	for_3iter SDWORD 0
	for_4iter SDWORD 0
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
	 mov mainoneStr,offset l21
	 mov maintwoStr,offset l22
	push offset l23
	pop dword ptr maing
	push dword ptr mainoneStr
	push offset l24
	call strcon
	jo EXIT_OVERFLOW
	push eax
	push dword ptr maintwoStr
	call strcon
	jo EXIT_OVERFLOW
	push eax
	pop mainstrSum
	push offset l30
	call outstr
	push maina
	call outint
	push offset l31
	call outstr
	push mainb
	call outuint
	push offset l32
	call outstr
	push mainb
	call outuint
	push offset l33
	call outstr
	push offset mainc
	call outbool
	push offset l34
	call outstr
	push offset maind
	call outbool
	push offset l40
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
	push offset l41
	call outstr
	push mainb
	call outuint
	push dword ptr maine
	call strl
	push eax
	pop mainlength
	push offset l42
	call outstr
	push mainlength
	call outint
	push l43
	pop mainparm
	push mainparm
	call random
	push eax
	pop mainnumber
	push offset l44
	call outstr
	push mainnumber
	call outuint
	push maina
	push l100
	pop ebx
	pop eax
	test ebx,ebx
	jz EXIT_DIV_ON_NULL
	cdq
	idiv ebx
	push eax
	pop mainresult1
	push offset l101
	call outstr
	push mainresult1
	call outint
	push maina
	push l102
	pop eax
	pop ebx
	imul eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push l103
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push l104
	pop ebx
	pop eax
	sub eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop mainresult2
	push offset l110
	call outstr
	push mainresult2
	call outint
	push mainresult1
	push l111
	pop ecx
	pop eax
	sar  eax, cl
	jo EXIT_OVERFLOW
	push eax
	pop mainresult3
	push offset l112
	call outstr
	push mainresult3
	call outint
	push mainresult2
	push l113
	pop ecx
	pop eax
	sal eax, cl
	jo EXIT_OVERFLOW
	push eax
	pop mainresult4
	push offset l114
	call outstr
	push mainresult4
	call outint
	push l120
	push l121
	pop ebx
	pop eax
	test ebx,ebx
	jz EXIT_DIV_ON_NULL
	cdq
	idiv ebx
	push eax
	push l122
	push l123
	pop eax
	pop ebx
	imul eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop ebx 
	pop eax 
	 cmp eax,ebx
	je istrue48
	push 0
	jmp exit48
	istrue48:
	push 1 
	exit48:
	pop dword ptr mainlogic_1
	push offset l124
	call outstr
	push offset mainlogic_1
	call outbool
	push l130
	push l131
	pop ebx
	pop eax
	test ebx,ebx
	jz EXIT_DIV_ON_NULL
	cdq
	idiv ebx
	push eax
	push l132
	pop ecx
	pop eax
	sal eax, cl
	jo EXIT_OVERFLOW
	push eax
	push l133
	push l134
	pop ebx
	pop eax
	sub eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push l140
	pop eax
	pop ebx
	imul eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push l141
	pop ebx
	pop eax
	test ebx,ebx
	jz EXIT_DIV_ON_NULL
	cdq
	idiv ebx
	push eax
	push l142
	pop eax
	pop ebx
	imul eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop ebx 
	pop eax 
	 cmp eax,ebx
	jne istrue49
	push 0
	jmp exit49
	istrue49:
	push 1 
	exit49:
	pop dword ptr mainlogic_2
	push offset l143
	call outstr
	push offset mainlogic_2
	call outbool
	push l144
	push l200
	pop ebx
	pop eax
	test ebx,ebx
	jz EXIT_DIV_ON_NULL
	cdq
	idiv ebx
	push eax
	push l201
	push l202
	pop eax
	pop ebx
	imul eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop ebx 
	pop eax 
	 cmp eax,ebx
	jl istrue50
	push 0
	jmp exit50
	istrue50:
	push 1
	exit50:
	pop dword ptr mainlogic_3
	push offset l203
	call outstr
	push offset mainlogic_3
	call outbool
	push l204
	push l210
	pop ebx
	pop eax
	sub eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push l211
	pop eax
	pop ebx
	imul eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push l212
	pop ebx
	pop eax
	test ebx,ebx
	jz EXIT_DIV_ON_NULL
	cdq
	idiv ebx
	push eax
	push l213
	pop eax
	pop ebx
	imul eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push l214
	push l220
	pop ebx
	pop eax
	test ebx,ebx
	jz EXIT_DIV_ON_NULL
	cdq
	idiv ebx
	push eax
	push l221
	pop ecx
	pop eax
	sal eax, cl
	jo EXIT_OVERFLOW
	push eax
	pop ebx 
	pop eax 
	 cmp eax,ebx
	jl istrue51
	push 0
	jmp exit51
	istrue51:
	push 1
	exit51:
	pop dword ptr mainlogic_4
	push offset l222
	call outstr
	push offset mainlogic_4
	call outbool
	push offset l223
	call outstr
	push l224
	push l230
	call pow11_proc
	push eax
	call outint
	push l231
	pop main1_resulting
	push l232
	pop main2_resulting
	push l233
	pop main3_resulting
	push l234
	pop for_2iter
	metkafor_2iter:
	push main1_resulting
	push l242
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop main1_resulting
	push offset l243
	call outstr
	push main1_resulting
	call outint
	push l244
	pop for_3iter
	metkafor_3iter:
	push main2_resulting
	push l302
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop main2_resulting
	push offset l303
	call outstr
	push main2_resulting
	call outint
	push l304
	pop for_4iter
	metkafor_4iter:
	push main3_resulting
	push l312
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop main3_resulting
	push offset l313
	call outstr
	push main3_resulting
	call outint
	push for_2iter
	push l241
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push for_3iter
	push l301
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push for_4iter
	push l311
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	 pop for_4iter
	push for_2iter
	push for_3iter
	push for_4iter
	pop ebx
	push l240
	push l300
	push l310
	pop eax
	 cmp ebx, eax
	jb  metkafor_4iter
	push for_2iter
	push l241
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push for_3iter
	push l301
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	 pop for_3iter
	push for_2iter
	push for_3iter
	pop ebx
	push l240
	push l300
	pop eax
	 cmp ebx, eax
	jb  metkafor_3iter
	push for_2iter
	push l241
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	 pop for_2iter
	push for_2iter
	pop ebx
	push l240
	pop eax
	 cmp ebx, eax
	jb  metkafor_2iter

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