Installing Dependencies: 
`deps/`

 - `GLFW 3.3 (glfw3)`: https://github.com/glfw/glfw
 - `assimp 4.0.1`: https://github.com/assimp/assimp/releases/tag/v4.1.0
 - `glm (GLM 0.9.9.9)`:  `brew install glm` and link. Or: https://github.com/g-truc/glm.git
 - `sqlite3`: `brew install sqlite` and `ln -s ...`

##FreeType 
 - `Freetype`: download version 2.11.0 from `https://download.savannah.gnu.org/releases/freetype/freetype-2.11.0.tar.gz` (the main freetype website)
 - `./autogen.sh`
 - Configure without `brotli`
    - `./configure --without-harfbuzz --without-brotli`
 - Generate a folder: `cmake -E make_directory build`
 - Build `cmake -E chdir build cmake ..`
 - Add to cmake
```
include_directories(deps/ft2)
add_subdirectory(deps/ft2)
include_directories(deps/ft2/include)
target_link_libraries(engine freetype)
```