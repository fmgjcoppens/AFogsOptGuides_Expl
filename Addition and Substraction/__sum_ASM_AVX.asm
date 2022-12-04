.code

__sum_ASM_AVX proc
	push rbx
	vpxor ymm0, ymm0, ymm0 ; Zero the counters

	mov ebx, edx
	sar edx, 2 ; Divide the count by 4 for AVX
	jz SumResiduals ; If the

LoopHead:
	vaddpd ymm0, ymm0, ymmword ptr [rcx]

	add rcx, 32 ; Move to the next 4 doubles

	dec edx
	jnz LoopHead

	; Horizontal add 4 doubles in ymm0
	vhaddpd ymm0, ymm0, ymm0
	vperm2f128 ymm1, ymm0,ymm0, 1
	addpd xmm0, xmm1

SumResiduals:
	and ebx, 3
	jz Finished

ResidualsLoopHead:
	addsd xmm0, real8 ptr [rcx]
	add rcx, 8
	dec ebx
	jnz ResidualsLoopHead

Finished:
	pop rbx
	ret
__sum_ASM_AVX endp

end




