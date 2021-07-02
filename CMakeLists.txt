cmake_minimum_required(VERSION 3.19)
project(engine)

set(CMAKE_CXX_STANDARD 14)

add_executable(engine main.cpp renderEngine/DisplayManager.h engineTester/MainGameLoop.h entities/InputManager.h entities/Camera.h models/RawModel.h renderEngine/Loader.h renderEngine/Renderer.h textures/Texture.h shaders/ShaderProgram.h shaders/StaticShader.h libraries/images/stb_image.h textures/ModelTexture.h models/TexturedModel.h toolbox/FileSystem.h toolbox/Maths.h entities/Entity.h entities/CameraInput.h)

include_directories(deps/GLFW)
add_subdirectory(deps/glfw)

include_directories(deps/glfw/include)
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

target_link_libraries(engine glfw ${GLFW_LIBRARIES} ${PNG_LIBRARY})
include_directories(deps/glm/glm)
target_link_libraries(engine  glm)
add_subdirectory(deps/glm EXCLUDE_FROM_ALL)