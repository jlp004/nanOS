ISO_DIR=iso/
BOOT_DIR=iso/boot/
GRUB_DIR=iso/boot/grub

CC=gcc
ASM=nasm
LINK=ld
ISO_GEN=genisoimage

KERNEL_SRC=loader.s
KERNEL_OBJ=loader.o
KERNEL_ELF=kernel.elf
ISO_FILE=os.iso

.PHONY: all clean

all: $(ISO_FILE)

$(KERNEL_OBJ): $(KERNEL_SRC)
	$(ASM) -f elf32 $(KERNEL_SRC)

$(KERNEL_ELF): $(KERNEL_OBJ)
	$(LINK) -T link.ld -melf_i386 $(KERNEL_OBJ) -o $(KERNEL_ELF)
	rm $(KERNEL_OBJ)

$(ISO_FILE): $(KERNEL_ELF)
	@mkdir -p $(GRUB_DIR)
	mv $(KERNEL_ELF) $(BOOT_DIR)
	$(ISO_GEN) -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o $(ISO_FILE) $(ISO_DIR)

# temporary clean function
clean:
	rm $(BOOT_DIR)/kernel.elf
