# Metal Pacman

This is a school project for my Graphics class. It's a Pacman remake in metal-and-rust style. I wrote my own C++ engine for the game. I used [Blender](https://www.blender.org/) to make the models.

## Compiling and running

You will need [Conan](https://conan.io/) to download the project dependencies. Also make sure you
have OpenGL, [CMake](https://cmake.org/) and `gcc`.

```
conan install --build missing

mkdir build
cd build
cmake ..
cmake --build .
cd ..

./build/bin/MetalPacman
```

