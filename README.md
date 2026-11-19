# OS Lab

Coursework for an Operating Systems lab: lab reports, an assignment, a Linux command cheatsheet, and a few C++ programs that simulate OS concepts.

## Contents

| Item | What it is |
|------|------------|
| `Round_Robin_Algo.cpp` | Round Robin CPU scheduling. Reads the number of processes, the time quantum, and each process's arrival and burst times, then prints per-process waiting and turnaround times and their averages. |
| `lab11task2.cpp` | Lab 11, parts C and D: a segmentation simulator (segment table with base/limit, logical-to-physical address translation and segmentation-fault checks) and a hybrid segmentation + paging model. |
| `cheatsheet.html` | Linux command cheatsheet (standalone HTML page). |
| `Lab *.docx` / `*.pdf`, `lab*_60199.*` | Lab reports. |
| `assignment1-lab-60199.*` | Assignment 1. |
| `core_sim/`, `core_sim.zip` | Files from the OS kernel simulator semester project: compiled classes, the course project manual, and a zip archive of the project. The source code lives in the separate `core-sim` repository. |
| `.vscode/` | VS Code build/debug config for compiling C++ with MinGW g++ (MSYS2 UCRT64). |

## Building the C++ programs

With any C++ compiler, for example g++:

```bash
g++ Round_Robin_Algo.cpp -o Round_Robin_Algo
./Round_Robin_Algo

g++ lab11task2.cpp -o lab11task2
./lab11task2
```

Both programs are interactive and read their input from the console. In VS Code, the default build task in `.vscode/tasks.json` compiles the active file with `C:/msys64/ucrt64/bin/g++.exe`.

The repo also contains prebuilt Windows executables (`Round_Robin_Algo.exe`, `lab11task2.exe`).
