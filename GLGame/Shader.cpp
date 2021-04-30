#include "Shader.h"

std::string getFileContents(const char* filename)
{
    std::ifstream source(filename);

    if (!source.is_open())
    {
        std::cout << "File '" << filename << "' may not be exists!";
        throw(errno);
    }

    std::string dataSource = std::string((std::istreambuf_iterator<char>(source)), std::istreambuf_iterator<char>());
    source.close();
    return dataSource;
}

void Shader::compileError(unsigned int shader, const char* type)
{
    int compileSuccess;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        // Check shader compiling error
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);

        if (!compileSuccess)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR: Shader Compilation (SHADER_COMPILATION_FAILED)" << type << "\n" << infoLog << std::endl;
        }
    }
    else
    {
        // Check linking failed
        glGetProgramiv(ID, GL_LINK_STATUS, &compileSuccess);

        if (!compileSuccess)
        {
            glGetProgramInfoLog(ID, 1024, NULL, infoLog);
            std::cout << "ERROR: Linking Shader Program (SHADER_LINKING_ERROR)" << type << " \n" << infoLog << std::endl;
        }
    }
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexCode = getFileContents(vertexFile);
    std::string fragmentCode = getFileContents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Create vertex shader object that will be used in program
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Attach source code to the shader object
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    compileError(vertexShader, "VERTEX");

    // Create fragment shader object that will be used in program
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Attach source code to the shader object
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    compileError(fragmentShader, "FRAGMENT");

    // Create shader program
    ID = glCreateProgram();

    // Attach shader objects into the program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    compileError(ID, "PROGRAM");

    // Delete all the shaders after the program has been attached, it will no longer need it
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::activateShader()
{
    glUseProgram(ID);
}

void Shader::deleteProgram()
{
    glDeleteProgram(ID);
}

void Shader::setBool(const std::string& varName, bool value)
{

}

void Shader::setInt(const std::string& varName, int value)
{

}

void Shader::setFloat(const std::string& varName, float value)
{

}