#include "watchpoint.h"
#include "expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP];
static WP *head, *free_;

void init_wp_pool() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_pool[i].NO = i;
                wp_pool[i].isEmpty=1;
		wp_pool[i].next = &wp_pool[i + 1];
	}
	wp_pool[NR_WP - 1].next = NULL;

	//head = NULL;    //???更改
        head = wp_pool;
	free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

void display_wp(){
        WP *p;
        p = head;
        while( p != free_ ){
               if(!p->isEmpty){
                  //打印表达式的值
               }
               p = p->next;
        }
        printf("watchpoint.c:here print the watchponit!\n");
}
