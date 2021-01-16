printf
	movdr r0 r5
	mov @0 r0
	getsp r5
	call dbgregs
main
	push #0
	push #1
	push #0
	push #1000
	push #0
	jmp .L0
.L0
	push @12
	push @0
	pop r0
	pop r1
	cmp r0 r1
	setlt r0
	push r0
	push #1
	pop r0
	pop r3
	cmp r0 r3
	jne .L1
	jmp .L2
.L2
	push #99999999
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
	push #3000
	push @16
	pop r0
	pop r1
	add r0 r1
	push r0
	pop r0
	mov @16 r0
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
	getsp r5
	call dbgregs
	getsp r5
	push @12
	call printf
	jmp .L0
.L1
	getsp r5
	call printf
