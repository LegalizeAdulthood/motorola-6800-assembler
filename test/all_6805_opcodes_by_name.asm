	cpu cmos
	org $E000


* =-=-=-=-= ADC - ADd with Carry =-=-=-=-=
	adc #$A9
	adc $B9
	adc $C9C9
	adc $D9D9,x
	adc $E9,x
	adc ,x
* =-=-=-=-= ADD - ADDition =-=-=-=-=
	add #$AB
	add $BB
	add $CBCB
	add $DBDB,x
	add $EB,x
	add ,x
* =-=-=-=-= AND - logical AND =-=-=-=-=
	and #$A4
	and $B4
	and $C4C4
	and $D4D4,x
	and $E4,x
	and ,x
* =-=-=-=-= ASL (same as LSL) =-=-=-=-=
	asl $BA
	asla
	aslx
	asl $EA,x
	asl ,x
* =-=-=-=-= ASR =-=-=-=-=
	asr $37
	asra
	asrx
	asr $67,x
	asr ,x
* =-=-=-=-= BCC (same as BHS) - Branch if Carry is Clear =-=-=-=-=
	bcc *+$26
* =-=-=-=-= BCLR - Bit CLeaR =-=-=-=-=
	bclr 0,$11
	bclr 1,$13
	bclr 2,$15
	bclr 3,$17
	bclr 4,$19
	bclr 5,$1B
	bclr 6,$1D
	bclr 7,$1F
* =-=-=-=-= BCS (same as BLO) - Branch if Carry is Set =-=-=-=-=
	bcs *+$27
* =-=-=-=-= BEQ - Branch of EQual =-=-=-=-=
	beq *+$29
* =-=-=-=-= BHCC - Branch if Half Carry is Clear =-=-=-=-=
	bhcc *+$2A
* =-=-=-=-= BHCS - Branch if Half Carry is Set =-=-=-=-=
	bhcs *+$2B
* =-=-=-=-= BHI - Branch if HIgher =-=-=-=-=
	bhi *+$24
* =-=-=-=-= BHS (same as BCC) - Branch if Higher or Same =-=-=-=-=
	bhs *+$26
* =-=-=-=-= BIH =-=-=-=-=
	bih *+$31
* =-=-=-=-= BIL =-=-=-=-=
	bil *+$30
* =-=-=-=-= BIT - BIt Test and compare =-=-=-=-=
	bit #$A5
	bit $B5
	bit $C5C5
	bit $D5D5,x
	bit $E5,x
	bit ,x
* =-=-=-=-= BLO (same as BCS) - Branch if LOwer =-=-=-=-=
	blo *+$27
* =-=-=-=-= BLS - Branch if Less or Same =-=-=-=-=
	bls *+$25
* =-=-=-=-= BMC =-=-=-=-=
	bmc *+$2E
* =-=-=-=-= BMI =-=-=-=-=
	bmi *+$2D
* =-=-=-=-= BMS =-=-=-=-=
	bms *+$2F
* =-=-=-=-= BNE - Branch if Not Equal =-=-=-=-=
	bne *+$28
* =-=-=-=-= BPL - Branch if PLus =-=-=-=-=
	bpl *+$2C
* =-=-=-=-= BRA - BRAnch =-=-=-=-=
	bra *+$22
* =-=-=-=-= BRCLR - BRanch if bit is CLeaR =-=-=-=-=
	brclr 0,$01,*+$4
	brclr 1,$03,*+$6
	brclr 2,$05,*+$8
	brclr 3,$07,*+$A
	brclr 4,$09,*+$C
	brclr 5,$0B,*+$E
	brclr 6,$0D,*+$10
	brclr 7,$0F,*+$12
* =-=-=-=-= BRN - Branch Never (basicly a 2 or 3 byte NOP) =-=-=-=-=
	brn *+$23
* =-=-=-=-= BRSET - BRanch if bit is SET =-=-=-=-=
	brset 0,$00,*+$3
	brset 1,$02,*+$5
	brset 2,$04,*+$7
	brset 3,$06,*+$9
	brset 4,$08,*+$B
	brset 5,$0A,*+$D
	brset 6,$0C,*+$F
	brset 7,$0E,*+$11
* =-=-=-=-= BSET - Bit SET =-=-=-=-=
	bset 0,$10
	bset 1,$12
	bset 2,$14
	bset 3,$16
	bset 4,$18
	bset 5,$1A
	bset 6,$1C
	bset 7,$1E
* =-=-=-=-= BSR - Branch to SubRoutine =-=-=-=-=
	bsr *-$51
* =-=-=-=-= CLC =-=-=-=-=
	clc
* =-=-=-=-= CLI =-=-=-=-=
	cli
* =-=-=-=-= CLR - CLeaR =-=-=-=-=
	clr $3F
	clra
	clrx
	clr $6F,x
	clr ,x
