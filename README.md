# Life Simulation

A visual implementation of **Conway's Game of Life** built with **C++ and SFML 3**.

The project simulates cellular automata on an interactive grid where cells evolve according to Conway's Game of Life rules.

## Features

- Interactive 25 × 25 grid
- Conway's Game of Life simulation
- Multiple predefined patterns:
    - Blinker
    - Glider
    - Beacon
    - Toad
    - Random Pattern
- Pause / Resume simulation
- Reset the grid
- Click cells to toggle them alive/dead
- Click and drag to draw alive cells
- Button hover effects
- Generation counter
- Alive cell counter
- Current pattern display
- Pixel-style UI
- CMake-based build system

## Tech Stack

- C++20
- SFML 3
- CMake
- Ninja
- MSYS2 / MinGW

## Preview

<img width="1000" height="682" alt="image" src="https://github.com/user-attachments/assets/1d99afcb-0957-47af-bedc-10e1c0392411" />
<img width="997" height="682" alt="image" src="https://github.com/user-attachments/assets/01c2a0e2-12d0-47c8-8ab5-513b4ae0c5ff" />
<img width="1000" height="683" alt="image" src="https://github.com/user-attachments/assets/72f0976e-96b6-4d42-be81-a6622a098a82" />

...

## How It Works

Each cell has two possible states:

- Alive
- Dead

Every generation, each cell checks its eight neighboring cells.

- Fewer than 2 neighbors → dies
- 2 or 3 neighbors → survives
- More than 3 neighbors → dies
- Exactly 3 neighbors → dead cell becomes alive

The next generation is calculated on a separate grid so that all cells update simultaneously.

...

## Project Structure

```text
life/
├── assets/
│   └── PixelifySans-Regular.ttf
│
├── include/
│   ├── CellState.h
│   ├── Game.h
│   ├── Grid.h
│   └── Pattern.h
│
├── src/
│   ├── Game.cpp
│   ├── Grid.cpp
│   └── main.cpp
│
├── CMakeLists.txt
├── README.md
└── .gitignore

```

## Installation

### Prerequisites

Make sure the following are installed:

- C++20 compatible compiler
- CMake
- Git
- MSYS2 / MinGW
- SFML 3

This project was developed using the **MSYS2 UCRT64** environment.

### 1. Clone the Repository

```
git clone https://github.com/ankushKumar143/life-simulation.git
cd life-simulation
```

### 2. Install SFML 3

If you are using the MSYS2 UCRT64 environment, install SFML with:

```
pacman -S mingw-w64-ucrt-x86_64-sfml3
```

Make sure you are using the **UCRT64 terminal** when installing and building the project.

### 3. Configure the Project

From the project root:

```
cmake -S . -B build
```

### 4. Build the Project

```
cmake --build build
```

After a successful build, the executable will be available at:

```
build/LifeSimulation.exe
```

### 5. Run the Application

From the project root:

```
./build/LifeSimulation.exe
```

You can also double-click `LifeSimulation.exe` inside the `build` folder.

## Controls

| Action         | Control           |
| -------------- | ----------------- |
| Pause / Resume | `Space`           |
| Blinker        | `1`               |
| Glider         | `2`               |
| Beacon         | `3`               |
| Toad           | `4`               |
| Random Pattern | `5`               |
| Reset          | `R`               |
| Toggle Cell    | Left Click        |
| Draw Cells     | Left Click + Drag |
