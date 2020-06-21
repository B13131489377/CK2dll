; r13�͕����񃋁[�v�̃J�E���^�B�t�H���g�ɕ����������Ă��Ȃ��Ă��֌W�Ȃ�
; r10�͕������lenght
; edx�i[rbp+1D0h+var_138]�j�͕����|�W�V�����J�E���^

EXTERN	mapJustifyProc1ReturnAddress1	:	QWORD
EXTERN	mapJustifyProc1ReturnAddress2	:	QWORD
EXTERN	mapJustifyProc2ReturnAddress	:	QWORD
EXTERN	mapJustifyProc3ReturnAddress	:	QWORD
EXTERN	mapJustifyProc4ReturnAddress	:	QWORD

;temporary space for code point
.DATA
	mapJustifyProc1TmpFlag	DD	0

ESCAPE_SEQ_1	=	10h
ESCAPE_SEQ_2	=	11h
ESCAPE_SEQ_3	=	12h
ESCAPE_SEQ_4	=	13h
LOW_SHIFT		=	0Fh
HIGH_SHIFT		=	9h
SHIFT_2			=	LOW_SHIFT
SHIFT_3			=	900h
SHIFT_4			=	8F1h
NO_FONT			=	98Fh
NOT_DEF			=	2026h
MAP_LIMIT		=	2Dh-3

.CODE
mapJustifyProc1 PROC
	cmp		byte ptr [r14 + rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [r14 + rax], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr [r14 + rax], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr [r14 + rax], ESCAPE_SEQ_4;
	jz		JMP_D;
	mov		mapJustifyProc1TmpFlag, 0h;
	movzx	eax, byte ptr [r14 + rax];
	mov		r10, qword ptr [rcx + rax * 8]
	test	r10, r10;
	jz		JMP_I;
	jmp		mapJustifyProc1ReturnAddress1;

JMP_A:
	movzx	eax, word ptr [r14 + rax + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr [r14 + rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr [r14 + rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr [r14 + rax + 1];
	add		eax, SHIFT_4;

JMP_F:
	dec		rdx;
	cmp		r14,MAP_LIMIT;
	ja		JMP_H;

	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_G;
JMP_H:
	mov		eax, NOT_DEF;

JMP_G:
	mov		mapJustifyProc1TmpFlag, 1h;
	mov     r10, qword ptr [rcx + rax * 8];

	test	r10, r10;
	jz		JMP_I;
	push	mapJustifyProc1ReturnAddress1;
	ret;

JMP_I:
	push	mapJustifyProc1ReturnAddress2;
	ret;
mapJustifyProc1 ENDP

;-------------------------------------------;

mapJustifyProc2 PROC
	cmp		mapJustifyProc1TmpFlag, 1h;
	jnz		JMP_A;

	; 3byte = 1�������ǂ���
	cmp		rdx, 2;
	ja		JMP_A;
	inc		rdx;
	inc		rdx;
	mov		rsi,1;
	movd	xmm6, esi;

JMP_A:

	; �G�X�P�[�v����
	cmp		mapJustifyProc1TmpFlag, 1h;
	jz		JMP_B;

	lea     eax, [rdx - 1]; ; -1���Ă���
	jmp		JMP_C;

JMP_B:
	lea     eax, [rdx - 2]; ; -2���Ă���

JMP_C:
	xorps	xmm8, xmm8;
	movss	xmm8, xmm0;
	movss	dword ptr [rbp + 1B0h - 148h], xmm1;
	xorps	xmm1, xmm1;
	sqrtss	xmm8, xmm8;

	push	mapJustifyProc2ReturnAddress;
	ret;
mapJustifyProc2 ENDP

;-------------------------------------------;

mapJustifyProc3 PROC
	movsd	xmm3, qword ptr [rbp + 1B0h - 190h];

	cmp		mapJustifyProc1TmpFlag, 1h;
	jnz		JMP_A;
	
	add     esi,3;
	add     r14,3;
	jmp		JMP_C;

JMP_A:
	inc		esi;
	inc		r14;

JMP_C:
	movsd	xmm4, qword ptr [rbp + 1B0h - 188h];
	movsd	xmm5, qword ptr [rbp + 1B0h - 198h];
	movsd   xmm9, qword ptr [rbp + 1B0h - 180h];
	movsxd	rax, edx;
	mov		qword ptr [rbp + 1B0h -128h], rsi;

	push	mapJustifyProc3ReturnAddress;
	ret;
mapJustifyProc3 ENDP

;-------------------------------------------;

mapJustifyProc4 PROC
	cmp		byte ptr [rdi + rax], ESCAPE_SEQ_1;
	jz		JMP_A;
			
	cmp		byte ptr [rdi + rax], ESCAPE_SEQ_2;
	jz		JMP_B;

	cmp		byte ptr [rdi + rax], ESCAPE_SEQ_3;
	jz		JMP_C;

	cmp		byte ptr [rdi + rax], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx	eax, byte ptr [rdi + rax];
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr [rdi + rax + 1];
	jmp		JMP_F;
JMP_B:
	movzx	eax, word ptr [rdi + rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;
JMP_C:
	movzx	eax, word ptr [rdi + rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;
JMP_D:
	movzx	eax, word ptr [rdi + rax + 1];
	add		eax, SHIFT_4;
	jmp		JMP_F;

JMP_F:
	add		edi, 2;
	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_E;
	mov		eax, NOT_DEF;

JMP_E:
	mov		r10, qword ptr [r12 + rax * 8 +0E8h];

	test	r10,r10;
	push	mapJustifyProc4ReturnAddress;
	ret;
mapJustifyProc4 ENDP

END