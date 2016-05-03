#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

void key_callback(GLFWwindow *window, int key, int scancode, int action,
        int mode);

const GLuint WIDTH = 800, HEIGHT = 600;

// shaders
const GLchar *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

const GLchar *fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

int main()
{
    cout << "Starting GLFW context, OpenGL 3.3\n";

    glfwInit();
    // set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL",
            nullptr, nullptr);
    if (window == nullptr) {
        cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    // --- Build and compile a shader program
    // create a vertex shader object
    // parameter: provide the type of shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // attach the shader source code to the shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    // compile the shader
    glCompileShader(vertexShader);
    // check if compilation was successful
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog
            << endl;
    }

    // repeat for fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    // check the compilation
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog
            << endl;
    }
    // in order to use shaders we need to link them to a shader program object
    // and then activate the program when rendering objects
    // create a program and return the ID ref to the program object
    GLuint shaderProgram = glCreateProgram();
    // attach the compiled shaders to the program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // link the shaders
    glLinkProgram(shaderProgram);
    // check if linking the shader program failed
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog
            << endl;
    }

    // now every shader and rendering call will use this program object and,
    // therefore, the shaders
    // delete the shaders objects once they have been linked into the program
    // object
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // -- set up a triangle
    // set up vertex data, buffers and attribute pointers
    // GLfloat vertices[] = {
    //  // First triangle
    //   0.5f,  0.5f,  // Top Right
    //   0.5f, -0.5f,  // Bottom Right
    //  -0.5f,  0.5f,  // Top Left
    //  // Second triangle
    //   0.5f, -0.5f,  // Bottom Right
    //  -0.5f, -0.5f,  // Bottom Left
    //  -0.5f,  0.5f   // Top Left
    //};
    // define vertices of the triangle in normalized device coordinates (NDC)
    GLfloat vertices1[] = {
        -1.0f, -0.5f, 0.0f, // left
        0.0f, -0.5f, 0.0f, // right
        -0.5f,  0.5f, 0.0f, // top
    };

    GLfloat vertices2[] = {
        0.0f, -0.5f, 0.0f, // left
        1.0f, -0.5f, 0.0f, // right
        0.5f,  0.5f, 0.0f  //top
    };

    // use vertex buffer objects (VBO) to store vertices in GPU's memory
    GLuint VBO, VAO, VBO2, VAO2;
    // generate a vertex array object (VAO)
    glGenVertexArrays(1, &VAO);
    glGenVertexArrays(1, &VAO2);
    // generate buffer ID
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO2);

    // bind the VAO with the prefered settings
    glBindVertexArray(VAO); // bind VAO
    // copy vertices array in a buffer for OpenGL to use
    // bind the buffer to GL_ARRAY_BUFFER: buffer type of VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // now every buffer call will be used to configure the currently bound
    // buffer: VBO
    // copy the previously defined vertex data into buffer's memory
    // The last parameter has three forms:
    // GL_STATIC_DRAW: the data will most likely not change at all or rarely
    // GL_DYNAMIC_DRAW: the data is likely to change a lot
    // GL_STREAM_DRAW: the data will change every time it is drawn
    // in our example the triangle does not change and stays the same for every
    // render call
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    // tell OpenGl how to interpret the vertex data (per vertex attribute)
    // parameters:
    // 1) which vertex attribute to configure (location = 0 in our example)
    // 2) size of vertex attribute: vec3 => attr is composed of 3 values
    // 3) type of data
    // 4) whether to normalize the data or not
    // 5) stride = space between consecutive vertex attribute sets (3 times the
    //      size of GLfloat and the array is tightly packed)
    //  6) offset of where the position data begins in the buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
            (GLvoid *)0);
    // enable the vertex attribute: since the defined VBO was bound before,
    // then the vertex attribute 0 is now associated with its vertex data
    glEnableVertexAttribArray(0);

    // the next is allowed: the call to glVertexAttribPointer registered VBO as
    // the currently bound vertex buffer object so afterwards we can safely
    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // unbind VAO (it is always good to unbind any buffer/array to prevent
    // strange bugs). Do not unbind the EBO, keep it bound to this VAO
    glBindVertexArray(0);

    // second triangle
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
            (GLvoid *)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // wireframe polygons
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // -- end set up the triangle

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // draw our first triangle
        // activate the program object
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // draw second triangle
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }
    // properly de-allocate all resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
        int mode) {
    (void)scancode; (void)mode;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
