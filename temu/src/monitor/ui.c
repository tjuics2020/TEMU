#include "monitor.h"
#include "temu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void cpu_exec(uint32_t);

void display_reg();

void display_wp();

void set_a_new_wp(char *);

void free_wp_i(int );

uint32_t expr(char *, bool *);

/* We use the `readline' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(temu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

static int cmd_c(char *args) {
	cpu_exec(-1);         //????为什么是-1
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}

static int cmd_si(char *args) {
        char *arg = strtok(NULL, " ");
        int i=1;
        if(arg)
          i=*arg-'0';
        if( i )
          cpu_exec(i);
        else 
          cpu_exec(1);

        return 0;
}

static int cmd_d(char *args){   //删除监视点
        char *arg=strtok(NULL," ");
        int i=0;
        if(arg){
          i=*arg-'0';
          free_wp_i(i);
          printf("delete %d watch point.\n",i);
          return 0;
        }  
        return 1;
}

static int cmd_p(char *args){
        //printf("cmd_p:args=%s\n",args);
        bool success;
        int result=expr(args, &success);
        if( success ){
           printf("%d\n",result);     //打印结果
        }
        else{
           printf("unkown expression\n");
        }
        return 0;
}

static int cmd_w(char *args){
        set_a_new_wp(args);
        return 0;
}

static int cmd_x(char *args){
        char *pN=strtok(NULL," ");
        char *pAdd = strtok(NULL," ");
        //printf("cmd_x:arg=%s pAdd=%s\n",pN,pAdd);
        bool success;
        success = true;
        int add = expr(pAdd,&success);
        if( success==false ){ printf("expression error!\n");return 0; }
        int n = atoi(pN);
        if( n == 0) { printf("N error!\n");return 0; }
        //printf("cmd_x:n=%d add=%d\n",n,add);
        int data = 0;
        for(int i=0; i<n; i++ ){
           data = mem_read(add+i*4,4);
           if( i%4 == 0&& i!=0 ) printf("\n");
           printf("%#8x  ",data);
        }
        printf("\n");
        
        return 0;
}

static int cmd_info(char *args);

static int cmd_help(char *args);

static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
	{ "q", "Exit TEMU", cmd_q },
        { "si","The program will pause after N instructions are executed step by step.the default N is 1", cmd_si },
        { "info","Print register status.Print watch point information", cmd_info },
        { "d", "Delte the watch point.",cmd_d},
        { "p", "calculate the expression.",cmd_p},
        { "w","set a watch point",cmd_w},
        { "x", "print memory", cmd_x}
	/* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}

static int cmd_info(char *args){ //打印寄存器信息和监视点信息
        char *arg = strtok(NULL," ");
        if(strcmp(arg,"r" )== 0 ){
                //打印寄存器
                display_reg();
        }
        else if( strcmp(arg,"w")==0 ){
                display_wp();
        }
        else{
                printf("Unknown subcmd '%s'\n",arg);
        }
        return 0;
}

void ui_mainloop() {
	while(1) {
		char *str = rl_gets();               //命令字符串起点地址
		char *str_end = str + strlen(str);   //命令字符串的终点地址

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		if(cmd == NULL) { continue; }

		/* treat the remaining string as the arguments,
		 * which may need further parsing
		 */
		char *args = cmd + strlen(cmd) + 1;
		if(args >= str_end) {
			args = NULL;
		}

		int i;
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
				if(cmd_table[i].handler(args) < 0) { return; }
				break;
			}
		}

		if(i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
	}
}
