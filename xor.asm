use32		
	mov ecx, 0xfffffbff
	xor ecx, 0xffffffff ;0x1000
	
	mov ebx, 0xffffffdf
	xor ebx, 0xffffffff ;32
xor_m:
	mov eax, [esp+ebx]
	xor eax, 0xEEEEEEEE
	mov [esp+ebx], eax
	add ebx, 0x4
	loop xor_m
	
	