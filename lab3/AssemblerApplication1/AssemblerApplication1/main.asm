;
; AssemblerApplication1.asm
;
; Created: 2022-02-21 12:23:35
; Author : mrmrj
;


; Replace with your application code
#define DDRB 0x04
#define PORTB 0x05
#define LED2 2
#define STACK_H 0x3E
#define STACK_L 0x3D
#define N_ALLOC 40


start:
	rjmp end



defense_routine:
	push r28
	push r29
	in r28, STACK_L
	in r29, STACK_H
	sbiw Y, N_ALLOC
	out STACK_L, r28
	out STACK_H, r29
	ldi r19, 1
	ldi r20, 0
	ld r21, Y+
	loop:
		st Y+, r19
		st Y+, r20
		st Y+, r20
		st Y+, r20
		cpi r19, 10
		inc r19
		brne loop
	sbiw Y, N_ALLOC
	st -Y, r21
	ret

delay:
	ldi r19, 1
	ldi r18, 0
	loop0:
	ldi r16, 0
	ldi r17, 0
		loop1:
			ADD r16, r19
			cpi r16, 255
			brne loop1
			rjmp loop2
			loop2:
				ldi r16, 0
				ADD r17, r19
				cpi r17, 255
				brne loop1
				ADD r18, r19
				cpi r18, 5
				brne loop0
				rjmp end

ledon:
	ldi r18, (1 << LED2)
	in r17, DDRB
	or r17, r18
	out DDRB, r18
	in r17, PORTB
	or r17, r18
	out PORTB, r18

end:
	rjmp ledon
	rjmp end