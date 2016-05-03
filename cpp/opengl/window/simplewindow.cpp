#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

void key_callback(GLFWwindow *window, int key, int scancode, int action,
        int mode);

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
    // initialize GLFW
    glfwInit();

    // --- configuring GLFW ---
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // explicitly declare the use of the core-profile: (result in "invalid
    // operation" errors when using old functionality
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // a user cannot resize the window
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // --- create a window object
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL",
            nullptr, nullptr);
    if (window == nullptr) {
        cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // register the callback
    glfwSetKeyCallback(window, key_callback);

    // initialize GLEW (manages function pointers for OpenGL) before calling
    // any OpenGL functions
    glewExperimental = GL_TRUE; // ensure the use of modern techniques
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    // size of the rendering window
    glViewport(0, 0, WIDTH, HEIGHT);

    // --- simple game loop
    // check if GLFW has been told to close
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // check for triggered events

        // Rendering
        // Set the color, clear the color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // swap the screen buffers
        glfwSwapBuffers(window);
    }

    // clean up and exit properly
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
        int mode) {
    (void)scancode; (void)mode;
    cout << key << endl;
    // when the escape key is pressed set the WindowShouldClose to true
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
