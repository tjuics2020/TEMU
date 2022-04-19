#include "watchpoint.h"
#include "expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP];
static WP *head, *free_;

WP* new_wp();
void free_wp(WP *);
void setexpr(WP *,char *);
int getstrlen(char *);
void strremove(char *des,char *src, int len, int begin);

void free_wp_i(int);

uint32_t expr(char *, bool *);

int checkWatchpoints();

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
        printf("num    what\n");
        while( p != free_ ){
               if(!p->isEmpty){
                  //打印表达式的值
                   printf("%-5d  %s\n",p->NO,p->expr);
               }
               p = p->next;
        }

        //printf("watchpoint.c:here print the watchponit!\n");
}

void set_a_new_wp(char *exp){
        WP *wp = new_wp();
        if(wp==NULL){
             printf("no enough space to set watch point.\n");
             return;
        }
        
        setexpr(wp,exp);
        
}

WP* new_wp(){
        /*if(head == NULL){
               head = wp_pool;
        }*/
        if( free_ == NULL) return NULL;//没有空位
        WP *p = free_;
        free_ = free_->next;
        
        return p;
}

void setexpr(WP *wp,char *exp){
        int len = getstrlen(exp);
        if(len>256){
            printf("expression is too long!\n");
            return;  
        }
        //计算表达式的值并且储存在结构体的data中
        bool success;
        success = true;
        int data = expr(exp,&success);
        if( success==false ){ printf("expression error!\n");return;}
        wp->data = data;
        strremove(wp->expr,exp,len,0);
        wp->isEmpty = 0;
}

void free_wp(WP *wp){
        wp->isEmpty = 1;
}

void free_all(){
        for(int i=0;i<NR_WP; i++ ){
            head[i].isEmpty=1;
        }
        free_=head;
}

void free_wp_i(int i){
        free_wp(&head[i]);
}

int checkWatchpoints(){
        WP *p;
        p = head;
        int flag = 0;
        while( p != free_ ){
               if(!p->isEmpty){
                  bool success;
                  success = true;
                  int newdata = expr(p->expr,&success);
                  if(p->data != newdata ){
                     printf("watch points(num:%-3d expr:%s):\nthe old data:%d\nthe new data:%d\n",p->NO,p->expr,p->data,newdata);
                     p->data = newdata;
                     flag = 1;
                  }
               }
               p = p->next;
        }
        
        return flag;
}
