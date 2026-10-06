# Assignment-6: NFS Configuration in Linux

## 📝 Assignment Overview

This assignment demonstrates the configuration of a **Network File System (NFS)** server and client in Linux. NFS allows users to access and share files over a network as if they were stored locally. The assignment covers the complete setup process including server configuration, export management, client mounting, and verification of file sharing capabilities.

## 🎯 Objectives

- Install and configure NFS server packages on Linux
- Create and configure shared directories with appropriate permissions
- Configure `/etc/exports` file to control NFS exports
- Mount NFS shares on client systems
- Verify file sharing between server and client
- Understand NFS security and access control mechanisms
- Implement read-only access and IP-based restrictions

## 🏗️ Architecture

```
┌──────────────────────────────────────────────┐
│            NFS SERVER (Server Machine)       │
├──────────────────────────────────────────────┤
│ 1. Install nfs-kernel-server                │
│ 2. Create shared directory (/srv/nfs/share)  │
│ 3. Set permissions (755, nobody:nogroup)     │
│ 4. Configure /etc/exports                    │
│ 5. Start nfs-kernel-server service           │
│ 6. Export filesystem                         │
└──────────────────────────────────────────────┘
                    ↕ NFS Protocol (Port 2049)
┌──────────────────────────────────────────────┐
│            NFS CLIENT (Client Machine)       │
├──────────────────────────────────────────────┤
│ 1. Install nfs-common                        │
│ 2. Create mount point (/mnt/nfs_share)        │
│ 3. Mount NFS share                           │
│ 4. Access shared files                       │
│ 5. Verify synchronization                    │
└──────────────────────────────────────────────┘
```

## 📂 Files

| File | Purpose |
|------|---------|
| `nfs_server_setup.sh` | Automated NFS server setup script |
| `nfs_client_setup.sh` | Automated NFS client setup script |
| `README.md` | This documentation file |
| `Assignment-6.pdf` | Original assignment instructions |

## 🔧 Configuration

**Server Configuration:**
- **Shared Directory:** `/srv/nfs/share`
- **Default Access:** Read-write (rw) for all clients (*)
- **Sync Mode:** Synchronous writes (sync)
- **Subtree Check:** Disabled (no_subtree_check)
- **NFS Service:** nfs-kernel-server

**Client Configuration:**
- **Mount Point:** `/mnt/nfs_share`
- **Mount Options:** defaults
- **NFS Client Package:** nfs-common

## 💻 Procedure

### Step 1: System Preparation

**Update the system and install required NFS packages.**

**Server Commands:**
```bash
sudo apt update
sudo apt install -y nfs-kernel-server
```

**Client Commands:**
```bash
sudo apt update
sudo apt install -y nfs-common
```

### Step 2: Server Configuration

**Create a directory to be shared and assign appropriate permissions.**

**Commands:**
```bash
sudo mkdir -p /srv/nfs/share
sudo chown nobody:nogroup /srv/nfs/share
sudo chmod 755 /srv/nfs/share
```

**Create a sample file:**
```bash
echo "Hello from NFS server" | sudo tee /srv/nfs/share/sample.txt
ls -l /srv/nfs/share
```

### Step 3: Export Configuration

**Open configuration file:**
```bash
sudo nano /etc/exports
```

**Write entry:**
```
/srv/nfs/share *(rw,sync,no_subtree_check)
```

**Apply configuration:**
```bash
sudo exportfs -a
sudo exportfs -v
```

### Step 4: Service Management

**Start/restart NFS service:**
```bash
sudo systemctl restart nfs-kernel-server
sudo systemctl enable nfs-kernel-server
sudo systemctl status nfs-kernel-server
```

### Step 5: Client Configuration

**Create mount point:**
```bash
sudo mkdir -p /mnt/nfs_share
```

**Mount shared directory:**
```bash
sudo mount <server_ip>:/srv/nfs/share /mnt/nfs_share
```

**Example:**
```bash
sudo mount 192.168.1.100:/srv/nfs/share /mnt/nfs_share
```

### Step 6: Verification

**List contents:**
```bash
ls -l /mnt/nfs_share
```

**Create file:**
```bash
echo "Hello from NFS client" | sudo tee /mnt/nfs_share/client_file.txt
```

**Verify on server:**
```bash
ls -l /srv/nfs/share
cat /srv/nfs/share/client_file.txt
```

### Step 7: Analysis

**1. Role of /etc/exports?**
The `/etc/exports` file defines which directories on the NFS server are available to be mounted by NFS clients. It specifies:
- The directory path to be exported
- Which clients or networks can access it (by IP, hostname, or wildcard)
- Access permissions (read-only or read-write)
- NFS-specific options (sync, no_subtree_check, etc.)

