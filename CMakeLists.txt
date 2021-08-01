cmake_minimum_required(VERSION 3.19)
project(engine)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_EXE_LINKER_FLAGS "-v")
set(CMAKE_CXX_VISIBILITY_PRESET)

add_executable(engine
        src/main.cpp
        src/RenderEngine/DisplayManager.h
        src/EngineTester/MainGameLoop.h
        src/Entities/Camera.h
        src/Models/RawModel.h
        src/RenderEngine/Loader.h
        src/RenderEngine/EntityRenderer.h
        src/Textures/TextureLoader.h
        src/Shaders/ShaderProgram.h
        src/Shaders/StaticShader.h
        src/Libraries/images/stb_image.h
        src/Textures/ModelTexture.h
        src/Models/TexturedModel.h
        src/Util/FileSystem.h
        src/Toolbox/Maths.h
        src/Entities/Entity.h
        src/Entities/CameraInput.h
        src/RenderEngine/ObjLoader.h
        src/RenderEngine/Vertex.h
        src/RenderEngine/ModelData.h
        src/Util/Debug.h
        src/Entities/Light.h
        src/RenderEngine/MasterRenderer.h
        src/Util/Utils.h
        src/Terrain/Terrain.h
        src/Shaders/TerrainShader.h
        src/RenderEngine/TerrainRenderer.h
        src/RenderEngine/RenderStyle.h
        src/Entities/Camera.cpp
        src/EngineTester/MainGameLoop.cpp
        src/RenderEngine/DisplayManager.cpp
        src/Entities/CameraInput.cpp
        src/Terrain/Terrain.cpp
        src/Textures/TextureLoader.cpp
        src/Textures/ModelTexture.cpp
        src/Shaders/ShaderProgram.cpp
        src/Util/FileSystem.cpp
        src/Shaders/StaticShader.cpp
        src/Shaders/TerrainShader.cpp
        src/RenderEngine/EntityRenderer.cpp
        src/RenderEngine/Loader.cpp
        src/RenderEngine/MasterRenderer.cpp
        src/RenderEngine/ObjLoader.cpp
        src/RenderEngine/TerrainRenderer.cpp
        src/RenderEngine/AssimpEntityLoader.h
        src/RenderEngine/AssimpMeshData.h
        src/Shaders/AssimpStaticShader.cpp
        src/Shaders/AssimpStaticShader.h
        src/Entities/AssimpEntity.h
        src/RenderEngine/AssimpEntityRenderer.h
        src/Textures/TerrainTexture.h
        src/Textures/TerrainTexturePack.h
        src/Entities/Player.h
        src/Entities/Player.cpp
        src/Entities/PlayerCamera.h
        src/Terrain/HeightMap.h
        src/Terrain/HeightMap.cpp
        src/Entities/PlayerCamera.cpp
        src/RenderEngine/AssimpMeshData.cpp
        src/RenderEngine/AssimpEntityLoader.cpp
        src/Guis/GuiTexture.h
        src/Guis/GuiTexture.cpp
        src/Guis/GuiRenderer.cpp
        src/Guis/GuiRenderer.h
        src/Guis/GuiShader.cpp
        src/Guis/GuiShader.h
        src/Util/LightUtil.h
        src/Skybox/SkyboxShader.cpp
        src/Skybox/SkyboxShader.h
        src/Skybox/SkyboxRenderer.cpp
        src/Skybox/SkyboxRenderer.h
        src/Util/Colors.h
        src/Toolbox/MousePicker.cpp
        src/Toolbox/MousePicker.h
        src/FontMeshCreator/TextMeshData.cpp
        src/FontMeshCreator/TextMeshData.h
        src/FontRendering/FontShader.cpp
        src/FontRendering/FontShader.h
        src/FontRendering/FontRenderer.cpp
        src/FontRendering/FontRenderer.h
        src/FontMeshCreator/GUIText.cpp
        src/FontMeshCreator/GUIText.h
        src/FontMeshCreator/Character.h
        src/FontMeshCreator/Word.cpp
        src/FontMeshCreator/Word.h
        src/FontMeshCreator/Line.cpp
        src/FontMeshCreator/Line.h
        src/FontMeshCreator/FontModel.h
        src/FontRendering/TextMaster.cpp
        src/FontRendering/TextMaster.h
        src/FontMeshCreator/TextMeshCreator.cpp
        src/FontMeshCreator/TextMeshCreator.h
        src/BoundingBox/RawBoundingBox.h
        src/Models/RawData.h
        src/BoundingBox/BoundingBox.h
        src/BoundingBox/BoundingBoxRenderer.cpp
        src/BoundingBox/BoundingBoxRenderer.h
        src/BoundingBox/BoundingBoxShader.cpp
        src/BoundingBox/BoundingBoxShader.h
        src/BoundingBox/BoundingBoxIndex.cpp
        src/BoundingBox/BoundingBoxIndex.h
        src/Input/InputMaster.h
        src/Input/InputMaster.cpp
        src/Toolbox/TerrainPicker.cpp
        src/Toolbox/TerrainPicker.h
        src/Toolbox/Picker.cpp
        src/Toolbox/Picker.h
        src/RenderEngine/FrameBuffers.cpp
        src/RenderEngine/FrameBuffers.h
        src/RenderEngine/AssimpEntityRenderer.cpp
        src/RenderEngine/MeshData.h
        src/RenderEngine/BoundingBoxData.h
        src/Util/CommonHeader.h
        src/Toolbox/Screenshot.h
        src/Interfaces/Clickable.h
        src/Interfaces/Moveable.h
        src/Interfaces/Interactive.h
        src/Util/Colors.cpp
        src/Interaction/InteractiveModel.cpp
        src/Interaction/InteractiveModel.h
        src/Entities/Entity.cpp
        src/Entities/AssimpEntity.cpp
        src/Entities/Light.cpp
        src/World/World.cpp
        src/World/World.h
        src/World/HashMap.h
        src/World/Chunk.cpp
        src/World/Chunk.h
        src/World/Map.cpp
        src/World/Map.h
        src/World/Block.h
        src/World/WorldCommon.h
        )

if (EXISTS deps/glrequired)
    message(STATUS "Requiring OpenGL")
    find_package(OpenGL REQUIRED)
    target_link_libraries(engine glfw)
    target_link_libraries(engine OpenGL::GL)
endif ()

include_directories(deps/glfw)
add_subdirectory(deps/glfw)
include_directories(deps/glfw/GLFW/include)

include_directories(deps/freetype2)
add_subdirectory(deps/freetype2)
include_directories(deps/freetype2/include)
target_link_libraries(engine freetype)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

include_directories(deps/assimp-4)
add_subdirectory(deps/assimp-4)
include_directories(deps/assimp-4/include)

add_subdirectory(deps/quill)

target_link_libraries(engine glfw ${GLFW_LIBRARIES} ${PNG_LIBRARY} assimp quill)
include_directories(deps/glm/glm)
target_link_libraries(engine glm)


add_subdirectory(deps/glm EXCLUDE_FROM_ALL)