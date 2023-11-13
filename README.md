# C++ OpenGL Engine

## Overview
This C++ OpenGL Engine is a versatile and powerful tool for creating 3D applications and games. It leverages modern OpenGL for rendering and includes a range of features from basic model loading to complex GUI systems.

## Features
- Model loading and rendering
- Advanced GUI system with constraint-based layout
- Terrain generation and rendering
- Skybox rendering
- Collision detection system
- Extensible architecture for further development

## Getting Started

### Prerequisites
- CMake (version 3.19 or higher)
- A C++ compiler supporting C++17 (e.g., GCC, Clang, MSVC)
- OpenGL 4.3 or higher

### Dependencies
The project relies on several external libraries:
- **GLFW** for window creation and input handling
- **GLM** for mathematics
- **Assimp** for model loading
- **Freetype** for font rendering
- **SQLite** for database management
- **Quill** for logging

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/sovrinbloc/cpp-opengl-engine.git
   cd cpp-opengl-engine
   ```

2. Update submodules (for dependencies):
   ```bash
   git submodule update --init --recursive
   ```

3. Build the project using CMake:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

4. Run the executable generated in the `bin` directory.

## Usage
- The main application can be started by running the executable in the `bin` directory.
- Modify the `src/MainGameLoop.h` to change the initial setup of the game.

## Documentation
- Detailed documentation for each module is available in the `readmes` directory.
- For specific implementation details, refer to the inline comments in the source files.

## Contributing
Contributions to the project are welcome. Please follow these steps:
1. Fork the repository.
2. Create a new branch for your feature (`git checkout -b feature/AmazingFeature`).
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4. Push to the branch (`git push origin feature/AmazingFeature`).
5. Open a pull request.

## Roadmap
- [ ] Networking implementation for multiplayer support
- [ ] Enhanced collision detection for complex scenarios
- [ ] Character creation and customization system
- [ ] NPC creation with AI behaviors
- [ ] Pathfinding algorithms for NPC navigation
- [ ] Quest system implementation
- [ ] Skill system development
- [ ] Account management system

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments
- Special thanks to all the contributors and maintainers of the dependencies used in this project.

---

Certainly! Merging the provided README content with the template I created earlier will give a more comprehensive overview of your project, including detailed installation instructions and dependency management. Here's the merged README:

---

# C++ OpenGL Engine

## Overview
This C++ OpenGL Engine is a versatile and powerful tool for creating 3D applications and games. It leverages modern OpenGL for rendering and includes a range of features from basic model loading to complex GUI systems.

## Features
- Model loading and rendering
- Advanced GUI system with constraint-based layout
- Terrain generation and rendering
- Skybox rendering
- Collision detection system
- Extensible architecture for further development

## Getting Started

### Prerequisites
- CMake (version 3.19 or higher)
- A C++ compiler supporting C++17 (e.g., GCC, Clang, MSVC)
- OpenGL 4.3 or higher

### Dependencies Overview
- OpenGL
- GLM
- GLFW
- ASSIMP-4
- FreeType2

### Installing Dependencies
Most of the installation is done through downloading and installing dependencies, and making sure they are correctly included within the CMakeLists.txt.

#### GLFW
- `GLFW 3.3 (glfw3)`: https://github.com/glfw/glfw

#### Assimp
- `assimp 4.0.1`: https://github.com/assimp/assimp/releases/tag/v4.1.0

#### GLM
- `glm (GLM 0.9.9.9)`:  `brew install glm` and link. Or: https://github.com/g-truc/glm.git

#### SQLite
- `sqlite3`: `brew install sqlite` and `ln -s ...`

#### FreeType
- Download version 2.11.0 from `https://download.savannah.gnu.org/releases/freetype/freetype-2.11.0.tar.gz`
- `./autogen.sh`
- Configure without `brotli`
   - `./configure --without-harfbuzz --without-brotli`
- Generate a folder: `cmake -E make_directory build`
- Build `cmake -E chdir build cmake ..`
- Add to cmake:
    ```
    include_directories(deps/ft2)
    add_subdirectory(deps/ft2)
    include_directories(deps/ft2/include)
    target_link_libraries(engine freetype)
    ```

#### For The Laptop
```
if(EXISTS deps/glrequired)
 message(STATUS "Requiring OpenGL")
 find_package(OpenGL REQUIRED)
 target_link_libraries(engine glfw)
 target_link_libraries(engine OpenGL::GL)
endif()
```

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/sovrinbloc/cpp-opengl-engine.git
   cd cpp-opengl-engine
   ```

2. Update submodules (for dependencies):
   ```bash
   git submodule update --init --recursive
   ```

3. Build the project using CMake:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

4. Run the executable generated in the `bin` directory.

## Usage
- The main application can be started by running the executable in the `bin` directory.
- Modify the `src/MainGameLoop.h` to change the initial setup of the game.

## Documentation
- Detailed documentation for each module is available in the `readmes` directory.
- For specific implementation details, refer to the inline comments in the source files.

## Links
- [Contents of Project](readmes/CONTENTS.md)
- [Usage](readmes/USAGE.md)

## Contributing
Contributions to the project are welcome. Please follow these steps:
1. Fork the repository.
2. Create a new branch for your feature (`git checkout -b feature/AmazingFeature`).
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4. Push to the branch (`git push origin feature/AmazingFeature`).
5. Open a pull request.

## Roadmap
- [ ] Networking implementation for multiplayer support
- [ ] Enhanced collision detection for complex scenarios
- [ ] Character creation and customization system
- [ ] NPC creation with AI behaviors
- [ ] Pathfinding algorithms for NPC navigation
- [ ] Quest system implementation
- [ ] Skill system development
- [ ] Account management system

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments
- Special thanks to all the contributors and maintainers of the dependencies used in this project.

---