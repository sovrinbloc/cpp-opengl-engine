# Usage Overview

### Rendering 
- GUI Rendering
- Model Rendering
- Terrain Rendering

### Setup
- MasterRenderer for Models &amp; Terrain
- UiMaster for Rendering All UI Related
- TextMaster for other Font Rendering

### Containerized Rendering
- Text Renderer
- GuiRenderer (Textures &amp; Images)
- FontRenderer (Text Rendering)
- RectRenderer (Rectangle Renderer for GUI)
- TerrainRenderer (Terrain Rendering)
- EntityRenderer (Model Rendering)

### Examples of what each class holds
- Entity
    - Model
    - Texture
- Terrain
    - Model
    - Texture
- Text
    - Font
    - Text
    - Color
- Gui
    - Rect
    - Texture / Image
    - Color
- Bounding Box
    - Uses mainly generated cubes around the model from high and low points
    - These are rendered off screen
    - The color assigned to them is used to ID them
        - the color itself is unique to the box
        - the box is unique to the model
        - when clicked, we get the color -> box -> model

### GUI
- Gui is containerized or not 
- You can place them each in their own container
- They can each have their own constraints
- They can be hidden, which hides their children
- They can be layerized, which means rendered in order.

