#定义一大堆变量，实质就是将需要多次重复用到的语句定义一个变量方便使用与替换
BUILD_DIR=./build
ENTRY_POINT=0xc0001500
HD60M_PATH=./hd60M.img
BOCHS_GDB=/home/wjm/bochs-gdb/bin
#只需要把hd60m.img路径改成自己环境的路径，整个代码直接make all就完全写入了，能够运行成功
AS=nasm
CC=gcc
LD=ld
LIB= -I lib/ -I lib/kernel/ -I lib/user/ -I kernel/ -I device/ -I thread/ -I userprog/
ASFLAGS= -f elf -g
CFLAGS= -Wall $(LIB) -c -fno-builtin -W -Wstrict-prototypes -Wmissing-prototypes -m32 -g
#-Wall warning wall的意思，产生尽可能多警告信息，-fno-builtin不要采用内部函数，
#-W 会显示警告，但是只显示编译器认为会出现错误的警告
#-Wstrict-prototypes 要求函数声明必须有参数类型，否则发出警告。-Wmissing-prototypes 必须要有函数声明，否则发出警告

LDFLAGS= -Ttext $(ENTRY_POINT) -e main -Map $(BUILD_DIR)/kernel.map -m elf_i386
#-Map,生成map文件，就是通过编译器编译之后，生成的程序、数据及IO空间信息的一种映射文件
#里面包含函数大小，入口地址等一些重要信息

INCLUDE_FILE= $(wildcard ./device/*.h ./kernel/*.h ./lib/kernel/*.h ./thread/*.h ./userprog/*.h)
SOURCE_C= $(wildcard ./device/*.c ./kernel/*.c ./lib/kernel/*.c ./lib/user/*.c ./thread/*.c ./userprog/*.c)
SOURCE_S= $(wildcard ./kernel/*.s ./lib/kernel/*.s ./thread/*.s)

SOURCE_C:= ./kernel/main.c $(filter-out ./kernel/main.c,$(SOURCE_C))

OBJS:= $(SOURCE_C)
OBJS+= $(SOURCE_S)
OBJS:= $(patsubst %.c, %.o,$(OBJS))
OBJS:= $(patsubst %.s, %.o,$(OBJS))
#OBJS:= $(patsubst ./%, $(BUILD_DIR)/%,$(OBJS))
#$(info The OBJS will be built is:)
#$(info $(patsubst ./%, $(BUILD_DIR)/%,$(OBJS)))
#$(info $(dir $(patsubst ./%, $(BUILD_DIR)/%,$(OBJS))))
#OBJS=$(BUILD_DIR)/main.o $(BUILD_DIR)/init.o \
#	$(BUILD_DIR)/interrupt.o $(BUILD_DIR)/timer.o $(BUILD_DIR)/kernel.o \
#	$(BUILD_DIR)/print.o $ 
#顺序最好是调用在前，实现在后

######################编译两个启动文件的代码#####################################
all:mk_dir boot build hd gdb_symbol


$(BUILD_DIR)/boot/mbr.o:boot/mbr.s
	$(AS) -I boot/include/ -o build/boot/mbr.o boot/mbr.s
	
$(BUILD_DIR)/boot/loader.o:boot/loader.s
	$(AS) -I boot/include/ -o build/boot/loader.o boot/loader.s
	
######################编译C内核代码###################################################
$(BUILD_DIR)/kernel/main.o:kernel/main.c
	$(CC) $(CFLAGS) -o $@ $<	

$(BUILD_DIR)/%.o:%.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/%.o:%.s
	$(AS) $(ASFLAGS) -o $@ $<

##################链接所有内核目标文件##################################################
$(BUILD_DIR)/kernel.bin:$(patsubst ./%, $(BUILD_DIR)/%,$(OBJS))
	$(LD) $(LDFLAGS) -o $@ $^
# $^表示规则中所有依赖文件的集合，如果有重复，会自动去重

$(HD60M_PATH):build/boot/mbr.o build/boot/loader.o $(BUILD_DIR)/kernel.bin
	if [ ! -f $(HD60M_PATH) ];then dd if=/dev/zero of=hd60M.img bs=512 count=122880;fi&& \
	dd if=build/boot/mbr.o of=$(HD60M_PATH) count=1 bs=512 conv=notrunc && \
	dd if=build/boot/loader.o of=$(HD60M_PATH) count=4 bs=512 seek=2 conv=notrunc && \
	dd if=$(BUILD_DIR)/kernel.bin of=$(HD60M_PATH) bs=512 count=200 seek=9 conv=notrunc 

$(BUILD_DIR)/kernel.sym:$(BUILD_DIR)/kernel.bin
	objcopy --only-keep-debug $(BUILD_DIR)/kernel.bin $(BUILD_DIR)/kernel.sym

mk_dir:
	@if [ ! -d $(BUILD_DIR) ];then mkdir $(BUILD_DIR);fi
	@if [ ! -d $(BUILD_DIR)/boot ];then mkdir $(BUILD_DIR)/boot; \
	echo "Creating directory $(BUILD_DIR)/boot";fi; 	
	@for p in $(dir $(patsubst ./%, $(BUILD_DIR)/%,$(OBJS))); do \
	if [ ! -d $$p ]; then \
	echo "Creating directory $$p"; \
	mkdir -p $$p; \
	fi; \
	done
#判断build文件夹是否存在，如果不存在，则创建

boot:$(BUILD_DIR)/boot/mbr.o $(BUILD_DIR)/boot/loader.o

hd: $(HD60M_PATH)
	
clean:
	@cd $(BUILD_DIR) && rm -rf ./* && echo "remove ./build all done"
#-f, --force忽略不存在的文件，从不给出提示，执行make clean就会删除build下所有文件

build:$(BUILD_DIR)/kernel.bin
	
#执行build需要依赖kernel.bin，但是一开始没有，就会递归执行之前写好的语句编译kernel.bin

rebuild:clean all

gdb_symbol:$(BUILD_DIR)/kernel.sym

gdb: all
	echo '' | $(BOCHS_GDB)/bochs -f $(BOCHS_GDB)/bochsrc_gdb.disk & \
	gdb -ex "target remote:1234" -ex "symbol-file $(shell pwd)/build/kernel.sym"

bochs: all
	$(BOCHS_GDB)/bochs -f $(BOCHS_GDB)/bochsrc.disk

.PHONY:mk_dir hd clean build all boot print-txtfiles gdb gdb_symbol bochs	#定义了6个伪目标

