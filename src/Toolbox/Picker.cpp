//
// Created by Joseph Alai on 7/26/21.
//

#include "Picker.h"
#include "../Entities/CameraInput.h"
#include "GLFW/glfw3.h"

/**
 * Calculating a Ray from the Mouse
 *
 * All ray casting starts with a ray. In this case it has an origin O at the position of the camera. We can do ray
 * intersections in any space (world, eye, etc.), but everything needs to be in the same space - let's assume that
 * we are doing our calculations in world space. This means that our ray origin is going to be the world x,y,z
 * position of the camera.
 *
 * @param projectionMatrix
 * @param viewMatrix
 * @return
 */
glm::vec3 Picker::calculateMouseRay(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
    glm::vec2 normalizedCoords = getNormalizedDeviceCoords();
    glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
    glm::vec4 eyeCoords = toEyeCoords(clipCoords, projectionMatrix );
    glm::vec3 worldCoords = toWorldCoords(eyeCoords, viewMatrix);
    return worldCoords;
}

/**
 * World Coordinates
 *
 * This should balance the up-and-down, left-and-right, and forwards components for us. So, assuming our camera is
 * looking directly along the -Z world axis, we should get [0,0,-1] when the mouse is in the centre of the screen, and
 * less significant z values when the mouse moves around the screen. This will depend on the aspect ratio, and field-of-
 * view defined in the view and projection matrices. We now have a ray that we can compare with surfaces in world space.
 *
 * @param eyeCoords
 * @param viewMatrix
 * @return
 */
glm::vec3 Picker::toWorldCoords(glm::vec4 eyeCoords, glm::mat4 viewMatrix) {
    glm::vec3 rayWorld = glm::inverse(viewMatrix) * eyeCoords;
    return glm::normalize(rayWorld);
}

/**
 * Eye (Camera) Coordinates
 *
 * Normally, to get into clip space from eye space we multiply the vector by a projection matrix. We can go backwards by
 * multiplying by the inverse of this matrix. Then, we only needed to un-project the x,y part, so let's manually set the
 * z,w part to mean "forwards, and not a point".
 *
 * @param clipCoords
 * @param projectionMatrix
 * @return
 */
glm::vec4 Picker::toEyeCoords(glm::vec4 clipCoords, glm::mat4 projectionMatrix) {
    glm::vec4 invertedProjection = glm::inverse(projectionMatrix) * clipCoords;
    return glm::vec4(invertedProjection.x, invertedProjection.y, -1.0f, 0.0f);
}

/**
 * Normalized Device Coordinates
 * range [-1:1, -1:1, -1:1]
 *
 * The next step is to transform it into 3d normalised device coordinates. This should be in the ranges of x [-1:1] y
 * [-1:1] and z [-1:1]. We have an x and y already, so we scale their range, and reverse the direction of y.
 *
 * @return
 */
glm::vec2 Picker::getNormalizedDeviceCoords() {
    float x = (2.0f * static_cast<float>(InputMaster::mouseX)) / static_cast<float>(DisplayManager::Width()) - 1;
    float y = (2.0f * static_cast<float>(InputMaster::mouseY)) / static_cast<float>(DisplayManager::Height()) - 1;
    return glm::vec2(x, -y);
}

/**
 * Get Color on Mouse Position
 *
 * Locates on the rendered image, where the mouse is positioned, and gets the color of it.
 *
 * @return
 */
Color Picker::getColor() {
    unsigned char pixel[4];
    glFlush();
    glFinish();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    int width, height;
    glfwGetFramebufferSize(DisplayManager::window, &width, &height);
    glReadPixels(static_cast<int>(width / DisplayManager::Width() * static_cast<int>(InputMaster::mouseX)),
                 static_cast<int>(static_cast<int>(height) - (height / DisplayManager::Height() * static_cast<int>(InputMaster::mouseY))), 1, 1, GL_RGBA,
                 GL_UNSIGNED_BYTE, pixel);
    return Color(pixel[0], pixel[1], pixel[2], pixel[3]);
}