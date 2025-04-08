# Kalah (Mancala) Game

## Overview
Kalah, also known as Mancala, is a strategic two-player board game that involves sowing seeds in an attempt to capture more seeds than your opponent. The game is played on a board with two sides, each containing six pits (houses) and a larger pit (store or kalah) at each end.

## Game Setup
- Each player has **6 pits** on their side and **1 store** (kalah).
- The game starts with **6 seeds** in each pit.

## Gameplay
1. Players take turns choosing a non-empty pit to sow seeds.
2. The chosen pit's seeds are distributed **counter-clockwise**, one seed per pit, skipping the opponent's store.
3. If the last seed lands in the player's store, they earn an additional turn.
4. If the last seed lands in an empty pit on the player's side and the opposite pit has seeds, the player captures both the last seed and the seeds from the opposite pit, placing them in their store.
5. The game ends when one player has no seeds left in their pits. The remaining seeds in the opponent's pits are moved to their store.

## Objective
The goal is to collect more seeds than your opponent in your store by the end of the game.

## Winning
The player with the most seeds in their store at the end of the game is declared the winner.

---

## How to Run the Game

To run this Kalah (Mancala) game on your system, follow these instructions based on your operating system.

## On Windows (using mysys2)

### 1. Install MSYS2
### 2. Install GTK+3
Open the MSYS2 terminal and run:
```bash
pacman -S mingw-w64-x86_64-gtk3
```
### 3. Write Your GTK Code
Save your GTK code in a file, e.g., game.c.
### 4. Compile the Code
In the MSYS2 terminal, navigate to the folder containing your game.c file, then compile it:
```bash
gcc `pkg-config --cflags gtk+-3.0` -o mancalagame game.c `pkg-config --libs gtk+-3.0`
```
pkg-config --cflags gtk+-3.0: Provides necessary compile flags for GTK+3.
pkg-config --libs gtk+-3.0: Links the GTK+3 library to your program.
mancalagame: The output executable file.
### 5. Run the Application
Run the compiled application using:
```bash
./mancalagame
```

## On macOS (Using Homebrew)

### 1. Install GTK+3
Run the following command in the Terminal to install GTK+3 using Homebrew:
```bash
brew install gtk+3
```
### 2. Write Your GTK Code
Save your GTK code in a file, e.g., game.c.
### 3. Compile the Code
Navigate to the directory where your game.c file is located, then run:
```bash
gcc `pkg-config --cflags gtk+-3.0` -o mancalagame game.c `pkg-config --libs gtk+-3.0`
```
pkg-config --cflags gtk+-3.0: Provides necessary compile flags for GTK+3.
pkg-config --libs gtk+-3.0: Links the GTK+3 library to your program.
mancalagame: The output executable file.
### 4. Run the Application
Run the compiled application using:
```bash
./mancalagame
```

## On Linux (Ubuntu/Debian-based)
### 1. Install GTK+3:
Open the terminal and run the following commands:
```bash
sudo apt update
sudo apt install libgtk-3-dev
```
### 2. Write your GTK code in a .c file, for example, main.c.
### 3. Compile the code:
In the terminal, navigate to the directory where main.c is located. Then compile it using:
```bash
gcc `pkg-config --cflags gtk+-3.0` -o mancalagame game.c `pkg-config --libs gtk+-3.0`
```
pkg-config --cflags gtk+-3.0: Provides necessary compile flags for GTK+3.
pkg-config --libs gtk+-3.0: Links the GTK+3 library to your program.
mancalagame: The output executable file.
### 4. Run the Application
Run the compiled application using:
```bash
./mancalagame
```









