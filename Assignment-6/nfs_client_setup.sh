#!/bin/bash
# Assignment-6: NFS Client Setup Script (Ubuntu/Debian)
# Run on the CLIENT machine with sudo privileges.
# Usage: chmod +x nfs_client_setup.sh && ./nfs_client_setup.sh <server_ip>
# Example: ./nfs_client_setup.sh 192.168.1.100

set -e

SERVER_IP="$1"
MOUNT_POINT="/mnt/nfs_share"
SERVER_SHARE="/srv/nfs/share"

if [ -z "$SERVER_IP" ]; then
    echo "Error: Server IP address is required."
    echo "Usage: $0 <server_ip>"
    echo "Example: $0 192.168.1.100"
    exit 1
fi

echo "=== Step 1: System Preparation ==="
sudo apt update
sudo apt install -y nfs-common

echo "=== Step 2: Client Configuration ==="
echo "Creating mount point: $MOUNT_POINT"
sudo mkdir -p "$MOUNT_POINT"

echo "=== Step 3: Mount Shared Directory ==="
echo "Mounting $SERVER_IP:$SERVER_SHARE to $MOUNT_POINT"
sudo mount "$SERVER_IP:$SERVER_SHARE" "$MOUNT_POINT"

echo "=== Step 4: Verification ==="
echo "Checking mount status:"
df -h | grep nfs || echo "Warning: NFS share not found in mount list"

echo ""
echo "Listing contents of mounted share:"
ls -l "$MOUNT_POINT"

echo ""
echo "=== Creating test file from client ==="
echo "Hello from NFS client" | sudo tee "$MOUNT_POINT/client_file.txt" > /dev/null
echo "Created: client_file.txt"

echo ""
echo "Current contents:"
ls -l "$MOUNT_POINT"

echo ""
echo "=== Verify on server ==="
echo "On the server machine, run:"
echo "  ls -l $SERVER_SHARE"
echo "  cat $SERVER_SHARE/client_file.txt"

echo ""
echo "=== NFS client setup complete ==="
echo "Mount point: $MOUNT_POINT"
echo "Server: $SERVER_IP:$SERVER_SHARE"
echo ""
echo "To unmount: sudo umount $MOUNT_POINT"
echo "To mount on boot, add to /etc/fstab:"
echo "  $SERVER_IP:$SERVER_SHARE $MOUNT_POINT nfs defaults 0 0"
