# Assignment-1: Client-Server Socket Communication

## 📝 Assignment Overview

This assignment implements a **basic TCP client-server communication system** using Winsock2 (Windows Sockets 2) in C. The program demonstrates fundamental concepts of network programming including socket creation, connection establishment, message transmission, and proper resource cleanup.

## 🎯 Objectives

- Implement socket programming using Winsock2 API
- Create a TCP server that listens for client connections
- Create a TCP client that connects to the server
- Exchange messages between client and server
- Implement comprehensive error handling
- Practice resource management (socket cleanup)

## 🏗️ Architecture

```
┌──────────────────────────────────────┐
│         SERVER (server.c)            │
├──────────────────────────────────────┤
│ 1. Initialize Winsock               │
│ 2. Create socket                    │
│ 3. Bind to PORT 8080                │
│ 4. Listen for connections           │
│ 5. Accept client connection         │
│ 6. Receive message from client      │
│ 7. Send response to client          │
│ 8. Close connection and cleanup     │
└──────────────────────────────────────┘
           ↕ TCP Connection (PORT 8080)
┌──────────────────────────────────────┐
│         CLIENT (client.c)            │
├──────────────────────────────────────┤
│ 1. Initialize Winsock               │
│ 2. Create socket                    │
│ 3. Connect to server at 127.0.0.1   │
│ 4. Send message to server           │
│ 5. Receive response from server     │
│ 6. Close connection and cleanup     │
└──────────────────────────────────────┘
```

## 📂 Files

| File | Purpose |
|------|---------|
| `server.c` | TCP server implementation |
| `client.c` | TCP client implementation |
| `README.md` | This documentation file |

## 🔧 Configuration

**Port Number:** `8080`  
**Server IP:** `127.0.0.1` (localhost)  
**Protocol:** TCP (SOCK_STREAM)  
**Protocol Family:** IPv4 (AF_INET)

## 💻 Source Code Summary

### server.c
- **Key Functions:**
  - `WSAStartup()` - Initialize Windows Sockets
  - `socket()` - Create TCP socket
  - `bind()` - Bind socket to port
  - `listen()` - Listen for incoming connections
  - `accept()` - Accept client connection
  - `recv()` - Receive data from client
  - `send()` - Send data to client
  - `closesocket()` - Close socket
  - `WSACleanup()` - Cleanup Winsock

- **Features:**
  - Error checking at each step
  - Displays client IP address and port
  - Handles connection termination gracefully
  - Null-terminated buffer handling

### client.c
- **Key Functions:**
  - `WSAStartup()` - Initialize Windows Sockets
  - `socket()` - Create TCP socket
  - `connect()` - Connect to server
  - `send()` - Send message to server
  - `recv()` - Receive response from server
  - `closesocket()` - Close socket
  - `WSACleanup()` - Cleanup Winsock

- **Features:**
  - IP address validation
  - Connection status messages
  - Proper error reporting
  - Automatic cleanup on errors

## 🔨 Compilation

### Prerequisites
- MinGW (GCC compiler for Windows) with Winsock2 support
- Windows Sockets 2 library (Ws2_32.lib)

### Compile Commands

**Server:**
```bash
gcc.exe -fdiagnostics-color=always -g server.c -o server.exe -lws2_32
```

**Client:**
```bash
gcc.exe -fdiagnostics-color=always -g client.c -o client.exe -lws2_32
```

### Compilation Flags Explained
- `-fdiagnostics-color=always` - Colored compiler output
- `-g` - Include debugging symbols
- `-lws2_32` - Link against Winsock2 library

## 🚀 Execution

### Step 1: Open Two Terminal Windows

### Step 2: Terminal 1 - Start Server
```bash
cd Assignment-1
.\server.exe
```

**Expected Output:**
```
Server is listening on port 8080...
Client connected from IP: 127.0.0.1, Port: <random_port>
Client: Hello from Client
Server: Hello from Server
Server closed.
```

### Step 3: Terminal 2 - Run Client
```bash
cd Assignment-1
.\client.exe
```

**Expected Output:**
```
Connected to server at 127.0.0.1:8080
Client: Hello from Client
Server: Hello from Server
Client closed.
```

## 📊 Program Flow

