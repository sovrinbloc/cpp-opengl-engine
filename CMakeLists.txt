cmake_minimum_required(VERSION 3.19)
project(engine)

set(CMAKE_CXX_STANDARD 14)

add_executable(engine main.cpp renderEngine/DisplayManager.h engineTester/MainGameLoop.h entities/Camera.h models/RawModel.h renderEngine/Loader.h renderEngine/EntityRenderer.h textures/Texture.h shaders/ShaderProgram.h shaders/StaticShader.h libraries/images/stb_image.h textures/ModelTexture.h models/TexturedModel.h toolbox/FileSystem.h toolbox/Maths.h entities/Entity.h entities/CameraInput.h renderEngine/ObjLoader.h renderEngine/Vertex.h renderEngine/ModelData.h toolbox/Debug.h entities/Light.h renderEngine/MasterRenderer.h toolbox/Utils.h terrain/Terrain.h shaders/TerrainShader.h renderEngine/TerrainRenderer.h renderEngine/RenderStyle.h entities/Camera.cpp engineTester/MainGameLoop.cpp renderEngine/DisplayManager.cpp entities/CameraInput.cpp terrain/Terrain.cpp textures/Texture.cpp textures/ModelTexture.cpp shaders/ShaderProgram.cpp toolbox/FileSystem.cpp)

include_directories(deps/GLFW)
add_subdirectory(deps/glfw)

include_directories(deps/glfw/include)
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

include_directories(deps/assimp-4)
add_subdirectory(deps/assimp-4)
include_directories(deps/assimp-4/include)

add_subdirectory(deps/quill)

target_link_libraries(engine glfw ${GLFW_LIBRARIES} ${PNG_LIBRARY} assimp quill)
include_directories(deps/glm/glm)
target_link_libraries(engine  glm)
add_subdirectory(deps/glm EXCLUDE_FROM_ALL)