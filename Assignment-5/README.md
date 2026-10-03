# Assignment 5 - Bully Election Algorithm

This assignment implements the **Bully Election Algorithm** for selecting a coordinator in a distributed system.

## Project Files

- `server.c`
  - C server implementation using Winsock2
  - Implements the Bully Election Algorithm
  - Takes input: number of processes, their active/failed status, and which process detects failure
  - Runs the recursive election() function to find the new coordinator

- `client.c`
  - C client that connects to the server
  - Receives the elected coordinator process ID

- `README.md`
  - This documentation file

## Project Description

The Bully Election Algorithm is used in distributed systems to elect a coordinator (leader) when the current coordinator fails. Key concepts:

- Each process has a unique ID
- The process with the highest ID becomes the coordinator
- When a process detects failure, it sends election messages to all higher-ID processes
- If no response → it becomes coordinator
- If response received → higher process takes over

## How to Run

1. Open a terminal in the Assignment-5 folder.
2. Compile the C files:
   ```bash
   gcc -fdiagnostics-color=always -g server.c -o server.exe -lws2_32
   gcc -fdiagnostics-color=always -g client.c -o client.exe -lws2_32
   ```
3. Start the server:
   ```bash
   .\server.exe
   ```
4. Open another terminal and run the client:
   ```bash
   .\client.exe
   ```
5. The server will prompt for input, then the client connects and receives the coordinator information

## Input Format

The server will prompt you to enter:
- **Number of processes**: Total processes in the system
- **Status of each process**: `1` = Active, `0` = Failed
- **Process which detects failure**: The ID of the process initiating the election

## Expected Output

**Server:**
```
Initializing Winsock...
Winsock initialized successfully.
Socket created successfully.
Binding successful. Server listening on port 8080...
Enter number of processes: 5
Enter status of each process (1 = Active, 0 = Failed):
Process 0: 1
Process 1: 1
Process 2: 0
Process 3: 1
Process 4: 1
Enter the process which detects failure: 1

Process 1 is initiating election...
Process 1 sends election message to Process 2
Process 2 is inactive, skipping
Process 1 sends election message to Process 3
Process 3 sends election message to Process 4
Current Coordinator is Process 4
Response sent to client.
Server closed.
```

**Client:**
```
Initializing Winsock...
Winsock initialized successfully.
Socket created successfully.
Connected to server at 127.0.0.1:8080
Sending message: Bully Election Client
Received from server: Coordinator elected: Process 4
Client closed.
```

## Learning Objective

This assignment helps understand:
- Bully Election Algorithm concepts
- Leader election in distributed systems
- Failure detection and recovery
- Process coordination and message passing
- Recursive algorithm implementation in C