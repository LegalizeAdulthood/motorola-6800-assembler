	cpu 6805
	.org $e000

;********** Single byte opcodes **********
;=-= Opcodes 0x =-=-=-=-=-=-=-=-=
	brset0 $00,*+3
	brclr0 $01,*+4
	brset1 $02,*+5
	brclr1 $03,*+6
	brset2 $04,*+7
	brclr2 $05,*+8
	brset3 $06,*+9
	brclr3 $07,*+10
	brset4 $08,*+11
	brclr4 $09,*+12
	brset5 $0A,*+13
	brclr5 $0B,*+14
	brset6 $0C,*+15
	brclr6 $0D,*+16
	brset7 $0E,*+17
	brclr7 $0F,*+18
;=-= Opcodes 0x =-=-=-=-=-=-=-=-=
	brset 0,$00,*+3
	brclr 0,$01,*+4
	brset 1,$02,*+5
	brclr 1,$03,*+6
	brset 2,$04,*+7
	brclr 2,$05,*+8
	brset 3,$06,*+9
	brclr 3,$07,*+10
	brset 4,$08,*+11
	brclr 4,$09,*+12
	brset 5,$0A,*+13
	brclr 5,$0B,*+14
	brset 6,$0C,*+15
	brclr 6,$0D,*+16
	brset 7,$0E,*+17
	brclr 7,$0F,*+18
;=-= Opcodes 1x =-=-=-=-=-=-=-=-=
	bset0 $10
	bclr0 $11
	bset1 $12
	bclr1 $13
	bset2 $14
	bclr2 $15
	bset3 $16
	bclr3 $17
	bset4 $18
	bclr4 $19
	bset5 $1A
	bclr5 $1B
	bset6 $1C
	bclr6 $1D
	bset7 $1E
	bclr7 $1F
;=-= Opcodes 1x =-=-=-=-=-=-=-=-=
	bset 0,$10
	bclr 0,$11
	bset 1,$12
	bclr 1,$13
	bset 2,$14
	bclr 2,$15
	bset 3,$16
	bclr 3,$17
	bset 4,$18
	bclr 4,$19
	bset 5,$1A
	bclr 5,$1B
	bset 6,$1C
	bclr 6,$1D
	bset 7,$1E
	bclr 7,$1F
;=-= Opcodes 2x =-=-=-=-=-=-=-=-=
label3:	bra *+$22
	brn *+$23
	bhi *+$24
	bls *+$25
	bcc *+$26
	bcs *+$27 ; same as blo
	blo *+$27 ; same as bcs
	bne *+$28
	beq *+$29
	bhcc *+$2A
	bhcs *+$2B
	bpl *+$2C
	bmi *+$2D
	bmc *+$2E
	bms *+$2F
	bil *+$30
	bih *+$31
;=-= Opcodes 3x =-=-=-=-=-=-=-=-=
	neg $30
	com $33
	lsr $34
	ror $36
	asr $37
	asl $38 ; same as lsl
	lsl $38 ; same as asl
	rol $39
	dec $3A
	inc $3C
	tst $3D
	clr $3F
;=-= Opcodes 4x =-=-=-=-=-=-=-=-=
	nega
	coma
	mul
	lsra
	rora
	asra
	asla ; same as lsla
	lsla ; same as asla
	rola
	deca
	inca
	tsta
	clra
;=-= Opcodes 5x =-=-=-=-=-=-=-=-=
	negx
	comx
	lsrx
	rorx
	asrx
	aslx ; same as lslx
	lslx ; same as aslx
	rolx
	decx
	incx
	tstx
	clrx
;=-= Opcodes 6x =-=-=-=-=-=-=-=-=
	neg $60,x
	com $63,x
	lsr $64,x
	ror $66,x
	asr $67,x
	asl $68,x ; same as lsl
	lsl $68,x ; same as asl
	rol $69,x
	dec $6A,x
	inc $6C,x
	tst $6D,x
	clr $6F,x
;=-= Opcodes 7x =-=-=-=-=-=-=-=-=
	neg ,x
	com ,x
	lsr ,x
	ror ,x
	asr ,x
	asl ,x ; same as lsl
	lsl ,x ; same as asl
	rol ,x
	dec ,x
	inc ,x
	tst ,x
	clr ,x
;=-= Opcodes 8x =-=-=-=-=-=-=-=-=
	rti
	rts
	swi
	stop
	wait
;=-= Opcodes 9x =-=-=-=-=-=-=-=-=
	tax
	tfr a,x
	clc
	sec
	cli
	sei
	rsp
	nop
	tsa
	tfr s,a
	txa
	tfr x,a
;=-= Opcodes Ax =-=-=-=-=-=-=-=-=
label4:	sub #$A0
	cmp #$A1
	sbc #$A2
	cpx #$A3
	and #$A4
	bit #$A5
	lda #$A6
	eor #$A8
	adc #$A9
	ora #$AA
	add #$AB
	bsr label4
	ldx #$AE
;=-= Opcodes Bx =-=-=-=-=-=-=-=-=
	sub $B0
	cmp $B1
	sbc $B2
	cpx $B3
	and $B4
	bit $B5
	lda $B6
	sta $B7
	eor $B8
	adc $B9
	ora $BA
	add $BB
	jmp $BC
	jsr $BD
	ldx $BE
	stx $BF
;=-= Opcodes Cx =-=-=-=-=-=-=-=-=
	sub $C0C0
	cmp $C1C1
	sbc $C2C2
	cpx $C3C3
	and $C4C4
	bit $C5C5
	lda $C6C6
	sta $C7C7
	eor $C8C8
	adc $C9C9
	ora $CACA
	add $CBCB
	jmp $CCCC
	jsr $CDCD
	ldx $CECE
	stx $CFCF
;=-= Opcodes Dx =-=-=-=-=-=-=-=-=
	sub $D0D0,x
	cmp $D1D1,x
	sbc $D2D2,x
	cpx $D3D3,x
	and $D4D4,x
	bit $D5D5,x
	lda $D6D6,x
	sta $D7D7,x
	eor $D8D8,x
	adc $D9D9,x
	ora $DADA,x
	add $DBDB,x
	jmp $DCDC,x
	jsr $DDDD,x
	ldx $DEDE,x
	stx $DFDF,x
;=-= Opcodes Ex =-=-=-=-=-=-=-=-=
	sub $E0,x
	cmp $E1,x
	sbc $E2,x
	cpx $E3,x
	and $E4,x
	bit $E5,x
	lda $E6,x
	sta $E7,x
	eor $E8,x
	adc $E9,x
	ora $EA,x
	add $EB,x
	jmp $EC,x
	jsr $ED,x
	ldx $EE,x
	stx $EF,x
;=-= Opcodes Fx =-=-=-=-=-=-=-=-=
	sub ,x
	cmp ,x
	sbc ,x
	cpx ,x
	and ,x
	bit ,x
	lda ,x
	sta ,x
	eor ,x
	adc ,x
	ora ,x
	add ,x
	jmp ,x
	jsr ,x
	ldx ,x
	stx ,x
