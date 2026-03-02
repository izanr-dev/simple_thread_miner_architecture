<div align="center">
  <h1>PoW Miner Architecture</h1>
  <p><i>A multiprocess and multithreaded Proof of Work based on miners</i></p>
</div>

<br>

## Description

This project is a Proof of Concept (PoC) developed in C using the POSIX standard. It simulates the core mechanics of a Proof of Work (PoW) mining system. The application solves mathematical hashing challenges by brute force, efficiently distributing the computational workload.

The architecture is built upon a **multiprocess** and **multithreaded** model:
- A **Miner** process that divides the search space among multiple parallel threads.
- A **Logger** process that asynchronously listens through a unidirectional pipe and persists the validated blocks to disk.

<br>

## Key Features

- **Scalable Concurrency**: Utilizes the `pthread` library to evenly divide the mathematical search space among the assigned threads.
- **Inter-Process Communication (IPC)**: Implements message passing and synchronization between the miner and the logger using an anonymous pipe.
- **Memory Management**: Structured to prevent memory leaks and orphan processes, ready for memory profiling.
- **Data Persistence**: Automatic generation of structured `.log` files detailing each round, target, solution, votes, and the winner's PID.

<br>

## Compilation

The project includes a `Makefile` to automate the build process. To generate the executable, navigate to the project root and run:
```bash
make
