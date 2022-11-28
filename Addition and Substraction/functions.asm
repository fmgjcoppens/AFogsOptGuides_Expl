.data
avx2_dvec1 ymmword 1.0, 2.0, 3.0, 4.0
avx2_dvec2 ymmword 5.0, 6.0, 7.0, 8.0

.code
add_double_avx2 proc
	vmovapd ymm0, ymmword ptr [avx2_dvec1]
	vmovapd ymm1, ymmword ptr [avx2_dvec2]

	vaddpd ymm0, ymm0, ymm1

	ret
add_double_avx2 endp
end
