#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

// Error callback function
void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

// Key event callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

// Shader loader
unsigned long getFileLength(std::ifstream& file) {
    if (!file.good())
        return 0;

    unsigned long pos = file.tellg();
    file.seekg(0, std::ios::end);
    unsigned long len = file.tellg();
    file.seekg(std::ios::beg);

    return len;
}

int loadShader(char* filename, GLchar** shaderSource, unsigned long& len) {
    std::ifstream file;
    file.open(filename, std::ios::in); // Opens as ASCII

    // check filename is a file
    if (!file) return -1;

    len = getFileLength(file);

    // Check if there are contents inside the file
    if (len == 0) return -2;

    *shaderSource = new char[len + 1];
    if (*shaderSource == 0) return -3; // Can't reserve memory

    *shaderSource[len] = 0;

    unsigned int i = 0;
    while (file.good()) {
        *shaderSource[i] = file.get();
        if (!file.eof()) i++;
    }

    *shaderSource[i] = 0;

    file.close();
    return 0;
}

int unloadShader(GLubyte** shaderSource) {
    if (*shaderSource != 0)
        delete[] * shaderSource;
    *shaderSource = 0;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // Set minimum version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Set Error callback
    glfwSetErrorCallback(error_callback);

    // Set Key Callback, where to assign the key input from user
    glfwSetKeyCallback(window, key_callback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Check glew initialization
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    // Create 3 points made of 9 floats
    float points[] = {
        -0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    GLchar *vertex_shader, *fragment_shader;

    loadShader("../", );

    // Compile Shader
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    // Create Empty "Program" to attach the shader
    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_programme);
        glBindVertexArray(vao);

        // Draw Triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Poll for and process events */
        glfwPollEvents();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}