#include "helper.h"
#include "monitor.h"
#include "reg.h"

extern uint32_t instr;
extern char assembly[80];
uint32_t mem_read(uint32_t ,size_t);

/* decode I-type instrucion with unsigned immediate */
static void decode_imm_type(uint32_t instr) {

	op_src1->type = OP_TYPE_REG;
	op_src1->reg = (instr & RS_MASK) >> (RT_SIZE + IMM_SIZE);
	op_src1->val = reg_w(op_src1->reg);
	
	op_src2->type = OP_TYPE_IMM;
	op_src2->imm = instr & IMM_MASK;
	op_src2->val = op_src2->imm;

	op_dest->type = OP_TYPE_REG;
	op_dest->reg = (instr & RT_MASK) >> (IMM_SIZE);
}

make_helper(lui) {

	decode_imm_type(instr);
	reg_w(op_dest->reg) = (op_src2->val << 16);
	sprintf(assembly, "lui   %s,   0x%04x", REG_NAME(op_dest->reg), op_src2->imm);
}

make_helper(ori) {

	decode_imm_type(instr);
	reg_w(op_dest->reg) = op_src1->val | op_src2->val;
	sprintf(assembly, "ori   %s,   %s,   0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->imm);
        //printf("here!:%s\n",REG_NAME(op_sr->reg));
}


make_helper(sw){
        decode_imm_type(instr);
        mem_write(op_src1->val+op_src2->val,4,reg_w(op_dest->reg));
        //printf("sw:yes!  %d\n",op_src1->val+op_src2->val);
        sprintf(assembly,"sw    %s,   %d(%s)",REG_NAME(op_dest->reg),op_src2->imm,REG_NAME(op_src1->reg));
}
make_helper(sb){
        decode_imm_type(instr);
        mem_write(op_src1->val+op_src2->val,1,reg_b(op_dest->reg));
        //printf("sb:yes!\n");
        sprintf(assembly,"sb    %s,   %d(%s)",REG_NAME(op_dest->reg),op_src2->imm,REG_NAME(op_src1->reg));
}

make_helper(sh){
        decode_imm_type(instr);
        mem_write(op_src1->val+op_src2->val,2,reg_h(op_dest->reg));
        sprintf(assembly,"sh    %s,   %d(%s)",REG_NAME(op_dest->reg),op_src2->imm,REG_NAME(op_src1->reg));
}

make_helper(lb){
       decode_imm_type(instr);
       reg_b(op_dest->reg) = mem_read(op_src1->val+(int32_t)op_src2->val,1);
       sprintf(assembly,"lb    %s,   %d(%s)",REG_NAME(op_dest->reg),op_src2->imm,REG_NAME(op_src1->reg));
       
}

make_helper(lbu){
       decode_imm_type(instr);
       reg_b(op_dest->reg) = mem_read(op_src1->val+op_src2->val,1);
       sprintf(assembly,"lbu    %s,   %d(%s)",REG_NAME(op_dest->reg),op_src2->imm,REG_NAME(op_src1->reg));
}


make_helper(lw){
       decode_imm_type(instr);
       reg_w(op_dest->reg) = mem_read(op_src1->val+op_src2->val,4);
       sprintf(assembly,"lw    %s,   %d(%s)",REG_NAME(op_dest->reg),op_src2->imm,REG_NAME(op_src1->reg));
}

make_helper(lh){
       decode_imm_type(instr);
       reg_h(op_dest->reg) = mem_read(op_src1->val+(int32_t)op_src2->val,2);
       sprintf(assembly,"lh    %s,   %d(%s)",REG_NAME(op_dest->reg),op_src2->imm,REG_NAME(op_src1->reg));
}

make_helper(lhu){
       decode_imm_type(instr);
       reg_h(op_dest->reg) = mem_read(op_src1->val+op_src2->val,2);
       sprintf(assembly,"lhu    %s,   %d(%s)",REG_NAME(op_dest->reg),op_src2->imm,REG_NAME(op_src1->reg));
}

make_helper( addi ){   //有符号数立即数加法
       decode_imm_type(instr);
       reg_w(op_dest->reg) = (int32_t)op_src1->val+(int32_t)op_src2->val;
       //设置溢出位
       sprintf(assembly,"addi   %s,   %s,    0x%04x",REG_NAME(op_dest->reg),REG_NAME(op_src1->reg),op_src2->imm);
}

make_helper( addiu ){  //无符号数立即数加法
       decode_imm_type(instr);
       reg_w(op_dest->reg) = op_src1->val+op_src2->val;
       //不设置溢出位
       sprintf(assembly,"addiu   %s,    %s,    0x%04x",REG_NAME(op_dest->reg),REG_NAME(op_src1->reg),op_src2->imm);
}

make_helper( slti ){  //有符号数小于置位
       decode_imm_type(instr);
       if( (int32_t)op_src1->val < (int32_t)op_src2->val ){
                reg_w(op_dest->reg) = 1;
       }
       else{
                reg_w(op_dest->reg) = 0;
       }
       sprintf(assembly,"slit    %s,   %s,    0x%04x",REG_NAME(op_dest->reg),REG_NAME(op_src1->reg),op_src2->imm);
} 

make_helper( sltiu ){  //无符号数小于置位
       decode_imm_type(instr);
       if( op_src1->val < op_src2->val ){
                reg_w(op_dest->reg) = 1;
       }
       else{
                reg_w(op_dest->reg) = 0;
       }
       sprintf(assembly,"sltiu    %s,   %s,    0x%04x",REG_NAME(op_dest->reg),REG_NAME(op_src1->reg),op_src2->imm);
}

make_helper( andi ) {
       decode_imm_type(instr);
       reg_w(op_dest->reg) = (op_src1->val & op_src2->val);
       
       sprintf(assembly,"andi    %s,   %s,    0x%04x",REG_NAME(op_dest->reg),REG_NAME(op_src1->reg),op_src2->imm);
}

make_helper( xori ){
       decode_imm_type(instr);
       reg_w(op_dest->reg) = op_src1->val ^ op_src2->val;
       sprintf(assembly,"xori    %s,   %s,    0x%04x",REG_NAME(op_dest->reg),REG_NAME(op_src1->reg),op_src2->imm);
}


