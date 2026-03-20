# Modular Physics Simulation with Python Controls

This project simulates a 2D particle system using a C++ physics engine and a Python interface for control, visualization, and GUI interaction.

## 🚀 Features

- C++ core engine for fast physics computation
- Python bindings via `pybind11`
- Tkinter GUI for adding particles and controlling simulation
- Real-time visualization with Matplotlib or Canvas
- Save/load particle states as JSON
- Export visual snapshots of simulation

## 🗂️ Structure
    Build
    # 1. Install pybind11
    pip install pybind11
    
    # 2. Configure and build
    mkdir build && cd build
    cmake .. -DCMAKE_PREFIX_PATH=$(python -c "import pybind11; print(pybind11.get_cmake_dir())")
    make -j$(nproc)
    
    # The .so is placed in python/ automatically
