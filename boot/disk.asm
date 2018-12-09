

disk_load:
	push dx

	mov ah, 0x02 	; BIOS read sector function
	mov al, dh		; read number of sector specified in dh
	mov ch, 0x00	; cylinder 0 (count from 0)
	mov dh, 0x00	; head 0 (count from 0)
	mov cl, 0x02	; read from sector 2 (count from 1)

	int 0x13

	jc disk_error

	pop dx
	cmp dh, al
	jne disk_error
	ret

disk_error:
	mov bx, DISK_ERROR_MSG
	call print
	jmp $


DISK_ERROR_MSG db "Disk read error!", 0