本目录为《计算机系统设计——基于FPGA的RISC微处理器设计与实现》第五章的测试程序目录。

包含build和src文件夹，convert.c，default.ld， Makefile文件。

目录结构：
   +--build/        		: 中间结果和最终文件保存目录
   |        
   |--src/			: 测试汇编源程序
   |
   |--convert.c			: 转化文件，将编译生成的二进制代码转化为Vivado工程能够直接使用的coe文件
   |
   |--default.ld		: 编译链接脚本
   |
   |--Makefile			: make脚本