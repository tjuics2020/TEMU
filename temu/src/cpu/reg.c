#include "temu.h"
#include <stdlib.h>
#include <string.h>

CPU_state cpu;

const char *regfile[] = {"$zero", "$at", "$v0", "v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};  //???v1寄存器是不是出错了

void display_reg() {
        int i;
        for(i = 0; i < 32; i ++) {
                printf("%s\t\t0x%08x\t\t%d\n", regfile[i], cpu.gpr[i]._32, cpu.gpr[i]._32);
        }

        printf("%s\t\t0x%08x\t\t%d\n", "$pc", cpu.pc, cpu.pc);
}

int getregData(char *name,bool* success) {
        int i;
        *success = false;
        for(i=0; i<32;i++){
               if(strcmp(name,regfile[i])==0){
                   *success = true;
                   return cpu.gpr[i]._32;
               }
               else if(strcmp(name,"$pc")==0){
                   *success = true;
                   return cpu.pc;
               }
        }
        
        return 0;
}
