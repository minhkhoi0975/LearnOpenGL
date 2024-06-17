#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void OnFramebufferResized(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow *window);

// settings
constexpr unsigned int SCREEN_WIDTH = 1920;
constexpr unsigned int SCREEN_HEIGHT = 1080;
constexpr char* WINDOW_TITLE = "LearnOpenGL";


int main()
{
    // Initialize GLFW.
    if (!glfwInit())
    {
		std::cout << "Cannot initialize GLFW." << std::endl;
		glfwTerminate();
		return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create a window.
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, OnFramebufferResized);

    // Initialize GLAD.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    // Run the render loop.
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ProcessInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        
    }

    glfwTerminate();
    return 0;
}

void ProcessInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void OnFramebufferResized(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}