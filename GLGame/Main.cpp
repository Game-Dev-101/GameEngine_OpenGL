#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "Texture2D.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

using namespace std;

#pragma region GLOBAL_VARIABLES
bool wireframeMode = false;

#pragma region KINDS_OF_SHAPES
/* Making a Rectangle */
// Define vertices for rectangle
GLfloat verticesRectangle[] = {
    -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // Bottom Left (0); Red Color; UV Bottom Left
    -0.5f, 0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // Top Left (1); Green Color; UV Top Left
    0.5f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // Top Right (2); Blue Color; UV Top Right
    0.5f, -0.5f, 0.0f,      1.0f, 1.0f, 1.0f,   1.0f, 0.0f // Bottom Right (3); White Color; UV Bottom Right
};

// Define indices for rectangle
GLuint indicesRectangle[] = {
    0, 1, 2, // Upper Triangle
    0, 2, 3 // Lower Triangle
};


/* Making a Triangle */
// Define vertices for Triangle
float verticesTriangle[] = {
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // Bottom Right, with red color on vertex
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // Bottom Left, with green color on vertex
     0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // Top, with blue color on vertex 
};

// Define indices for Triangle
unsigned int indicesTriangle[] = {
    0, 1, 2
};
#pragma endregion
#pragma endregion

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
    // Initialize OpenGL
    if (!glfwInit())
    {
        cout << "ERROR: Cannot start the Aplication" << endl;
        return -1;
    }

    // Configuring which OpenGL version be used
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifndef __APPLE__ // Only for apple device
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create window object
    GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL Game Engine", NULL, NULL);
    if (window == NULL)
    {
        cout << "ERROR: Failed to create a window object" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load GLAD to configure OpenGL
    gladLoadGL();

    // Get Version Information
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    cout << "Renderer: " << renderer << " | Version: " << version << endl;

    // Set viewport dimensions
    glViewport(0, 0, 1280, 720);

    // Register a window resize event callback
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);


#pragma region Create Shape in OpenGL
    /* Source from https://learnopengl.com/Getting-started/Hello-Triangle */

    /* SUMMARY: To draw object in OpenGL
    * 1. Bind Vertex Array Object (VAO)
    * glBindVertexArray(vao);
    *
    * 2. Copy vertices array in a buffer to be used by OpenGL
    * glBindBuffer(GL_ARRAY_BUFFER, vbo);
    * glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    *
    * 3. Set vertex attribute pointer
    * glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    * glEnableVertexAttribArray(0);
    *
    * 4. Draw the Object
    * glUseProgram(shaderProgram);
    * glBindVertexArray(vao);
    * glDrawArrays(GL_TRIANGLES, 0, 3);
    */

    // Create Shader Program
    Shader shader = Shader("./default_shader.glvsh", "./default_shader.glfsh");

    // Create VBO, VAO, and EBO
    VAO vao = VAO();
    vao.Bind();

    VBO vbo = VBO(verticesRectangle, sizeof(verticesRectangle));
    EBO ebo = EBO(indicesRectangle, sizeof(indicesRectangle));

    // Create a linker between vertices by create vertex attribute pointer
    vao.LinkAttribute(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);

    // Create a color attribute pointer
    vao.LinkAttribute(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    // Create a coordinate for texture placement
    vao.LinkAttribute(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    vao.Unbind();
    vbo.Unbind();
    ebo.UnBind();

#pragma endregion

#pragma region PLACE_TEXTURE
    Texture2D texture = Texture2D("./Risitas.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    texture.TextureUnit(shader, "tex0", 0);
    
#pragma endregion

    // Application loop
    while (!glfwWindowShouldClose(window))
    {
        // Inputs
        processInput(window);

        // Render commands
        glClearColor(0.2f, 0.16f, 0.04f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //// Add Uniform Shader
        //float timeValue = (float)glfwGetTime();
        //float alphaColor = (sin(timeValue) / 2.0f) + 0.5f;
        //int vertexColorLocation = glGetUniformLocation(shader.ID, "colorTime");
        //glUniform1f(vertexColorLocation, alphaColor);

        // Draw Rectangle with Photo
        shader.activateShader();
        texture.Bind();
        vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);

        // Handle GLFW events
        glfwPollEvents();
    }

    // Delete all objects that have been created
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shader.deleteProgram();

    // Delete window before ending the program
    glfwDestroyWindow(window);

    // When application was closed then clean it up by terminate it
    glfwTerminate();

    return 0;
}


#pragma region SOURCE_FUNCTIONS
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        wireframeMode = !wireframeMode;
        glPolygonMode(GL_FRONT_AND_BACK, wireframeMode ? GL_LINE : GL_FILL);
    }
}
#pragma endregion