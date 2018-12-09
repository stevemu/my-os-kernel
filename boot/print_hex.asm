
print_hex:
	mov ax, dx ; store value in a and manupilate that
	mov bx, HEX_OUT + 5 ; the current byte manupilating in the string; start from the last char
	mov cx, 4 ; how many bits the next time it should shift

hex_loop:
	and ax, 0x000f

	cmp bx, HEX_OUT + 1
	je end


	cmp al, 9
	jle less_equal_9
	
	add al, 87 ; if bigger than 9
	mov [bx], al ; store the ascii value in the current string char address

	mov ax, dx ; reset the ax with dx
	shr ax, cl ; shift ax by the value in cl
	add cl, 4 ; increase cl for use next time
	sub bx, 1 ; decrease bx for use next time

	jmp hex_loop

end:
	mov bx, HEX_OUT
	call print

	ret

less_equal_9:
	add al, 48
	mov [bx], al ; store the ascii value in the current string char address

	mov ax, dx ; reset the ax with dx
	shr ax, cl ; shift ax by the value in cl
	add cl, 4 ; increase cl for use next time
	sub bx, 1 ; decrease bx for use next time

	jmp start

HEX_OUT:
	db '0x0000', 0
