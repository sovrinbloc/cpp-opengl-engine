cmake_minimum_required(VERSION 3.19)
project(engine)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_EXE_LINKER_FLAGS "-v")

add_executable(engine src/main.cpp src/RenderEngine/DisplayManager.h src/EngineTester/MainGameLoop.h src/Entities/Camera.h src/Models/RawModel.h src/RenderEngine/Loader.h src/RenderEngine/EntityRenderer.h src/Textures/TextureLoader.h src/Shaders/ShaderProgram.h src/Shaders/StaticShader.h src/Libraries/images/stb_image.h src/Textures/ModelTexture.h src/Models/TexturedModel.h src/Util/FileSystem.h src/Toolbox/Maths.h src/Entities/Entity.h src/Entities/CameraInput.h src/RenderEngine/ObjLoader.h src/RenderEngine/Vertex.h src/RenderEngine/ModelData.h src/Util/Debug.h src/Entities/Light.h src/RenderEngine/MasterRenderer.h src/Util/Utils.h src/Terrain/Terrain.h src/Shaders/TerrainShader.h src/RenderEngine/TerrainRenderer.h src/RenderEngine/RenderStyle.h src/Entities/Camera.cpp src/EngineTester/MainGameLoop.cpp src/RenderEngine/DisplayManager.cpp src/Entities/CameraInput.cpp src/Terrain/Terrain.cpp src/Textures/TextureLoader.cpp src/Textures/ModelTexture.cpp src/Shaders/ShaderProgram.cpp src/Util/FileSystem.cpp src/Shaders/StaticShader.cpp src/Shaders/TerrainShader.cpp src/RenderEngine/EntityRenderer.cpp src/RenderEngine/Loader.cpp src/RenderEngine/MasterRenderer.cpp src/RenderEngine/ObjLoader.cpp src/RenderEngine/TerrainRenderer.cpp src/RenderEngine/SceneLoader.h src/RenderEngine/MeshData.h src/Shaders/ModelShader.cpp src/Shaders/ModelShader.h src/Entities/Scene.h src/RenderEngine/SceneRenderer.h src/Textures/TerrainTexture.h src/Textures/TerrainTexturePack.h src/Entities/Player.h src/Entities/Player.cpp src/Entities/PlayerCamera.h src/Terrain/HeightMap.h src/Terrain/HeightMap.cpp src/Entities/PlayerCamera.cpp src/RenderEngine/MeshData.cpp src/RenderEngine/SceneLoader.cpp src/Guis/GuiTexture.h src/Guis/GuiTexture.cpp src/Guis/GuiRenderer.cpp src/Guis/GuiRenderer.h src/Guis/GuiShader.cpp src/Guis/GuiShader.h src/Util/LightUtil.h src/Skybox/SkyboxShader.cpp src/Skybox/SkyboxShader.h src/Skybox/SkyboxRenderer.cpp src/Skybox/SkyboxRenderer.h src/Util/ColorNames.h src/Toolbox/MousePicker.cpp src/Toolbox/MousePicker.h)

include_directories(deps/glfw)
add_subdirectory(deps/glfw)
include_directories(deps/glfw/GLFW/include)

include_directories(deps/ft2)
add_subdirectory(deps/ft2)
include_directories(deps/ft2/include)
target_link_libraries(engine freetype)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

include_directories(deps/assimp-4)
add_subdirectory(deps/assimp-4)
include_directories(deps/assimp-4/include)

add_subdirectory(deps/quill)

target_link_libraries(engine glfw  ${GLFW_LIBRARIES} ${PNG_LIBRARY} assimp quill)
include_directories(deps/glm/glm)
target_link_libraries(engine glm)


add_subdirectory(deps/glm EXCLUDE_FROM_ALL)