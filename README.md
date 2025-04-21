# Snake Game — RIPES Simulator (Computer Architecture Project)

This project implements the classic **Snake Game** using the **RIPES simulator**, as part of the *Computer Organization and Architecture* course. The main objective is to **evaluate performance impact** under different **cache memory configurations**.

## 🎯 Objective

Develop a Snake Game in C, running on the RIPES CPU simulator, using:

- **LED Matrix 0** as the display.
- **D-Pad 0** as the input controller.
- **Switch 0** to restart the game after a collision.

In addition to game functionality, the project will evaluate the **cache hit rate** across multiple cache configurations to analyze performance differences.

## 🕹️ Game Rules

- The player controls a **red-colored snake**, initially 2×2 in size (4 LEDs).
- **Apples** appear as 2×2 blocks (4 green LEDs).
- Eating an apple increases the snake's size to 2×4 LEDs.
- No score is tracked.
- The game ends when the snake collides with itself or a border.
- The game can be restarted using **Switch 0**.

## ⚙️ Technical Considerations

- Peripheral usage: `LED_MATRIX_0_BASE`, `D_PAD_0_*`, and `SWITCHES`.
- Written in C, compatible with the RIPES simulator's architecture.
- Visual rendering and input handling rely on system macros from `ripes_system.h`.

## 🧪 Cache Configuration Testing

The game's execution will be used to evaluate cache performance (hit rate) under the following configurations:

1. Direct-mapped, 4 lines
2. 2-way set-associative, 2 sets
3. Fully associative, 4 ways
4. Direct-mapped, 16 lines
5. 4-way set-associative, 4 sets
6. Fully associative, 16 ways

### Evaluation Questions

- What is the hit rate for each configuration?
- Which configuration shows the best performance?

## 📄 Deliverables

- Functional C implementation of the Snake Game.
- Screenshots and a flowchart of the algorithm.
- Report with analysis and individual conclusions.
---

📘 Este proyecto también está disponible en [Español](README.es.md)
