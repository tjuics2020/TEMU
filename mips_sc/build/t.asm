
build/t:     file format elf32-tradlittlemips
build/t


Disassembly of section .text:

00000000 <main>:
   0:	20100010 	addi	s0,zero,16
   4:	20110110 	addi	s1,zero,272
   8:	20120004 	addi	s2,zero,4
   c:	3c13f234 	lui	s3,0xf234
  10:	36735678 	ori	s3,s3,0x5678
  14:	02104020 	add	t0,s0,s0
  18:	22090010 	addi	t1,s0,16
  1c:	02105021 	addu	t2,s0,s0
  20:	260b0010 	addiu	t3,s0,16
  24:	02306022 	sub	t4,s1,s0
  28:	02306823 	subu	t5,s1,s0
  2c:	ae5303e8 	sw	s3,1000(s2)
  30:	a25303ec 	sb	s3,1004(s2)
  34:	a65303f0 	sh	s3,1008(s2)
  38:	825403e8 	lb	s4,1000(s2)
  3c:	865503e8 	lh	s5,1000(s2)
  40:	8e5603e8 	lw	s6,1000(s2)
  44:	0013102b 	sltu	v0,zero,s3
  48:	0013102a 	slt	v0,zero,s3
  4c:	3c101234 	lui	s0,0x1234
  50:	36105678 	ori	s0,s0,0x5678
  54:	02134027 	nor	t0,s0,s3
  58:	02134826 	xor	t1,s0,s3
  5c:	00135100 	sll	t2,s3,0x4
  60:	02535804 	sllv	t3,s3,s2
  64:	00136103 	sra	t4,s3,0x4
  68:	02536807 	srav	t5,s3,s2
  6c:	00137102 	srl	t6,s3,0x4
  70:	02537806 	srlv	t7,s3,s2
  74:	02130019 	multu	s0,s3
  78:	3c10ffff 	lui	s0,0xffff
  7c:	2210ffff 	addi	s0,s0,-1
  80:	02100019 	multu	s0,s0
  84:	4a000000 	c2	0x0

Disassembly of section .reginfo:

00000000 <.reginfo>:
   0:	007fff04 	0x7fff04
	...
