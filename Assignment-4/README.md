# Assignment 4 - Lamport Logical Clock Algorithm

This assignment implements the **Lamport Logical Clock Algorithm** for maintaining causal ordering in distributed systems.

## Project Files

- `server.c`
  - TCP server implementation using Winsock2
  - Implements Lamport Logical Clock: increments logical clock on each event
  - Runs on the server side, processes client requests

- `client.c`
  - Connects to the server and sends a message
  - Receives the current logical clock value from the server

- `README.md`
  - This documentation file

## Features

The Lamport Logical Clock algorithm demonstrates:
- Logical timestamp maintenance for event ordering
- Message passing effects on time synchronization
- How concurrent events are ordered in distributed systems

The server maintains a logical clock that increments:
- On initialization (starts at 0)
- On each event (message reception from client)
- The clock value is included in the response sent to the client

## How to Run

1. Open a terminal in the Assignment-4 folder.
2. Compile the C files:
   ```bash
   gcc -fdiagnostics-color=always -g server.c -o server.exe -lws2_32
   gcc -fdiagnostics-color=always -g client.c -o client.exe -lws2_32
   ```
3. Start the server:
   ```bash
   java RMIServer
   ```
4. Open another terminal and run the client:
   ```bash
   java RMIClient
   ```
5. The client connects and displays the server's logical clock value

## Expected Output

**Server:**
```
Initializing Winsock...
Winsock initialized successfully.
Socket created successfully.
Binding successful. Server listening on port 8080...
Client connected from IP: 127.0.0.1, Port: <port>
Received message from client: Hello from Client
After event 1, logical clock = 1
Response sent to client.
Server closed.
```

**Client:**
```
Initializing Winsock...
Winsock initialized successfully.
Socket created successfully.
Connected to server at 127.0.0.1:8080
Sending message: Hello from Client
Received from server: Message processed. Logical clock: 1
Client closed.
```

## Learning Objective

This assignment helps understand:
- Lamport Logical Clock concepts
- Causal ordering in distributed systems
- Message passing and timestamp synchronization
- Socket programming using Winsock2