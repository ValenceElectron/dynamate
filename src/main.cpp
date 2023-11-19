// A dynamic/animated wallpaper engine for Linux by ValenceElectron
#include "utils/OGLSetup.hpp"
#include "utils/Camera.hpp"

#define numVAOs 1
#define numVBOs 1

GLuint d4Program;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

Camera camera(0.0f, 0.0f, 10.0f);
float cameraX, cameraY, cameraZ;
float d4LocX, d4LocY, d4LocZ;
int windowWidth, windowHeight, monitorX, monitorY;
int width, height;

GLuint mLoc, vLoc, pLoc;
float aspect;
glm::mat4 pMat, vMat, mMat, tMat, rMat;

void SetupVertices() {
    float d4[36] = {
        -0.5f, -0.5f, -0.5f,    0.0f, -0.5f, 0.5f,      0.0f, 0.5f, 0.0f,                                   // Forward-left tri
        0.0f, -0.5f, 0.5f,      0.5f, -0.5f, -0.5f,     0.0f, 0.5f, 0.0f,                                   // Forward-right tri
        0.5f, -0.5f, -0.5f,     -0.5f, -0.5f, -0.5f,    0.0f, 0.5f, 0.0f,                                   // Backward tri
        0.0f, -0.5f, 0.5f,      -0.5f, -0.5f, -0.5f,    0.5f, -0.5f, -0.5f
    };

    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);

    // d4
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(d4), d4, GL_STATIC_DRAW);
}

void SetupProjMat(GLFWwindow* window) {
    // building perspective matrix
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float) width / (float) height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees
}

void init(GLFWwindow* window) {
    d4Program = OGLSetup::createShaderProgram("shaders/vertShader.glsl", "shaders/fragShader.glsl");
    //waycli.ConnectToServer();
    
    d4LocX = 0.0f; d4LocY = 0.0f; d4LocZ = 5.0f;

    SetupProjMat(window);
    SetupVertices();
}

void DisplayD4(double currentTime) {
    glUseProgram(d4Program);

    tMat = glm::translate(glm::mat4(1.0f), glm::vec3(d4LocX, d4LocY, d4LocZ));
    rMat = glm::rotate(glm::mat4(1.0f), 0.7f * (float) currentTime,  glm::vec3(0.0f, 1.0f, 0.0f));
    mMat = tMat * rMat;

     // uniform variables for MV and proj matrices
    mLoc = glGetUniformLocation(d4Program, "mMat");
    vLoc = glGetUniformLocation(d4Program, "vMat");
    pLoc = glGetUniformLocation(d4Program, "pMat");
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(mMat));
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 12);
}

void Draw(GLFWwindow* window, double currentTime) {
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Builds view matrix from the U, V, N, and C vectors held in the camera object.
    vMat = glm::inverse(glm::mat4(camera.GetU(), camera.GetV(), camera.GetN(), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)))
            * glm::translate(glm::mat4(1.0f), glm::vec3(-camera.GetC().x, -camera.GetC().y, -camera.GetC().z));

    DisplayD4(currentTime);
}

int main(void) {
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

    GLFWwindow* window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetWindowPos(window, monitorX + (videoMode->width - windowWidth) / 2, monitorY + (videoMode->height - windowHeight) / 2);

    glfwShowWindow(window);

    if(glewInit() != GLEW_OK) {exit(EXIT_FAILURE);}
    glfwSwapInterval(1);

    init(window);

    // comment following line to see the border of window
    glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);

    while(!glfwWindowShouldClose(window)) {
        Draw(window, glfwGetTime());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
