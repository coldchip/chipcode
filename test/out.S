printf
	movdr r0 r5
	mov @0 r0
	getsp r5
	call dbgregs
main
	getsp r5
	call domath
domath
	push #0
	push #1
	push #0
	push #10000
	push #0
	jmp .L0
.L0
	push #1
	push #1
	pop r0
	pop r3
	cmp r0 r3
	jne .L1
	getsp r6
	jmp .L2
.L2
	push #999999999
	push @16
	pop r0
	pop r1
	cmp r0 r1
	setlt r0
	push r0
	push #1
	pop r0
	pop r3
	cmp r0 r3
	jne .L3
	getsp r6
	push #3000
	push @16
	pop r0
	pop r1
	add r0 r1
	push r0
	pop r0
	mov @16 r0
	setsp r6
	jmp .L2
.L3
	push #0
	pop r0
	mov @16 r0
	push @4
	push @0
	pop r0
	pop r1
	add r0 r1
	push r0
	pop r0
	mov @8 r0
	push @4
	pop r0
	mov @0 r0
	push @8
	pop r0
	mov @4 r0
	push @12
	push @0
	pop r0
	pop r1
	cmp r0 r1
	setgt r0
	push r0
	push #1
	pop r0
	pop r3
	cmp r0 r3
	je .L4
	jmp .L5
.L4
	getsp r6
	getsp r5
	call domath
	setsp r6
	jmp .L6
.L5
	getsp r6
	getsp r5
	push @0
	call printf
	setsp r6
	jmp .L6
.L6
	setsp r6
	jmp .L0
.L1
	getsp r5
	call printf
