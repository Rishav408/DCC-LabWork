# DCC - Distributed Cloud Computing Lab Work

A comprehensive collection of assignments and lab work for the **Distributed Cloud Computing (DCC)** course (Semester 7).

## ?? Overview

This repository contains practical implementations and lab assignments focusing on distributed systems, cloud computing concepts, and network programming using C/C++.

## ?? Learning Objectives

- Understand distributed system architecture and communication
- Implement client-server applications using socket programming
- Work with network protocols and inter-process communication
- Develop proficiency in C/C++ for system-level programming
- Build scalable and efficient distributed systems
- Configure and manage Network File Systems (NFS)
- Implement distributed storage solutions

## ?? Repository Structure

```
DCC-LabWork/
+-- Assignment-1/          # Basic Client-Server Communication
+-- Assignment-2/          # RMI Calculator
+-- Assignment-3/          # RPC Student Marks Service
+-- Assignment-4/          # Lamport Logical Clock Algorithm
+-- Assignment-5/          # Bully Election Algorithm
+-- Assignment-6/          # NFS Configuration in Linux
+-- .gitignore            # Git ignore file for C/C++ projects
+-- README.md             # This file
```

## ?? Prerequisites

### Software Requirements

- **GCC Compiler** - MinGW for Windows or native GCC for Linux/Mac
- **Windows Sockets 2 (Winsock2)** - For Windows socket programming
- **Java JDK** - For RMI and Java-based assignments
- **NFS Packages** - nfs-kernel-server and nfs-common for Linux (Assignment-6)
- **VS Code** (Optional) - For development
- **Git** - For version control

### Installation

**Windows:**

```bash
# Install MinGW with Winsock2 support
# Download from: https://www.mingw-w64.org/
```

**Linux/Mac:**

```bash
# Install GCC
sudo apt-get install gcc  # Ubuntu/Debian
brew install gcc          # macOS

# Install NFS packages (for Assignment-6)
sudo apt-get install nfs-kernel-server nfs-common  # Ubuntu/Debian
```

## ?? Quick Start

### Assignment-1: Basic Client-Server Communication

**Compile:**
```bash
cd Assignment-1

# Server
gcc.exe -fdiagnostics-color=always -g server.c -o server.exe -lws2_32

# Client
gcc.exe -fdiagnostics-color=always -g client.c -o client.exe -lws2_32
```

**Run (in separate terminals):**

Terminal 1 - Server:
```bash
.\server.exe
```

Terminal 2 - Client:
```bash
.\client.exe
```

## ?? Assignment Details

Each assignment folder contains:
- Source code files (.c / .cpp)
- Detailed README with implementation explanation
- Expected output and test cases

### Assignment-1: Client-Server Socket Communication

Basic implementation of TCP socket communication where a client connects to a server, sends a message, and receives a response. Includes comprehensive error handling and Winsock2 initialization.

[? See Assignment-1 Details](./Assignment-1/README.md)

### Assignment-2: RMI Calculator

Java RMI (Remote Method Invocation) calculator that allows a client to call arithmetic methods on a remote server.

[? See Assignment-2 Details](./Assignment-2/README.md)

### Assignment-3: RPC Student Marks Service

RPC implementation in C that returns student marks based on a student ID using Sun RPC.

[? See Assignment-3 Details](./Assignment-3/README.md)

### Assignment-4: Lamport Logical Clock Algorithm

C implementation of Lamport Logical Clock for maintaining causal ordering in distributed systems using TCP/Socket programming.

[? See Assignment-4 Details](./Assignment-4/README.md)

### Assignment-5: Bully Election Algorithm

C implementation of Bully Election Algorithm for coordinator selection in distributed systems using TCP/Socket programming.

[? See Assignment-5 Details](./Assignment-5/README.md)

### Assignment-6: NFS Configuration in Linux

Linux NFS (Network File System) server and client configuration for sharing files over a network. Includes automated setup scripts, export configuration, mount point management, and verification of file sharing capabilities.

[? See Assignment-6 Details](./Assignment-6/README.md)

## ??? Build & Compilation

### General Command

```bash
gcc -g filename.c -o output.exe -lws2_32
```

### With Debug Symbols

```bash
gcc -fdiagnostics-color=always -g filename.c -o output.exe -lws2_32
```

## ?? Notes

- Assignments 1, 4, and 5 are implemented in **C** using **Winsock2** for cross-platform compatibility
- Assignment 2 uses **Java RMI** for remote method invocation
- Assignment 3 uses **C with Sun RPC** for remote procedure calls
- Assignment 6 is a **Linux shell script** based assignment for NFS configuration
- Comprehensive error handling is implemented in all programs
- Code follows best practices for socket programming and resource management

## ?? Contributing

This is an educational repository. Modifications and improvements are welcome for learning purposes.

## ?? License

Academic use only.

---

**Course:** Distributed Cloud Computing (DCC)  
**Semester:** 7  
**Institution:** [Your College Name]
