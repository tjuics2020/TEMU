#include "trap.h"
   .set noat
   .globl main
   .text
main:
   addi  $s0,$zero,0x10                #s0 = 0x10
   addi  $s1,$zero,0x110               #s1 = 0x110
   addi  $s2,$zero,20                   #s2 = 20
   andi  $s2,$s2, 0xf           #s2 = 4
   li  $s3,0xf2345678           #s3 = 0x12345678
   add  $t0,$s0,$s0             #t0 = 0x20
   addi $t1,$s0,0x10            #t1 = 0x20
   addu $t2,$s0,$s0             #t2 = 0x20
   addiu $t3,$s0,0x10           #t3 = 0x20
   sub $t4,$s1,$s0              #t4 = 0x100
   subu $t5,$s1,$s0             #t5 = 0x100
   sw $s3, 1000($s2)            #0x12345678存到地址1004中
   sb $s3, 1004($s2)            #0x78存到地址1008中
   sh $s3, 1008($s2)            #0x5678存到地址1012中
   lb $s4, 1000($s2)            #$s4 = 0x78
   lh $s5, 1000($s2)            #$s5 = 0x5678
   lw $s6, 1000($s2)            #$s6 = 0x12345678
   lbu $s7, 1000($s2)           #s7 = 0x78  //以下两个没有测试lbu和lb、lhu和lh的差别
   lhu $a0, 1000($s2)           #a0 = 0x5678     
   #addi $s6,$s6,0x0
   #li  $s0,0xffffffff
   sltu $v0, $zero,$s3           #v0 = 1
   slt $v0, $zero,$s3           #v0 = 0
   li $s0, 0x12345678           #s0 = 0x12345678
   nor $t0, $s0, $s3            #t0 = 0xdcba987
   xor $t1, $s0, $s3            #t1 = 0xE0000000
   sll $t2, $s3, 4              #t2 = 0x23456780
   sllv $t3, $s3, $s2           #t3 = 0x23456780
   sra $t4, $s3, 4              #t4 = 0xff234567
   srav $t5, $s3, $s2           #t5 = 0xff234567
   srl $t6, $s3, 4              #t6 = 0x0f234567
   srlv $t7, $s3, $s2           #t7 = 0x0f234567
   multu $s0, $s3               #hi = 0x11393285 lo = 0x1df4d840
   li $s0, 0xffff0000
   addi $s0, $s0, 0xffff
   multu $s0, $s0               #hi = 0xFFFFFFFE lo = 0x00000001
   mult $s0, $s0                #hi = 0x0 lo = 0x1
   mult $s0, $s3                #????
   
   HIT_GOOD_TRAP		#stop temu