**2. Why mounting is required?**
Mounting is required because:
- NFS shares are remote filesystems that need to be integrated into the local filesystem hierarchy
- Mounting creates a connection between the local mount point and the remote NFS share
- It allows the operating system to treat the remote files as if they were local
- Without mounting, the client cannot access the shared files through the filesystem

**3. Difference between local FS and NFS?**
| Aspect | Local File System | NFS (Network File System) |
|--------|------------------|---------------------------|
| **Location** | Files stored on local disk | Files stored on remote server |
| **Access Speed** | Fast (direct disk I/O) | Slower (network latency) |
| **Reliability** | Depends on local hardware | Depends on network and server |
| **Concurrent Access** | Limited to local processes | Multiple clients can access simultaneously |
| **Configuration** | Automatically mounted | Requires manual or automount configuration |
| **Security** | Local user permissions | Network-based authentication + permissions |

**4. Effect of incorrect permissions?**
- **Server-side incorrect permissions:** Clients may be unable to read/write files even if NFS export allows it
- **Client-side mount point permissions:** Users may not be able to access the mounted share
- **Export permission mismatch:** If `/etc/exports` specifies `ro` but directory has write permissions, clients still cannot write
- **Root squashing:** If not configured properly, root access may be mapped to anonymous user, limiting operations

### Step 8: Advanced Task

**Allow only specific IP and read-only access:**

**Edit /etc/exports:**
```bash
sudo nano /etc/exports
```

**Replace entry with:**
```
/srv/nfs/share 192.168.1.50(ro,sync,no_subtree_check)
```

**Apply changes:**
```bash
sudo exportfs -a
sudo exportfs -v
sudo systemctl restart nfs-kernel-server
```

**Verify:**
```bash
showmount -e localhost
```

## 🔨 Automated Setup

### Server Setup Script

The provided `nfs_server_setup.sh` automates the entire server configuration:

**Usage:**
```bash
chmod +x nfs_server_setup.sh
sudo ./nfs_server_setup.sh [client_ip]
```

**Examples:**
```bash
# Allow all clients (default)
sudo ./nfs_server_setup.sh

# Allow specific client IP
sudo ./nfs_server_setup.sh 192.168.1.50

# Allow specific network
sudo ./nfs_server_setup.sh 192.168.1.0/24
```

### Client Setup Script

The `nfs_client_setup.sh` automates client configuration:

**Usage:**
```bash
chmod +x nfs_client_setup.sh
sudo ./nfs_client_setup.sh <server_ip>
```

**Example:**
```bash
sudo ./nfs_client_setup.sh 192.168.1.100
```

## 🚀 Execution

### Method 1: Automated (Recommended)

**Server Machine:**
```bash
cd Assignment-6
chmod +x nfs_server_setup.sh
sudo ./nfs_server_setup.sh
```

**Client Machine:**
```bash
cd Assignment-6
chmod +x nfs_client_setup.sh
sudo ./nfs_client_setup.sh <server_ip>
```

### Method 2: Manual

Follow the detailed procedure steps outlined above.

## 📊 Verification Steps

### Server Verification
```bash
# Check NFS service status
sudo systemctl status nfs-kernel-server

# List exported shares
showmount -e localhost

# Check exports file
cat /etc/exports

# Verify shared directory contents
ls -l /srv/nfs/share
```

### Client Verification
```bash
# Check mounted filesystems
df -h | grep nfs

# List mounted contents
ls -l /mnt/nfs_share

# Create test file
echo "Test from client" | sudo tee /mnt/nfs_share/test.txt

# Verify on server (on server machine)
cat /srv/nfs/share/test.txt
```

## 🔍 Key Features

### Export Options Explained
- **rw** - Read-write access
- **ro** - Read-only access
- **sync** - Synchronous writes (data written to disk before response)
- **async** - Asynchronous writes (faster but less reliable)
- **no_subtree_check** - Disables subtree checking (improves performance)
- **root_squash** - Maps root user to anonymous user (security feature)
- **no_root_squash** - Allows root to have root access on shared files

### Security Considerations
- Use specific IP addresses instead of wildcards (*)
- Implement firewall rules to restrict NFS port (2049)
- Use read-only access when possible
- Regularly review `/etc/exports` for stale entries
- Monitor NFS logs for suspicious activity

## 🧪 Testing

### Basic Test Case
1. **Setup:** Run server and client setup scripts
2. **Create file on client:** `echo "test" | sudo tee /mnt/nfs_share/test.txt`
3. **Verify on server:** `cat /srv/nfs/share/test.txt`
4. **Expected:** File appears on server with correct content

### Advanced Test Case
1. **Configure read-only access:** Edit `/etc/exports` with `ro` option
2. **Remount on client:** `sudo umount /mnt/nfs_share && sudo mount <server_ip>:/srv/nfs/share /mnt/nfs_share`
3. **Attempt to write:** `echo "test" | sudo tee /mnt/nfs_share/readonly_test.txt`
4. **Expected:** Write operation fails with "Read-only file system" error

