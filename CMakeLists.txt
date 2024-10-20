cmake_minimum_required(VERSION 3.19)
project(engine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable verbose linker output (optional)
set(CMAKE_EXE_LINKER_FLAGS "-v")

# -----------------------------------
# Define Executable and Sources
# -----------------------------------

add_executable(engine
        src/main.cpp
        src/RenderEngine/DisplayManager.h
        src/EngineTester/Main/MainGameLoop.h
        src/EngineTester/Main/MainGameLoop.cpp
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
        src/Guis/Texture/GuiTexture.h
        src/Guis/Texture/GuiTexture.cpp
        src/Guis/Texture/Rendering/GuiRenderer.cpp
        src/Guis/Texture/Rendering/GuiRenderer.h
        src/Guis/Texture/Rendering/GuiShader.cpp
        src/Guis/Texture/Rendering/GuiShader.h
        src/Util/LightUtil.h
        src/Skybox/SkyboxShader.cpp
        src/Skybox/SkyboxShader.h
        src/Skybox/SkyboxRenderer.cpp
        src/Skybox/SkyboxRenderer.h
        src/Util/ColorName.h
        src/Toolbox/MousePicker.cpp
        src/Toolbox/MousePicker.h
        src/Guis/Text/FontMeshCreator/TextMeshData.cpp
        src/Guis/Text/FontMeshCreator/TextMeshData.h
        src/Guis/Text/Rendering/FontShader.cpp
        src/Guis/Text/Rendering/FontShader.h
        src/Guis/Text/Rendering/FontRenderer.cpp
        src/Guis/Text/Rendering/FontRenderer.h
        src/Guis/Text/GUIText.cpp
        src/Guis/Text/GUIText.h
        src/Guis/Text/FontMeshCreator/Character.h
        src/Guis/Text/FontMeshCreator/Word.cpp
        src/Guis/Text/FontMeshCreator/Word.h
        src/Guis/Text/FontMeshCreator/Line.cpp
        src/Guis/Text/FontMeshCreator/Line.h
        src/Guis/Text/FontMeshCreator/FontModel.h
        src/Guis/Text/Rendering/TextMaster.cpp
        src/Guis/Text/Rendering/TextMaster.h
        src/Guis/Text/FontMeshCreator/TextMeshCreator.cpp
        src/Guis/Text/FontMeshCreator/TextMeshCreator.h
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
        src/Interfaces/Positionable.h
        src/Interfaces/Interactive.h
        src/Util/ColorName.cpp
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
        src/OpenGLWrapper/OpenGLUtils.cpp
        src/OpenGLWrapper/OpenGLUtils.h
        src/Toolbox/Color.h
        src/Toolbox/Color.cpp
        src/Collision/AABB.cpp
        src/Collision/AABB.h
        src/Toolbox/Noise.h
        src/Guis/Constraints/UiConstraints.cpp
        src/Guis/Constraints/UiConstraints.h
        src/Guis/Alpha.cpp
        src/Guis/Alpha.h
        src/Guis/UiContainer.h
        src/Guis/GuiComponent.cpp
        src/Guis/Container.h
        src/Guis/GuiComponent.h
        src/Guis/UiMaster.cpp
        src/Guis/UiMaster.h
        src/Guis/Rect/Rendering/RectRenderer.cpp
        src/Guis/Rect/Rendering/RectRenderer.h
        src/Guis/Rect/Rendering/RectShader.cpp
        src/Guis/Rect/Rendering/RectShader.h
        src/Guis/Rect/GuiRect.cpp
        src/Guis/Rect/GuiRect.h
        src/Toolbox/Logger/Log.h
        src/Toolbox/Logger/ANSI.hpp
        src/EngineTester/GUI/MainGuiLoop.cpp
        src/EngineTester/GUI/MainGuiLoop.h
        src/Guis/Components/ButtonUi.cpp
        src/Guis/Components/ButtonUi.h
        src/Guis/Constraints/UiConstraint.cpp
        src/Guis/Constraints/UiConstraint.h
        src/Guis/Constraints/UiPercentConstraint.h
        src/Guis/Constraints/UiPixelConstraint.h
        src/Guis/Constraints/Tools.h
        src/Guis/Constraints/UiNormalizedConstraint.h
        src/Guis/Text/FontMeshCreator/FontNames.h
        )

# -----------------------------------
# Find and Link Dependencies
# -----------------------------------

# **GLFW**
add_subdirectory(deps/glfw)
target_include_directories(engine PRIVATE deps/glfw/GLFW/include)
target_link_libraries(engine PRIVATE glfw)

# **OpenGL**
if(APPLE)
    find_library(OpenGL_LIBRARY OpenGL)
    if(OpenGL_LIBRARY)
        message(STATUS "Found OpenGL library: ${OpenGL_LIBRARY}")
        target_link_libraries(engine PRIVATE ${OpenGL_LIBRARY})
    else()
        message(FATAL_ERROR "OpenGL library not found")
    endif()
else()
    find_package(OpenGL REQUIRED)
    if(OPENGL_FOUND)
        message(STATUS "OpenGL found: ${OPENGL_LIBRARIES}")
        target_include_directories(engine PRIVATE ${OPENGL_INCLUDE_DIR})
        target_link_libraries(engine PRIVATE ${OPENGL_LIBRARIES})
    else()
        message(FATAL_ERROR "OpenGL not found")
    endif()
endif()

# **HarfBuzz**
include_directories(/usr/local/Cellar/harfbuzz/9.0.0/include/harfbuzz)
target_link_libraries(engine PRIVATE /usr/local/Cellar/harfbuzz/9.0.0/lib/libharfbuzz.dylib)

# **Brotli**
include_directories(/usr/local/Cellar/brotli/1.1.0/include)
target_link_libraries(engine PRIVATE
        /usr/local/Cellar/brotli/1.1.0/lib/libbrotlicommon.dylib
        /usr/local/Cellar/brotli/1.1.0/lib/libbrotlidec.dylib
        /usr/local/Cellar/brotli/1.1.0/lib/libbrotlienc.dylib
        )

# **Freetype2**
add_subdirectory(deps/freetype2)
target_include_directories(engine PRIVATE deps/freetype2/include)
target_link_libraries(engine PRIVATE freetype)

# **PNG**
find_package(PNG REQUIRED)
if(PNG_FOUND)
    target_include_directories(engine PRIVATE ${PNG_INCLUDE_DIR})
    target_link_libraries(engine PRIVATE ${PNG_LIBRARY})
else()
    message(FATAL_ERROR "PNG not found")
endif()

# **Assimp**
add_subdirectory(deps/assimp-4)
target_include_directories(engine PRIVATE deps/assimp-4/include)
target_link_libraries(engine PRIVATE assimp)

# **Quill**
add_subdirectory(deps/quill)
target_link_libraries(engine PRIVATE quill)

# **GLM** (Header-only, no need to link)
target_include_directories(engine PRIVATE deps/glm/glm)

# -----------------------------------
# Additional Settings (Optional)
# -----------------------------------

# Set verbose linker output
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -v")

# Include the source directory (if needed)
target_include_directories(engine PRIVATE src)

# -----------------------------------
# End of CMakeLists.txt
# -----------------------------------
