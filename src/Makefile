BUILD_DIR=../build/
ISO_DIR=../iso/
BOOT_DIR=../iso/boot/
GRUB_DIR=../iso/boot/grub
SRC=src/
BUILD=build/

CC?=gcc
ASM?=nasm
LINK?=ld
ISO_GEN?=genisoimage

CFLAGS= -m32 -ffreestanding -c

KERNEL=kernel.elf
KERNEL_SRC=loader.s
KERNEL_OBJ=loader.o
ISO_FILE=os.iso

C_SOURCES=$(wildcard *.c)
OBJECTS=$(patsubst %.c, $(BUILD_DIR)/%.o, $(C_SOURCES))

.PHONY: all clean

all: $(ISO_FILE) $(KERNEL)

$(C_SOURCES)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL_OBJ): $(KERNEL_SRC)
	$(ASM) -f elf32 $(KERNEL_SRC)

$(KERNEL): $(KERNEL_OBJ) $(OBJECTS)
	$(LINK) -T link.ld -melf_i386 $(KERNEL_OBJ) $(OBJECTS) -o $(KERNEL)
	rm $(KERNEL_OBJ)

$(ISO_FILE): $(KERNEL)
	@mkdir -p $(GRUB_DIR)
	mv $(KERNEL) $(BOOT_DIR)
	$(ISO_GEN) -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o $(ISO_FILE) $(ISO_DIR)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

# temporary clean function
clean:
	rm $(BOOT_DIR)/kernel.elf
	rm bochslog.txt
	rm os.iso
