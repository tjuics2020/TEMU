#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"

typedef struct watchpoint {
	int NO;
	struct watchpoint *next;

	/* TODO: Add more members if necessary */
        int isEmpty;
        int data;
        char expr[256];           //一条表达式的长度
} WP;

#endif
