Here’s the updated README file that includes information about the chunk system based on the Winter.dev article:

---

# Falling Sand Cellular Automata

Welcome to the **Falling Sand Cellular Automata** project! This simulation is inspired by popular games like **Noita** and **Powder Toy**, developed using **C++** and **SDL**. The focus is on creating a sandbox environment where particles fall and interact in a basic manner, demonstrating simple gravitational behavior without complex interactions.

The chunk system used in this project is based on the techniques outlined in a [Winter.dev article](https://winter.dev/articles/falling-sand-worlds), which provides a robust framework for managing particles efficiently in a grid-based environment.

## Features

- **Dynamic Particle Simulation**: Particles fall and interact with gravity, creating an engaging visual experience.
- **Fluid Simulation**: Observe how fluid particles behave as they flow through the environment.
- **Basic Fire Effect**: Includes a simple fire particle that adds an interesting visual element.

### Demonstration GIFs

- **Sand and Water Simulation**  
  ![Sand and Water](https://github.com/Toast7529/FallingSandCellularAutomata/blob/main/doc/SandWater.gif)

- **Fire Simulation**  
  ![Fire](https://github.com/Toast7529/FallingSandCellularAutomata/blob/main/doc/Fire.gif)

## Controls

- **Left Mouse Button**: Add a particle at the mouse cursor location.
- **Right Mouse Button**: Remove a particle at the mouse cursor location.
- **Scroll Wheel**: Increase or decrease the brush size.
- **1**: Select sand.
- **2**: Select water.
- **3**: Select wall.
- **4**: Select steam.
- **5**: Select fire.
- **6**: Select smoke.
- **7**: Select wood.

## To-Do List / Bug Fixes

- Fix the dirty rectangle implementation (Partially implemented).
- Improve fluid movement for smoother simulation.
- Restore wood to solid status (currently moving for debugging purposes).
- Implement multithreading for better performance.
- Add reactions between different particles for more complex interactions.
- Prevent sand from clipping through floors when velocity is high.
- Handle different particle densities.
