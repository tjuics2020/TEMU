
build/t:     file format elf32-tradlittlemips
build/t


Disassembly of section .text:

00000000 <main>:
   0:	20100010 	addi	s0,zero,16
   4:	20110110 	addi	s1,zero,272
   8:	20120014 	addi	s2,zero,20
   c:	3252000f 	andi	s2,s2,0xf
  10:	3c13f234 	lui	s3,0xf234
  14:	36735678 	ori	s3,s3,0x5678
  18:	02104020 	add	t0,s0,s0
  1c:	22090010 	addi	t1,s0,16
  20:	02105021 	addu	t2,s0,s0
  24:	260b0010 	addiu	t3,s0,16
  28:	02306022 	sub	t4,s1,s0
  2c:	02306823 	subu	t5,s1,s0
  30:	ae5303e8 	sw	s3,1000(s2)
  34:	a25303ec 	sb	s3,1004(s2)
  38:	a65303f0 	sh	s3,1008(s2)
  3c:	825403e8 	lb	s4,1000(s2)
  40:	865503e8 	lh	s5,1000(s2)
  44:	8e5603e8 	lw	s6,1000(s2)
  48:	925703e8 	lbu	s7,1000(s2)
  4c:	964403e8 	lhu	a0,1000(s2)
  50:	0013102b 	sltu	v0,zero,s3
  54:	0013102a 	slt	v0,zero,s3
  58:	3c101234 	lui	s0,0x1234
  5c:	36105678 	ori	s0,s0,0x5678
  60:	02134027 	nor	t0,s0,s3
  64:	02134826 	xor	t1,s0,s3
  68:	00135100 	sll	t2,s3,0x4
  6c:	02535804 	sllv	t3,s3,s2
  70:	00136103 	sra	t4,s3,0x4
  74:	02536807 	srav	t5,s3,s2
  78:	00137102 	srl	t6,s3,0x4
  7c:	02537806 	srlv	t7,s3,s2
  80:	02130019 	multu	s0,s3
  84:	3c10ffff 	lui	s0,0xffff
  88:	2210ffff 	addi	s0,s0,-1
  8c:	02100019 	multu	s0,s0
  90:	02100018 	mult	s0,s0
  94:	02130018 	mult	s0,s3
  98:	4a000000 	c2	0x0

Disassembly of section .reginfo:

00000000 <.reginfo>:
   0:	00ffff14 	0xffff14
	...
