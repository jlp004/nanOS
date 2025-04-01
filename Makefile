BUILD_DIR=build
ISO_DIR=iso
BOOT_DIR=iso/boot
GRUB_DIR=iso/boot/grub
SRC=src

CC?=gcc
ASM?=nasm
LINK?=ld
ISO_GEN?=genisoimage

CFLAGS= -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
ASMFLAGS= -f elf32

KERNEL=kernel.elf
KERNEL_SRC=loader.s
KERNEL_OBJ=loader.s.o
ISO_FILE=os.iso

C_SOURCES := $(shell find $(SRC) -name '*.c')
C_OBJECTS=$(patsubst $(SRC)/%.c, $(BUILD_DIR)/%.c.o, $(C_SOURCES))
ASM_SOURCES := $(shell find $(SRC) -name '*.s')
ASM_OBJECTS=$(patsubst $(SRC)/%.s, $(BUILD_DIR)/%.s.o, $(ASM_SOURCES))

.PHONY: all clean

all: $(C_OBJECTS) $(ASM_OBJECTS) $(ISO_FILE) $(KERNEL) 

$(KERNEL_OBJ): $(SRC)/$(KERNEL_SRC) $(ASM_OBJECTS) $(C_OBJECTS)
	$(ASM) $(ASMFLAGS) $(SRC)/$(KERNEL_SRC) -o $(BUILD_DIR)/$(KERNEL_OBJ)

$(KERNEL): $(KERNEL_OBJ) $(C_OBJECTS) $(ASM_OBJECTS)
	$(LINK) -T $(SRC)/link.ld -melf_i386 $(ASM_OBJECTS) $(C_OBJECTS) -o $(KERNEL)

$(ISO_FILE): $(KERNEL)
	@mkdir -p $(GRUB_DIR)
	mv $(KERNEL) $(BOOT_DIR)
	$(ISO_GEN) -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o $(ISO_FILE) $(ISO_DIR)

$(BUILD_DIR)/%.c.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.s.o: $(SRC)/%.s
	@mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $< -o $@

# temporary clean function
clean:
	rm $(BOOT_DIR)/kernel.elf
	rm bochslog.txt
	rm os.iso
