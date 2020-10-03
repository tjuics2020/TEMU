#define HIT_GOOD_TRAP \
	addi $at, $zero, 0; \
	.byte 0xd6

#define HIT_BAD_TRAP \
	addi $at, $zero, 1; \
	.byte 0xd6
