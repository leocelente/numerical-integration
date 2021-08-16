# Numerical Integration
Author: Leonardo Celente

# What is it?
Trying out coding my own numerical integration library, with the special purpose
of use in a future C++ implementation of Aerospace Simulations. I have a simulation
built using Python that lacks speed, I was considering just switching to Cython
but I had this idea of a cache aware, STL-heavy, implementation that I wanted to see if it 
could really be built like I imagined. 

## Design
The idea was to follow the advice to keep critical data close in memory. I used an array of structs
to keep information relevant to each simulated timestep. On the Python implementation I was trying
to decouple the integration from other parts such as logging of variables of interest, what I called
probing. This time I'm keeping everything that gets touched on the main loop adjacent in memory to 
improve cache utilization. 

The other key design aspect is the use of good third-party and the STL. What really motivated me
to do this was seeing integration as (what in Haskell we would call) a left fold. With that idea
was also the wish to make this implementation succinctly, (almost) like the functional programs you 
see around. To accomplish this I made heavy use of the STL algorithms.

# How do I build it?
## Dependencies
 - CMake 
 - C++20
 - Conan Package Manager
    - fmt
    - spdlog
    - catch2
    - ctre
    - cxxopts
    - range-v3

## Steps
```bash
mkdir build
cd build
cmake .. 
cmake --build . --config Debug
```

Executables should be in `build/bin`
