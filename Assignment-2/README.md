# Assignment 2 - Remote Method Invocation (RMI) Calculator

This assignment demonstrates a simple Java RMI (Remote Method Invocation) application that allows a client to call arithmetic methods on a remote server.

## Project Files

- Calculator.java
  - Defines the remote interface.
  - Contains methods for addition, subtraction, multiplication, and division.

- CalculatorImpl.java
  - Implements the remote calculator methods.
  - Runs on the server side.

- RMIServer.java
  - Starts the RMI registry and binds the calculator service.

- RMIClient.java
  - Connects to the server and calls the remote methods.

## Features

The calculator supports the following operations:
- Addition
- Subtraction
- Multiplication
- Division

The client is now interactive and asks the user to choose an operation and enter two numbers before sending the request to the remote server.

## How to Run

1. Open a terminal in the Assignment-2 folder.
2. Compile the Java files:
   ```bash
   javac *.java
   ```
3. Start the server:
   ```bash
   java RMIServer
   ```
4. Open another terminal and run the client:
   ```bash
   java RMIClient
   ```
5. When prompted, enter:
   - the operation number (1-4)
   - the first number
   - the second number

## Expected Output

The client will display the result of the selected arithmetic operation performed remotely.

## Learning Objective

This assignment helps understand:
- Java RMI concepts
- Remote interfaces
- Server-client communication in Java
- Basic distributed computing
