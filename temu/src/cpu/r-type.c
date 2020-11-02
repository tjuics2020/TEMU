#include "helper.h"
#include "monitor.h"
#include "reg.h"

extern uint32_t instr;
extern char assembly[80];


/* decode R-type instrucion */

static void decode_r_type(uint32_t instr) {

	op_src1->type = OP_TYPE_REG;
	op_src1->reg = (instr & RS_MASK) >> (RT_SIZE + IMM_SIZE);
	op_src1->val = reg_w(op_src1->reg);
	
	op_src2->type = OP_TYPE_REG;
	op_src2->imm = (instr & RT_MASK) >> (RD_SIZE + SHAMT_SIZE + FUNC_SIZE);
	op_src2->val = reg_w(op_src2->reg);

	op_dest->type = OP_TYPE_REG;
	op_dest->reg = (instr & RD_MASK) >> (SHAMT_SIZE + FUNC_SIZE);
}

make_helper(and) {

	decode_r_type(instr);
	reg_w(op_dest->reg) = (op_src1->val & op_src2->val);
	sprintf(assembly, "and   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
        //printf("here!:%s\n",REG_NAME(op_src1->reg));
}

make_helper(add) {
        decode_r_type(instr);
        reg_w(op_dest->reg) = op_src1->val+op_src2->val;
        //设置溢出位
        sprintf(assembly, "add   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(addu) {
        decode_r_type(instr);
        reg_w(op_dest->reg) = op_src1->val+op_src2->val;
        //不设置溢出位
        sprintf(assembly, "addu   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper( sub ){
        decode_r_type(instr);
        reg_w(op_dest->reg) = op_src1->val-op_src2->val;
        //设置溢出位
        sprintf(assembly, "sub   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper( subu) {
        decode_r_type(instr);
        reg_w(op_dest->reg) = op_src1->val-op_src2->val;
        //不设置溢出位
        sprintf(assembly, "subu   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper( slt ){
        decode_r_type(instr);
        //有符号数小于置位
        if( (int32_t)op_src1->val < (int32_t)op_src2->val ){
            reg_w(op_dest->reg) = 1;
        }else{
            reg_w(op_dest->reg) = 0; 
        }
        sprintf(assembly, "slt   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper( sltu ){
        decode_r_type(instr);
        //无符号数小于置位  
        if( op_src1->val < op_src2->val ){
            reg_w(op_dest->reg) = 1;
        }else{
            reg_w(op_dest->reg) = 0;
        }
        sprintf(assembly, "sltu   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}
\
make_helper( nor ){   //或非 ??
        decode_r_type(instr);
        reg_w(op_dest->reg) = ~(op_src1->val|op_src2->val);
        sprintf(assembly, "nor   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper( or ){  //
        decode_r_type(instr);  
        reg_w(op_dest->reg) = op_src1->val|op_src2->val;
        sprintf(assembly, "or   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper( xor ){  //??
        decode_r_type(instr);
        reg_w(op_dest->reg) = op_src1->val ^ op_src2->val;
        sprintf(assembly, "xor   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper( sll ){
        decode_r_type(instr);
        int shamt = (instr & SHAMT_MASK) >> FUNC_SIZE;
        reg_w(op_dest->reg) = op_src2->val << shamt;
        sprintf(assembly, "sll   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), shamt);
}

make_helper( sllv ){
        decode_r_type(instr);
        reg_w(op_dest->reg) = op_src2->val << op_src1->val;
        sprintf(assembly, "sllv   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), REG_NAME(op_src1->reg));
}

make_helper( sra ){  //算术右移   即符号扩展
        decode_r_type(instr);
        int shamt = (instr & SHAMT_MASK) >> FUNC_SIZE;
        reg_w(op_dest->reg) = (int32_t)op_src2->val >> shamt;
        sprintf(assembly, "sra   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), shamt);
}

make_helper( srav ){  //算术右移   即符号扩展
        decode_r_type(instr);
        reg_w(op_dest->reg) = (int32_t)op_src2->val >> op_src1->val;
        sprintf(assembly, "srav   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), REG_NAME(op_src1->reg));
}

make_helper( srl ){  //逻辑右移   即0扩展
        decode_r_type(instr);
        int shamt = (instr & SHAMT_MASK) >> FUNC_SIZE;
        reg_w(op_dest->reg) = op_src2->val >> shamt;
        sprintf(assembly, "srl   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), shamt);
}

make_helper( srlv ){  //逻辑右移   即0扩展
        decode_r_type(instr);
        reg_w(op_dest->reg) = op_src2->val >> op_src1->val;
        sprintf(assembly, "srlv   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), REG_NAME(op_src1->reg));
}


make_helper( multu ){
        decode_r_type(instr);
        uint32_t src1_h,src1_l,src2_h,src2_l,temp;
        src1_h = op_src1->val>>16;
        src1_l = op_src1->val&0xffff;
        src2_h = op_src2->val>>16;
        src2_l = op_src2->val&0xffff;
        reg_sp(hi) = src1_h*src2_h;
        reg_sp(lo) = src1_l*src2_l;
        temp = src1_l*src2_h+src1_h*src2_l;
        reg_sp(lo) += temp<<16;
        reg_sp(hi) += temp>>16;
        printf("src1:0x%x src2:0x%x temp:0x%x\n",op_src1->val,op_src2->val,temp);
        printf("hi:0x%x lo:0x%x\n",reg_sp(hi),reg_sp(lo));
        sprintf(assembly, "multu   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), REG_NAME(op_src1->reg));
}