### Troubleshooting
| Issue | Solution |
|-------|----------|
| Mount: Connection timed out | Check firewall, ensure server is reachable |
| Permission denied | Verify `/etc/exports` and directory permissions |
| Stale file handle | Unmount and remount the share |
| showmount: No route to host | Check network connectivity and NFS service status |

## 📚 Concepts Covered

| Concept | Description |
|---------|-------------|
| **NFS** | Network File System - distributed file system protocol |
| **Export** | Making a directory available for NFS clients |
| **Mount** | Attaching a remote filesystem to local directory |
| **ExportFS** | Command to manage NFS exports |
| **Showmount** | Utility to display NFS exports from a server |
| **/etc/exports** | Configuration file for NFS exports |
| **Sync vs Async** | Write synchronization modes for NFS |
| **Root Squashing** | Security feature to prevent root access |

## 🔗 Related Concepts

- **Network Protocols** - TCP/IP, UDP (NFS can use both)
- **File Systems** - EXT4, XFS, NFS, CIFS
- **System Administration** - Service management, user permissions
- **Network Security** - Firewalls, IP-based access control
- **Distributed Systems** - Remote resource sharing

## 📖 Learning Resources

- [NFS Documentation (Ubuntu)](https://ubuntu.com/server/docs/service-nfs)
- [NFS How-To (Linux Documentation)](https://nfs.sourceforge.net/)
- [exports(5) Manual Page](https://linux.die.net/man/5/exports)
- [Network File System (Wikipedia)](https://en.wikipedia.org/wiki/Network_File_System)

## ❓ FAQ

### 1. What is the role of /etc/exports?
The `/etc/exports` file is the configuration file that defines which directories on the NFS server are available to be mounted by NFS clients. It specifies the export path, allowed clients (by IP, hostname, or network), and access options like read-only/read-write, sync mode, and security settings. The NFS server reads this file to determine which filesystems to export and with what permissions.

### 2. Why is mounting required in NFS?
Mounting is required because NFS shares are remote filesystems that need to be integrated into the local filesystem hierarchy. The mount operation establishes the connection between a local directory (mount point) and the remote NFS share, allowing the operating system to treat remote files as if they were stored locally. Without mounting, the client cannot access the shared files through standard filesystem operations.

### 3. Difference between local file system and NFS.
Local file systems reside on physical disks directly attached to the system, offering fast access with minimal latency. NFS is a network-based file system where files are stored on a remote server and accessed over the network. Key differences include: access speed (local is faster), reliability (local depends on hardware, NFS depends on network), concurrent access (NFS supports multiple clients), and configuration (local is automatic, NFS requires explicit mounting and network setup).

### 4. What will happen if permissions are not set properly?
If permissions are not set properly, several issues can occur:
- **Directory permissions:** If the shared directory doesn't have appropriate read/write permissions, clients may be unable to access files even if NFS export allows it
- **Export permissions:** If `/etc/exports` is misconfigured (e.g., missing `rw` flag), clients will be denied write access
- **Client mount point:** If the local mount point has restrictive permissions, users may not be able to access the mounted share
- **Root squashing:** If not configured, root users may have unexpected behavior (mapped to anonymous user by default for security)

## ✅ Checklist

- [x] Install NFS server package (nfs-kernel-server)
- [x] Install NFS client package (nfs-common)
- [x] Create shared directory with proper permissions
- [x] Configure `/etc/exports` file
- [x] Apply export configuration with exportfs
- [x] Start and enable NFS service
- [x] Create mount point on client
- [x] Mount NFS share on client
- [x] Verify file sharing between server and client
- [x] Understand export options and permissions
- [x] Implement read-only access configuration
- [x] Troubleshoot common NFS issues

## 📝 Notes

- NFS uses port 2049 by default (ensure firewall allows this)
- The `nobody:nogroup` user/group is standard for anonymous NFS access on Debian/Ubuntu
- Use `sync` mode for data integrity, `async` for performance (with risk)
- Always use `no_subtree_check` for better performance when possible
- For persistent mounts, add entries to `/etc/fstab` on the client
- NFSv4 is the current standard; older versions may have different configurations

## 🎓 Assignment Extensions

**Potential improvements for future versions:**
1. Implement NFSv4 with Kerberos authentication
2. Configure automatic mounting with `/etc/fstab`
3. Set up NFS with SELinux/AppArmor security contexts
4. Implement NFS monitoring and logging
5. Configure failover with multiple NFS servers
6. Benchmark NFS performance with different options
7. Implement NFS with encryption (NFS over SSH or TLS)

---

**Assignment Number:** 6  
**Difficulty Level:** Intermediate  
**Topics:** NFS, Network File Systems, Linux System Administration, Distributed Storage  
**Status:** ✅ Complete
