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

KERNEL=kernel.elf
KERNEL_SRC=loader.s
KERNEL_OBJ=loader.o
ISO_FILE=os.iso

C_SOURCES=$(wildcard $(SRC)/*.c)
OBJECTS=$(patsubst $(SRC)/%.c, $(BUILD_DIR)/%.o, $(C_SOURCES))

.PHONY: all clean

all: $(ISO_FILE) $(KERNEL)

$(KERNEL_OBJ): $(SRC)/$(KERNEL_SRC)
	$(ASM) -f elf32 $(SRC)/$(KERNEL_SRC) -o $(BUILD_DIR)/$(KERNEL_OBJ)

$(KERNEL): $(KERNEL_OBJ) $(OBJECTS)
	$(LINK) -T $(SRC)/link.ld -melf_i386 $(BUILD_DIR)/$(KERNEL_OBJ) $(OBJECTS) -o $(KERNEL)

$(ISO_FILE): $(KERNEL)
	@mkdir -p $(GRUB_DIR)
	mv $(KERNEL) $(BOOT_DIR)
	$(ISO_GEN) -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o $(ISO_FILE) $(ISO_DIR)

$(BUILD_DIR)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $< -o $@

# temporary clean function
clean:
	rm $(BOOT_DIR)/kernel.elf
	rm bochslog.txt
	rm os.iso
