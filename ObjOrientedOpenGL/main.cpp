#include <string>
#include <cmath>
#include <iostream>
#include <cerrno>
#include <cstring>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VertexArray.h"
#include "ShaderProgram.h"

#define FLOAT_SIZE sizeof(GLfloat)

void framebufferSizeCallback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);
int init();
void renderLoop(ShaderProgram&, VertexArray&);
void cleanup();

int width = 800;
int height = 600;
std::string title = "Learn OpenGL";
GLFWwindow* window = nullptr;
std::string shaderPath = "shaders/basicShader";

std::vector<GLfloat> vertices = {
     0.5f,  0.5f, 0.0f,  // 0: top right pos
     0.5f,  0.0f, 0.0f,  // 0: top right color
     0.5f, -0.5f, 0.0f,  // 1: bottom right pos
     0.0f,  0.5f, 0.0f,  // 1: bottom right color
    -0.5f, -0.5f, 0.0f,  // 2: bottom left pos
     0.5f,  0.0f, 0.5f,  // 2: bottom left color
    -0.5f,  0.5f, 0.0f,  // 3: top left pos
     1.0f,  1.0f, 1.0f   // 3: top left color
};
std::vector<GLuint> indices = {  // note it goes clockwise!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

int main()
{
    int status = init();
    if (status == 0)
    {
        ShaderProgram shader(shaderPath);
        VertexArray vao(vertices, indices, GL_STATIC_DRAW);
        vao.enableAttribute(0, 3, 6, 0);
        vao.enableAttribute(1, 3, 6, 3);

        renderLoop(shader, vao);
        cleanup();
    }

    return status;
}

int init()
{
    //initialise and configure GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    //create window
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to initialise GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    //GLAD defines GL functions and points them to the system-specific spots.
    //we need glfwGetProcAddress to work properly for that.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialise GLAD" << std::endl;
        return -2;
    }

    return 0;
}

void renderLoop(ShaderProgram& shader, VertexArray& vao)
{
    glClearColor(0.2f, 0.5f, 0.5f, 1.0f); //GL_COLOR_BUFFER_BIT
    while(!glfwWindowShouldClose(window))
    {
    	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode. Default uses GL_FILL
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float time = glfwGetTime();
        float intensity = sin(time)*0.5f + 0.5f; //sin gives -1 to 1, so we remap it to 0 to 1

        shader.use();
        shader.setFloat("intensity", intensity);
        vao.bind();
        vao.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void cleanup()
{
    glfwTerminate();
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height){
    //first two parameters indicate where on the window (here lower left corner)
    //  we want the lower left corner of our viewport to be
    //third 'n' fourth are size of the viewport
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
    //GLFW_PRESS if currently pressed down. GLFW_RELEASE if not.
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}
