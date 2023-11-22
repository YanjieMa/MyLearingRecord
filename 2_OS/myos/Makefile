include config/make-locations
include config/make-os
include config/make-cc

CFLAGS := -std=gnu99 -ffreestanding -O2  -Wall -Wl,--build-id=none
# -std=gnu99 使用C99标准 支持在for循环中定义变量 默认是C89的标准
# -w 关闭编译时的警告
# -W 只显示编译器认为会出现错误的警告
# -Wall 编译时 显示所有警告
LDFLAGS := -ffreestanding -O2  -nostdlib -Wall -lgcc -Wl,--build-id=none
# -ffreestanding 编译的目标是一个独立式的环境 标准库可能不存在 程序的入口函数不一定是main 编译城独立程序 而非宿主程序
# -O2 编译器的优化级别
# -nostdlib 不链接系统标准启动文件和标准库文件 仅把系统指定的文件传递给链接器
# -lgcc -l 指定链接的库 libgcc 是gcc包提供的内部库

# -Wl,--build-id=none的影响如下
# [root@cloud myos]# readelf -S myos.bin 
# There are 11 section headers, starting at offset 0x2700:

# Section Headers:
#   [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
#   [ 0]                   NULL            00000000 000000 000000 00      0   0  0
#   [ 1] .note.gnu.build-i NOTE            00100000 001000 000024 00   A  0   0  4
#   [ 2] .text             PROGBITS        00101000 002000 000253 00  AX  0   0 4096
#   [ 3] .rodata.str1.1    PROGBITS        00101253 002253 000016 01 AMS  0   0  1
#   [ 4] .eh_frame         PROGBITS        0010126c 00226c 000118 00   A  0   0  4
#   [ 5] .eh_frame_hdr     PROGBITS        00101384 002384 00004c 00   A  0   0  4
#   [ 6] .bss              NOBITS          00102000 003000 004010 00  WA  0   0 4096
#   [ 7] .comment          PROGBITS        00000000 0023d0 00002c 01  MS  0   0  1
#   [ 8] .shstrtab         STRTAB          00000000 0023fc 000069 00      0   0  1
#   [ 9] .symtab           SYMTAB          00000000 002468 000190 10     10  12  4
#   [10] .strtab           STRTAB          00000000 0025f8 000106 00      0   0  1
# Key to Flags:
#   W (write), A (alloc), X (execute), M (merge), S (strings)
#   I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
#   O (extra OS processing required) o (OS specific), p (processor specific)
# [root@cloud myos]# readelf -S myos_nobuildid.bin 
# There are 10 section headers, starting at offset 0x16dc:

# Section Headers:
#   [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
#   [ 0]                   NULL            00000000 000000 000000 00      0   0  0
#   [ 1] .text             PROGBITS        00100000 001000 000253 00  AX  0   0 4096
#   [ 2] .rodata.str1.1    PROGBITS        00100253 001253 000016 01 AMS  0   0  1
#   [ 3] .eh_frame         PROGBITS        0010026c 00126c 000118 00   A  0   0  4
#   [ 4] .eh_frame_hdr     PROGBITS        00100384 001384 00004c 00   A  0   0  4
#   [ 5] .bss              NOBITS          00101000 002000 004010 00  WA  0   0 4096
#   [ 6] .comment          PROGBITS        00000000 0013d0 00002c 01  MS  0   0  1
#   [ 7] .shstrtab         STRTAB          00000000 0013fc 000056 00      0   0  1
#   [ 8] .symtab           SYMTAB          00000000 001454 000180 10      9  11  4
#   [ 9] .strtab           STRTAB          00000000 0015d4 000106 00      0   0  1
# Key to Flags:
#   W (write), A (alloc), X (execute), M (merge), S (strings)
#   I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
#   O (extra OS processing required) o (OS specific), p (processor specific)



# 头文件
INCLUDES := $(patsubst %, -I%, $(INCLUDES_DIR))
# 所有 .c .s .S文件
SOURCES_FILES := $(shell find . -name "*.[csS]")
# 所有生成的 .o文件
OBJS := $(patsubst ./%, $(OBJECT_DIR)/%.o, $(SOURCES_FILES))

# 编译.S文件
$(OBJECT_DIR)/%.S.o : %.S
	@mkdir -p $(dir $@)
	@echo "CC $<"
	$(CC) $(INCLUDES) -c $< -o $@
# 编译.s文件
$(OBJECT_DIR)/%.s.o : %.s
	@mkdir -p $(dir $@)
	@echo "CC $<"
	$(CC) $(INCLUDES) -c $< -o $@
#编译.c文件
$(OBJECT_DIR)/%.c.o: %.c 
	@mkdir -p $(dir $@)
	@echo "CC    $<"
	$(CC) $(INCLUDES) -c $< -o $@ $(CFLAGS)
#链接生成bin文件
$(BIN_DIR)/$(OS_BIN): $(OBJS)
	@mkdir -p $(dir $@)
	@echo "  LD    $(BIN_DIR)/$(OS_BIN)"
	$(CC) -T link/linker.ld -o $(BIN_DIR)/$(OS_BIN) $(OBJS) $(LDFLAGS)
#生成iso文件
$(BUILD_DIR)/$(OS_ISO) : $(BIN_DIR)/$(OS_BIN)
	@mkdir -p $(dir $@)
	@mkdir -p $(ISO_GRUB_DIR)
	@mkdir -p $(ISO_BOOT_DIR)
	@./config-grub.sh ${OS_NAME} $(ISO_GRUB_DIR)/grub.cfg
	@cp $(BIN_DIR)/$(OS_BIN) $(ISO_BOOT_DIR)
	@grub2-mkrescue -o $(BUILD_DIR)/$(OS_ISO) $(ISO_DIR)


all : $(BUILD_DIR)/$(OS_ISO)


all-debug : CFLAGS := -g -std=gnu99 -ffreestanding -Og -Wall -Wl,--build-id=none
all-debug : LDFLAGS := -g -ffreestanding -Og  -nostdlib -lgcc -Wall -Wl,--build-id=none
all-debug : clean $(BUILD_DIR)/$(OS_ISO)
	@echo "Dumping the disassembled kernel code to $(BUILD_DIR)/kdump.txt"
	@mkdir -p $(BUILD_DIR)
	@objdump -S $(BIN_DIR)/$(OS_BIN) > $(BUILD_DIR)/kdump.txt

.PHONY:
debug:
	@echo "SOURCES_FILES is ${SOURCES_FILES}"
clean:
	rm -rf build