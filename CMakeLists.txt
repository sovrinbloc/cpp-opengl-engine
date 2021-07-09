cmake_minimum_required(VERSION 3.19)
project(engine)

set(CMAKE_CXX_STANDARD 14)

add_executable(engine src/main.cpp src/RenderEngine/DisplayManager.h src/EngineTester/MainGameLoop.h src/Entities/Camera.h src/Models/RawModel.h src/RenderEngine/Loader.h src/RenderEngine/EntityRenderer.h src/Textures/TextureLoader.h src/Shaders/ShaderProgram.h src/Shaders/StaticShader.h src/Libraries/images/stb_image.h src/Textures/ModelTexture.h src/Models/TexturedModel.h src/Toolbox/FileSystem.h src/Toolbox/Maths.h src/Entities/Entity.h src/Entities/CameraInput.h src/RenderEngine/ObjLoader.h src/RenderEngine/Vertex.h src/RenderEngine/ModelData.h src/Toolbox/Debug.h src/Entities/Light.h src/RenderEngine/MasterRenderer.h src/Toolbox/Utils.h src/Terrain/Terrain.h src/Shaders/TerrainShader.h src/RenderEngine/TerrainRenderer.h src/RenderEngine/RenderStyle.h src/Entities/Camera.cpp src/EngineTester/MainGameLoop.cpp src/RenderEngine/DisplayManager.cpp src/Entities/CameraInput.cpp src/Terrain/Terrain.cpp src/Textures/TextureLoader.cpp src/Textures/ModelTexture.cpp src/Shaders/ShaderProgram.cpp src/Toolbox/FileSystem.cpp src/Shaders/StaticShader.cpp src/Shaders/TerrainShader.cpp src/RenderEngine/EntityRenderer.cpp src/RenderEngine/Loader.cpp src/RenderEngine/MasterRenderer.cpp src/RenderEngine/ObjLoader.cpp src/RenderEngine/TerrainRenderer.cpp src/RenderEngine/SceneLoader.h src/RenderEngine/MeshData.h src/Shaders/ModelShader.cpp src/Shaders/ModelShader.h src/Entities/Scene.h src/RenderEngine/SceneRenderer.h src/Textures/TerrainTexture.h src/Textures/TerrainTexturePack.h)

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