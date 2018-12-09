
print_string:
	mov ah, 0x0e ; set tty mode


start_of_loop:

	mov al, [bx]
	int 0x10

	add bx, 1

	cmp byte [bx], byte 0
	je end_loop

	jmp start_of_loop


end_loop:
	ret