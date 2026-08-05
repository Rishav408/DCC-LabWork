# Assignment 3 - RPC Student Marks Service

This assignment implements a simple RPC program that returns student marks based on a student ID.

## Project Files

- `student.x`
  - RPC interface definition for the `student` structure and the `GETMARKS` remote procedure.
- `student.h`
  - RPC header file for client and server use.
- `student_server.c`
  - RPC server implementation with the service dispatch loop.
- `student_client.c`
  - RPC client that sends a student ID to the server and receives the marks.
- `Steps to run RPC Program.docx`
  - Original assignment instructions for setting up and running RPC.

## How It Works

The RPC service receives a `student` record containing an `id` and returns an integer representing the student's marks. The server computes marks as `id * 10`.

## Build and Run Instructions

### 1. Compile the server and client

If your system uses `libtirpc`:

```bash
gcc -o student_server student_server.c -ltirpc
gcc -o student_client student_client.c -ltirpc
```

If your system provides legacy RPC libraries:

```bash
gcc -o student_server student_server.c -lnsl
gcc -o student_client student_client.c -lnsl
```

### 2. Start the RPC server

```bash
sudo rpcbind
./student_server
```

### 3. Run the client in another terminal

```bash
./student_client <server_ip> <student_id>
```

Example:

```bash
./student_client 127.0.0.1 5
```

## Expected Output

On the client side, you should see:

```text
Student Marks for ID 5 = 50
```

## Notes

- If `rpcbind` is not installed, install it using your package manager. For Debian/Ubuntu:
  ```bash
  sudo apt update
  sudo apt install rpcbind rpcsvc-proto libtirpc-dev
  ```
- If `rpcgen` is available, you can still generate header/stub files from `student.x` for extra compatibility.

## Learning Objectives

- Understand RPC interface definition with `student.x`.
- Implement a simple RPC server and client in C.
- Register and execute remote procedures with `rpcbind`.
- Learn basic client-server communication using Sun RPC.
