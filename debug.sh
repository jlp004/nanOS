#!/bin/bash

# Set paths
KERNEL_IMAGE="build/kernel.img"             # Replace with your kernel binary
DISK_IMAGE="build/main_floppy.img"          # Replace with disk image if debugging full OS
USE_DISK=true                               # Set to true if debugging a disk image

# QEMU options
QEMU_CMD="qemu-system-x86_64 -s -S"

if [ "$USE_DISK" = true ]; then
    QEMU_CMD="$QEMU_CMD -drive file=$DISK_IMAGE,format=raw"
else
    QEMU_CMD="$QEMU_CMD -kernel $KERNEL_IMAGE"
fi

# Start QEMU in the background
echo "[+] Starting QEMU with debugging enabled..."
$QEMU_CMD &

# Get QEMU process ID (for cleanup)
QEMU_PID=$!

# Create a temporary GDB script
GDB_SCRIPT=$(mktemp)

cat <<EOF > $GDB_SCRIPT
set architecture i386:x86-64  # Set CPU architecture
target remote localhost:1234  # Connect to QEMU debug server

# Set breakpoints (edit as needed)
break *0x100000  # Example address (replace with actual)
continue
EOF

# Start GDB
echo "[+] Starting GDB and attaching to QEMU..."
gdb -x $GDB_SCRIPT

# Cleanup
rm $GDB_SCRIPT
kill $QEMU_PID  # Kill QEMU after debugging
