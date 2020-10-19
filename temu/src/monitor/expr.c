#include "temu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>
//#include <stdlib.h>
//#include <stdio.h>

enum {
	NOTYPE = 256, EQ,NEQ,REG,PAR,SUB,MULT,DIV,NUM

	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE},				// spaces
	{"\\+", '+'},					// plus
	{"==", EQ},					// equal
        {"\\!=",NEQ},                                   // not equal
        {"\\$[a-z][0-9]",REG},                              // register
        {"\\$[a-z]*",REG},                              // register
        {"\\(.*\\)",PAR},                               // parentheses
        {"\\-",SUB},                                    // sub      
        {"\\*",MULT},                                   // multiplication
        {"\\/",DIV},                                    // division     只支持整数除法，不四舍五入
        {"[0-9]*",NUM}                                  // number

};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

int getregData(char *,bool *);

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			Assert(ret == 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[64];   //增加到64个
int nr_token;
int init_data;      

void strremove(char *des,char *src, int len, int begin){
    for(int i=0; i<len; i++){
       des[i]=src[i+begin];
    }
    des[len] ='\0';
}

int getstrlen(char *str){
     int i=0;
     while(str[i+1] != '\0'){i++;}
     return i+1;
}

void ints_to_chars(int num,char *des){
     char tempstr[32];
     sprintf(tempstr,"%d",num);
     int len = getstrlen(tempstr);
     strremove(des,tempstr,len,0);
     des[len]='\0';
}



static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = init_data;  //初始值

	while(e[position] != '\0') {
		/* Try all rules one by one. */
                
		for(i = 0; i < NR_REGEX; i ++) {
                        
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);                  
                                int begin = position;
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array `tokens'. For certain types
				 * of tokens, some extra actions should be performed.
				 */
                                
                                
				switch(rules[i].token_type) {
					/*case EQ:
                                             break;
                                        case REG:
                                             char name[32];
                                             strremove(name,e,substr_len,begin);
                                             int num = getregData(name);
                                             itoa(num,name,10);        //将数字变成char数组
                                             tokens[nr_token].type = NUM;
                                             strremove( tokens[nr_token].str,name,getstrlen(name),0);
                                             nr_token++;
                                             break;*/
                                        case NOTYPE:
                                             break;
                                        default:
                                             tokens[nr_token].type = rules[i].token_type;
                                             strremove( tokens[nr_token].str,e,substr_len,begin);
                                             nr_token++;
                                             break;//panic("swicth:please implement me");
				}
                                
				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true; 
}
void cal_onetoken(int , bool*);
int cal_tokens(int, int, bool*);

uint32_t expr(char *e, bool *success) {
	init_data = 0;
        if(!make_token(e)) {
		*success = false;
		return 0;
	}

	/* TODO: Insert codes to evaluate the expression. */
	//panic("expr:please implement me");
        printf("yes\n");
        
        for(int i=0;i<nr_token;i++){
           printf("first:%s\n", tokens[i].str);
        }
        
        int result;
        result = cal_tokens(0,nr_token,success);
        
        if( !(*success) ) return 0;
        
        for(int i=0;i<nr_token;i++){
           printf("second:%s\n", tokens[i].str);
        }
	return result;
}



int cal_tokens(int begin,int end,bool *success){//计算多个token式子的值    begin是需要计算的Token数组里的第一个的位置，end是最后一个的位置
        int sum = 123;
        for(int i=begin;i<end;i++){
             cal_onetoken(i,success);
             if( !(*success) ) return 0;
        }
        
        return sum;
}

void cal_onetoken(int pos,bool *success){ //计算某一个token的值   并且将数字储存到tokens[pos].str中
        *success = true;
        int data = 0 ;
        if(tokens[pos].type == REG ){  //寄存器
             data = getregData(tokens[pos].str,success);
             if( !(*success) ) return;
             tokens[pos].type = NUM;
             ints_to_chars(data,tokens[pos].str);
             //return data;
        }
        else if(tokens[pos].type==PAR){
             char temp[32];
             int len = getstrlen(tokens[pos].str);
             strremove(temp,tokens[pos].str,len-2,1); //去掉括号
             printf("\n%d\n\n",len );
             bool is;
             int pre_init_data = init_data;
             int pre_nr_token = nr_token;
             init_data = nr_token;
             is = make_token(temp);               //分解括号里的token项
             printf("这次分解，增加了%d个token\n",nr_token-init_data);
             if( !is ){ *success = false;return;} //计算失败
             data = cal_tokens(init_data,nr_token,&is);     
             if( !is ){ *success = false;return;}
             tokens[pos].type = NUM;
             ints_to_chars(data,tokens[pos].str);
             init_data = pre_init_data;
             nr_token = pre_nr_token;
        }
        
        /*else if( tokens[pos].type == '+'){
             if( pos<1 || pos==nr_token-1 ){
                   *success = false;
                   return 0; 
             }
              
             
        }*/
        
}