```
SERVER FLOW:
┌─────────────────────────────┐
│ WSAStartup()                │
└──────────┬──────────────────┘
           ↓
┌─────────────────────────────┐
│ Create Socket (AF_INET)     │
└──────────┬──────────────────┘
           ↓
┌─────────────────────────────┐
│ Bind to Port 8080           │
└──────────┬──────────────────┘
           ↓
┌─────────────────────────────┐
│ Listen for connections      │
└──────────┬──────────────────┘
           ↓
┌─────────────────────────────┐
│ Accept client connection    │
└──────────┬──────────────────┘
           ↓
┌─────────────────────────────┐
│ Receive message from client │
└──────────┬──────────────────┘
           ↓
┌─────────────────────────────┐
│ Send response to client     │
└──────────┬──────────────────┘
           ↓
┌─────────────────────────────┐
│ Close socket & WSACleanup   │
└─────────────────────────────┘


CLIENT FLOW:
┌─────────────────────────────┐
│ WSAStartup()                │
└──────────┬──────────────────┘
           ↓
┌─────────────────────────────┐
│ Create Socket (AF_INET)     │
└──────────┬──────────────────┘
           ↓
┌─────────────────────────────┐
│ Connect to 127.0.0.1:8080   │
└──────────┬──────────────────┘
           ↓
┌─────────────────────────────┐
│ Send message to server      │
└──────────┬──────────────────┘
           ↓
┌─────────────────────────────┐
│ Receive response from server│
└──────────┬──────────────────┘
           ↓
┌─────────────────────────────┐
│ Close socket & WSACleanup   │
└─────────────────────────────┘
```

## 🔍 Key Features

### Error Handling
- **WSAStartup()** return value check
- **Socket creation** validation
- **Connection** error reporting
- **Send/Recv** operation error checking
- **Resource cleanup** on all error paths

### Buffer Management
- Fixed-size buffers: 1024 bytes
- Null termination for string safety
- Proper buffer bounds checking

### Communication Protocol
- **Direction:** Bidirectional (full-duplex)
- **Message Format:** Plain text strings
- **Server Message:** "Hello from Server"
- **Client Message:** "Hello from Client"

## 🧪 Testing

### Basic Test Case
1. Start server → Should show "Server is listening on port 8080..."
2. Start client → Should connect and exchange messages
3. Both programs should terminate gracefully with status code 0

### Error Cases Handled
- Server startup failure
- Socket creation failure
- Connection refused
- Invalid IP address
- Network errors during send/recv
- Client disconnect

## 📚 Concepts Covered

| Concept | Description |
|---------|-------------|
| **Socket** | Endpoint for network communication |
| **Server** | Passive endpoint that listens for connections |
| **Client** | Active endpoint that initiates connections |
| **TCP** | Reliable, connection-oriented protocol |
| **Port** | Identifies the service on a host |
| **Bind** | Associate socket with IP address and port |
| **Listen** | Place socket in passive listening mode |
| **Accept** | Accept incoming client connections |
| **Connect** | Initiate connection to server |
| **Send/Recv** | Exchange data over connection |

## 🔗 Related Concepts

- **Winsock2 API** - Windows Sockets API for network programming
- **Socket Programming** - Low-level network communication
- **Network Protocols** - TCP/IP stack
- **Inter-Process Communication (IPC)** - Communication between processes
- **System Programming** - Low-level system calls

## 📖 Learning Resources

- [Winsock2 Documentation](https://docs.microsoft.com/en-us/windows/win32/winsock/about-winsock)
- [Socket Programming Guide](https://www.tutorialspoint.com/unix_sockets/)
- [TCP/IP Protocol Suite](https://en.wikipedia.org/wiki/Internet_protocol_suite)

## ✅ Checklist

- [x] Socket creation and initialization
- [x] Server-side binding and listening
- [x] Client-side connection establishment
- [x] Bidirectional message exchange
- [x] Error handling and validation
- [x] Proper resource cleanup
- [x] Cross-platform compatibility (Windows-focused)
- [x] Buffer management and safety

## 📝 Notes

- This implementation is synchronous and handles one client at a time
- For multiple concurrent clients, use threading or asynchronous I/O
- The server terminates after serving one client
- Both programs use `127.0.0.1` (localhost) for testing

## 🎓 Assignments Extensions

**Potential improvements for future versions:**
1. Multi-threaded server to handle multiple clients
2. Message protocol with headers and payload
3. File transfer between client and server
4. Authentication and encryption
5. Asynchronous I/O with event-driven architecture
6. Connection pooling and keep-alive

---

**Assignment Number:** 1  
**Difficulty Level:** Beginner  
**Topics:** Socket Programming, TCP/IP, Winsock2, C Programming  
**Status:** ✅ Complete

