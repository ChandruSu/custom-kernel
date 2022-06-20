

CC := utils/i686-elf-tools-windows/bin/i686-elf-gcc.exe
AS := utils/i686-elf-tools-windows/bin/i686-elf-as.exe
LD := utils/i686-elf-tools-windows/bin/i686-elf-ld.exe
DB := utils/i686-elf-tools-windows/bin/i686-elf-gdb.exe
OD := utils/i686-elf-tools-windows/bin/i686-elf-objdump.exe
CC_FLAGS := -ffreestanding -S -g -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable
LD_FLAGS := -Ttext 0x1000
QEMU_FLAGS := -hdb

OUT := out
SRC := src
ASM := asm

C_SOURCES = $(wildcard $(SRC)/*/*.c)
HEADERS = $(wildcard $(SRC)/*/*.h)
OBJS = $(C_SOURCES:$(SRC)/%.c=$(OUT)/%.o $(OUT)/interrupt.o)

all: run

$(OUT)/os-image.bin: $(OUT)/boot.bin $(OUT)/kernel.bin
	cat $^ > $@

$(OUT)/kernel.bin: $(OUT)/boot_kernel.o $(OBJS)
	$(LD) $(LD_FLAGS) $^ -o $@ --oformat binary

$(OUT)/kernel.elf: $(OUT)/boot_kernel.o $(OBJS)
	$(LD) $(LD_FLAGS) $^ -o $@

run: $(OUT)/os-image.bin
	qemu-system-x86_64 $(QEMU_FLAGS) $<

debug: $(OUT)/os-image.bin $(OUT)/kernel.elf
	qemu-system-x86_64 -s $(QEMU_FLAGS) $<
		$(DB) -ex "set architecture i386:x86-64" -ex "symbol-file $(OUT)/kernel.elf" -ex "target remote localhost:1234"

$(OUT)/%.s: $(SRC)/%.c
	$(CC) $(CC_FLAGS) $< -o $@

$(OUT)/%.o: $(SRC)/%.s
	$(AS) $< -o $@

$(OUT)/%.o: $(ASM)/%.asm
	nasm $< -f elf -o $@

$(OUT)/%.bin: $(ASM)/%.asm
	nasm $< -f bin -o $@

final: $(OUT)/os-image.bin
	dd if=$< of=$(OUT)/os-img.bin bs=10MB conv=sync
	qemu-img convert $(OUT)/os-img.bin -O raw $(OUT)/os-img.raw
	VBoxManage convertfromraw $(OUT)/os-img.raw --format vdi $(OUT)/os-img.vdi
	rm $(OUT)/os-img.bin $(OUT)/os-img.raw

clean:
	rm $(OUT)/*.o $(OUT)/*/*.o $(OUT)/*.bin $(OUT)/*.raw $(OUT)/*.vdi
