#!/bin/bash
# Assignment-6: NFS Server Setup Script (Ubuntu/Debian)
# Run on the SERVER machine with sudo privileges.
# Usage: chmod +x nfs_server_setup.sh && ./nfs_server_setup.sh [client_ip]
# Example: ./nfs_server_setup.sh 192.168.1.50
# Use "*" to allow all clients (lab default).

set -e

CLIENT_IP="${1:-*}"
SHARE_DIR="/srv/nfs/share"

echo "=== Step 1: System Preparation ==="
sudo apt update
sudo apt install -y nfs-kernel-server

echo "=== Step 2: Server Configuration ==="
sudo mkdir -p "$SHARE_DIR"
# nobody:nogroup is the standard anonymous NFS owner on Debian/Ubuntu
sudo chown nobody:nogroup "$SHARE_DIR"
sudo chmod 755 "$SHARE_DIR"

echo "Hello from NFS server" | sudo tee "$SHARE_DIR/sample.txt" > /dev/null
ls -l "$SHARE_DIR"

echo "=== Step 3: Export Configuration ==="
EXPORT_ENTRY="$SHARE_DIR $CLIENT_IP(rw,sync,no_subtree_check)"
if ! grep -qF "$SHARE_DIR" /etc/exports 2>/dev/null; then
    echo "$EXPORT_ENTRY" | sudo tee -a /etc/exports > /dev/null
    echo "Added to /etc/exports: $EXPORT_ENTRY"
else
    echo "/etc/exports already contains an entry for $SHARE_DIR"
    echo "Current entry:"
    grep -F "$SHARE_DIR" /etc/exports
fi
sudo exportfs -a
sudo exportfs -v

echo "=== Step 4: Service Management ==="
sudo systemctl restart nfs-kernel-server
sudo systemctl enable nfs-kernel-server
sudo systemctl status nfs-kernel-server --no-pager || true

echo "=== Verify on server ==="
showmount -e localhost

echo "NFS server setup complete. Share: $SHARE_DIR"
