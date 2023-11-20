// Dynamate is a software that adds an animated character to your desktop
#include "render/Draw.hpp"

#define numVAOs 1
#define numVBOs 1

int windowWidth, windowHeight, monitorX, monitorY;
int width, height;

GLFWwindow* window;

void init() {
    std::cout << "Initializing...\n";
    if (!glfwInit()) {exit(EXIT_FAILURE);}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitors[0]);

    // width = 75% of the screen
    windowWidth = static_cast<int>(videoMode->width / 1.5);
    // aspect ratio 16 by 9
    windowHeight = static_cast<int>(videoMode->height / 16 * 9);

    glfwGetMonitorPos(monitors[0], &monitorX, &monitorY);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    
    window = glfwCreateWindow(600, 600, "Dynamate", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSetWindowPos(window, monitorX + (videoMode->width - windowWidth) / 2, monitorY + (videoMode->height - windowHeight) / 2);

    glfwShowWindow(window);

    if(glewInit() != GLEW_OK) {exit(EXIT_FAILURE);}
    glfwSwapInterval(1);
}

int main(void) {
    init();
    //init(window);

    std::cout << "Initializing rendering pipeline...\n";
    Draw draw(window, width, height);

    // comment following line to see the border of window
    //glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
    
    std::cout << "Beginning main program loop...\n";
    while(!glfwWindowShouldClose(window)) {
        //std::cout << "drawing\n";
        draw.startDrawing(glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
