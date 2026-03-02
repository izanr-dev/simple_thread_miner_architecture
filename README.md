<div align="center">
  <h1>Proof of Work (PoW) Simulator</h1>
  <p><i>A multiprocess and multithreaded Proof of Work proof of concept in C</i></p>
</div>

<br>

## Description

[cite_start]This project is a Proof of Concept (PoC) developed in C using the POSIX standard[cite: 12]. [cite_start]It simulates the core mechanics of a Proof of Work (PoW) mining system[cite: 1001, 1002]. [cite_start]The application solves mathematical hashing challenges by brute force, efficiently distributing the computational workload[cite: 1004, 1006].

The architecture is built upon a **multiprocess** and **multithreaded** model:
- [cite_start]A **Miner** process that divides the search space among multiple parallel threads[cite: 1031, 1034].
- [cite_start]A **Logger** process that asynchronously listens through a unidirectional pipe and persists the validated blocks to disk[cite: 1041, 1042, 1044].

<br>

## Key Features

- [cite_start]**Scalable Concurrency**: Utilizes the `pthread` library to evenly divide the mathematical search space among the assigned threads[cite: 1011, 1034].
- [cite_start]**Inter-Process Communication (IPC)**: Implements message passing and synchronization between the miner and the logger using an anonymous pipe[cite: 1042].
- [cite_start]**Memory Management**: Structured to prevent memory leaks and orphan processes, ready for memory profiling[cite: 208, 316].
- [cite_start]**Data Persistence**: Automatic generation of structured `.log` files detailing each round, target, solution, votes, and the winner's PID[cite: 1044, 1045].

<br>

## Compilation and Usage

[cite_start]The project includes a `Makefile` to automate the build process, execution, and testing.

### Build the Project
To generate the executable, navigate to the project root and run:
```bash
make
