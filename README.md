1. TEMU工程目录介绍
本目录用于保存测试程序，并对其进行编译，包含build和src文件夹，convert.c，default.ld， Makefile文件。
目前测试程序仅支持汇编形式。

目录结构：
   +--mips_sc/        		: 测试程序目录
   |        
   |--temu/			: temu源程序目录
   |
   |--Makefile			: make脚本

2. TEMU的使用步骤

(1). 在终端进入目录”mips_sc“，输入“make”，在TEMU工程根目录下生成可加载的二进制文件“entry”。
(2). 在终端退回TEMU工程根目录，输入“make run”，编译temu指令集仿真器并启动。
(3). 如果需要重新编译和运行temu仿真器源代码，请在TEMU工程根目录下输入“make clean”，然后重复前两步。

------------------------
3. 10.16前的更改
全部更改都是在TEMU/temu/src/monitor/目录下
(1). ui.c文件下添加了cmd_si(),cmd_d(),cmd_p(),cmd_info()函数分别实现了si，d,p, info命令，并且将对应命令添加到cmd_table[]结构数组里（结构体使用了函数指针）。
其中cmd_d()因为监视点的结构还没有完全实现，所以并没有实际上删除监视点。cmd_p()因为表达式相关的代码还没有实现，所以也暂时处于半完成状态。
(2). monitor.c文件下,增加了枚举类型EQ,REG,NUM，还在rule[]数组中添加两个正则表达式的匹配模式。在根据规则匹配到token后，使用swicth结构对不同的token类型进行不同操作。识别出token并存储到tokens[]数组里。在expr()函数下，应该要完成对tokens数组的计算，但是此时只是打印了tokens数组的内容。更多的枚举类型和更多的rule需要添加进去。
(3). watchpoint.c里添加了display_wp()打印监视点。但是因为监视点的结构还没有实现，所以打印并没有真正打印。


