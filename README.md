# DCC - Distributed Cloud Computing Lab Work

A comprehensive collection of assignments and lab work for the **Distributed Cloud Computing (DCC)** course (Semester 7).

## 📋 Overview

This repository contains practical implementations and lab assignments focusing on distributed systems, cloud computing concepts, and network programming using C/C++.

## 🎯 Learning Objectives

- Understand distributed system architecture and communication
- Implement client-server applications using socket programming
- Work with network protocols and inter-process communication
- Develop proficiency in C/C++ for system-level programming
- Build scalable and efficient distributed systems

## 📁 Repository Structure

```
DCC-LabWork/
├── Assignment-1/          # Basic Client-Server Communication
├── Assignment-2/          # (Upcoming)
├── Assignment-3/          # (Upcoming)
├── .gitignore            # Git ignore file for C/C++ projects
└── README.md             # This file
```

## 🔧 Prerequisites

### Software Requirements
- **GCC Compiler** - MinGW for Windows or native GCC for Linux/Mac
- **Windows Sockets 2 (Winsock2)** - For Windows socket programming
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
```

## 🚀 Quick Start

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

## 📚 Assignment Details

Each assignment folder contains:
- Source code files (.c / .cpp)
- Detailed README with implementation explanation
- Expected output and test cases

### Assignment-1: Client-Server Socket Communication
Basic implementation of TCP socket communication where a client connects to a server, sends a message, and receives a response. Includes comprehensive error handling and Winsock2 initialization.

[→ See Assignment-1 Details](./Assignment-1/README.md)

## 🛠️ Build & Compilation

### General Command
```bash
gcc -g filename.c -o output.exe -lws2_32
```

### With Debug Symbols
```bash
gcc -fdiagnostics-color=always -g filename.c -o output.exe -lws2_32
```

## 📝 Notes

- All assignments are implemented in **C** using **Winsock2** for cross-platform compatibility
- Comprehensive error handling is implemented in all programs
- Code follows best practices for socket programming and resource management

## 🤝 Contributing

This is an educational repository. Modifications and improvements are welcome for learning purposes.

## 📜 License

Academic use only.

---

**Course:** Distributed Cloud Computing (DCC)  
**Semester:** 7  
**Institution:** [Your College Name]

