  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #

  .data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "hello"
	.text

.global delay
.global time2string
.global enable_interrupt

hexasc:
	andi	$a0, $a0, 0xF
	addi	$t3, $zero, 48
	slti	$t1, $a0, 10
	bne	$t1, $zero, alpha
	nop
	addi	$t3, $t3, 7

alpha:
	add	$t2, $a0, $t3
	move	$v0, $t2
	jr $ra
	nop

delay:
	PUSH $ra
	PUSH $s0
	PUSH $s1
	PUSH $s2

	add $s0, $zero, $a0

	while:
	  addi $t2, $zero, 1
	  slt $t1, $s0, $t2
	  bne $t1, $zero, done
	  nop
	  jal for
	  nop
	  addi $s0, $s0, -1
	  j while
	  nop
	done:

	POP $s2
	POP $s1
	POP $s0
	POP $ra
	jr $ra
	nop

for:	addi $s1, $zero, 0
	addi $s2, $zero, 16
	loop:
	  beq $s1, $s2, doneLoop
	  nop
	  addi $s1, $s1, 1
	  j loop
	  nop
	doneLoop:
	jr $ra
	nop


enable_interrupt:
   ei
   jr $ra
 	 nop

time2string:
	PUSH $ra
	PUSH $t0
	PUSH $s0
	PUSH $s1

	move	$s0, $a0
	move	$s1, $a1	# a1 is time value

	# Get first digit in minutes
	andi	$t0, $s1, 0xF000
	srl	$a0, $t0, 12
	jal	hexasc
	nop
	sb	$v0, 0($s0)

	# Get second digit in minutes
	andi	$t0, $s1, 0xF00
	srl	$a0, $t0, 8
	jal	hexasc
	nop
	sb	$v0, 1($s0)

	# Get first digit in seconds
	andi	$t0, $s1, 0xF0
	srl	$a0, $t0, 4
	jal	hexasc
	nop
	sb	$v0, 3($s0)

	# Get second digit in seconds
	andi	$t0, $s1, 0xF
	srl	$a0, $t0, 0
	jal	hexasc
	nop
	sb	$v0, 4($s0)

	# Add colon
	addi	$t0, $zero, 0x3a
	sb	$t0, 2($s0)

	POP $s1
	POP $s0
	POP $t0
	POP $ra
	jr	$ra
	nop
