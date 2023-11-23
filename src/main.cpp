// Dynamate is a software that adds an animated character to your desktop
#include "Draw.hpp"
#include "render/DrawableObjectManager.hpp"
#include "utils/OGLSetup.hpp"

int windowWidth, windowHeight, monitorX, monitorY;
int width, height;

GLFWwindow* window;

DrawableObjectManager objManager;

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        std::cout << "x: " << x << ", y: " << y << std::endl;
        objManager.handleMouseClick(x, y);

    }
}

void initGLFW() {
    std::cout << "Initializing...\n";
    if (!glfwInit()) {exit(EXIT_FAILURE);} // this line needs to be called before any OpenGL calls. Make sure this happens before anything.

    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitors[0]);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    windowWidth = static_cast<int>(videoMode->width);
    // if width was smaller than monitor width, use videoMode->height / 16 * 9 for height, for an aspect ratio 16 by 9
    windowHeight = static_cast<int>(videoMode->height);

    glfwGetMonitorPos(monitors[0], &monitorX, &monitorY);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    window = glfwCreateWindow(windowWidth, windowHeight, "Dynamate", NULL, NULL);
    glfwMakeContextCurrent(window);
    //glfwSetWindowPos(window, monitorX + (videoMode->width - windowWidth) / 2, monitorY + (videoMode->height - windowHeight) / 2);
    glfwShowWindow(window);

    if(glewInit() != GLEW_OK) {exit(EXIT_FAILURE);}
    glfwSwapInterval(1);

    // comment following line to see the border of window
    glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);

    glfwSetMouseButtonCallback(window, MouseButtonCallback);
}

int main(void) {
    initGLFW();
    std::cout << "Initializing rendering pipeline...\n";
    Draw draw = Draw(objManager, windowWidth, windowHeight);

    std::cout << "Beginning main program loop...\n";
    while(!glfwWindowShouldClose(window)) {
        draw.startDrawing(glfwGetTime(), objManager);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