* =-=-=-=-= CMP - CoMPare =-=-=-=-=
	cmp #$A1
	cmp $B1
	cmp $C1C1
	cmp $D1D1,x
	cmp $E1,x
	cmp ,x
* =-=-=-=-= CMPX - CoMPare with X =-=-=-=-=
	cmpx #$A3
	cmpx $B3
	cmpx $C3C3
	cmpx $D3D3,x
	cmpx $E3,x
	cmpx ,x
* =-=-=-=-= COM - COMpliment =-=-=-=-=
	com $3F
	coma
	comx
	com $6F,x
	com ,x
* =-=-=-=-= CPX - ComPare with X =-=-=-=-=
	cpx #$A3
	cpx $B3
	cpx $C3C3
	cpx $D3D3,x
	cpx $E3,x
	cpx ,x
* =-=-=-=-= DEC - DECriment =-=-=-=-=
	dec $3A
	deca
	decx
	dec $6A,x
	dec ,x
* =-=-=-=-= EOR - Exclusive OR =-=-=-=-=
	eor #$A8
	eor $B8
	eor $C8C8
	eor $D8D8,x
	eor $E8,x
	eor ,x
* =-=-=-=-= INC =-=-=-=-=
	inc $3C
	inca
	incx
	inc $6C,x
	inc ,x
* =-=-=-=-= JMP - JuMP to address =-=-=-=-=
	jmp $BC
	jmp $CCCC
	jmp $DCDC,x
	jmp $EC,x
	jmp ,x
* =-=-=-=-= JSR - Jump to SubRoutine =-=-=-=-=
	jsr $BD
	jsr $CDCD
	jsr $DDDD,x
	jsr $ED,x
	jsr ,x
* =-=-=-=-= LDA - LoaD register A =-=-=-=-=
	lda #$A6
	lda $B6
	lda $C6C6
	lda $D6D6,x
	lda $E6,x
	lda ,x
* =-=-=-=-= LDX - LoaD register X =-=-=-=-=
	ldx #$AE
	ldx $BE
	ldx $CECE
	ldx $DEDE,x
	ldx $EE,x
	ldx ,x
* =-=-=-=-= LSL (same as ASL) =-=-=-=-=
	lsl $38
	lsra
	lsrx
	lsl $68,x
	lsl ,x
* =-=-=-=-= LSR =-=-=-=-=
	lsr $34
	lsra
	lsrx
	lsr $64,x
	lsr ,x
* =-=-=-=-= NEG =-=-=-=-=
	neg $30
	nega
	negx
	neg $60,x
	neg ,x
* =-=-=-=-= NOP =-=-=-=-=
	nop
* =-=-=-=-= ORA - OR with register A =-=-=-=-=
	ora #$AA
	ora $BA
	ora $CACA
	ora $DADA,x
	ora $EA,x
	ora ,x
* =-=-=-=-= ROL =-=-=-=-=
	rol $39
	rola
	rolx
	rol $69,x
	rol ,x
* =-=-=-=-= ROR =-=-=-=-=
	ror $36
	rora
	rorx
	ror $66,x
	ror ,x
* =-=-=-=-= RSP - Reset Stack Pointer =-=-=-=-=
	rsp
* =-=-=-=-= RTI - ReTurn from Interrupt =-=-=-=-=
	rti
* =-=-=-=-= RTS - ReTurn from Subroutine =-=-=-=-=
	rts
* =-=-=-=-= SBC - SuBtract with Carry =-=-=-=-=
	sbc #$A2
	sbc $B2
	sbc $C2C2
	sbc $D2D2,x
	sbc $E2,x
	sbc ,x
* =-=-=-=-= SEC =-=-=-=-=
	sec
* =-=-=-=-= SEI =-=-=-=-=
	sei
* =-=-=-=-= STA - STore register A =-=-=-=-=
	sta $B7
	sta $C7C7
	sta $D7D7,x
	sta $E7,x
	sta ,x
* =-=-=-=-= STOP =-=-=-=-=
	stop
* =-=-=-=-= STX - STore register X =-=-=-=-=
	stx $BF
	stx $CFCF
	stx $DFDF,x
	stx $EF,x
	stx ,x
* =-=-=-=-= SUB - SUBtract =-=-=-=-=
	sub #$A0
	sub $B0
	sub $C0C0
	sub $D0D0,x
	sub $E0,x
	sub ,x
* =-=-=-=-= SWI - SoftWare Interrupt =-=-=-=-=
	swi
* =-=-=-=-= TAX - Transfer A to X =-=-=-=-=
	tax
* =-=-=-=-= TST - TeST =-=-=-=-=
	tst $3E
	tsta
	tstx
	tst $6E,x
	tst ,x
* =-=-=-=-= TXA - Transfer X to A =-=-=-=-=
	txa
* =-=-=-=-= WAIT =-=-=-=-=
	wait
