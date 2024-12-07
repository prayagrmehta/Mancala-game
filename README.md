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

### 1. **Prerequisites**

You need to have GTK+3 installed to run this game. GTK+ is a library for creating graphical user interfaces.

### 2. **Installing GTK+3**

#### **On Ubuntu/Linux:**
To install GTK+3, run the following commands in the terminal:

```bash
sudo apt update
sudo apt install libgtk-3-dev
