#include "Texture2D.h"

Texture2D::Texture2D(const char* filename, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    type = texType;

    // Load Image Source
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load("./Risitas.png", &widthImg, &heightImg, &numColCh, 0);

    // Set texture slot at 0 (UV0)
    glGenTextures(1, &ID);
    glActiveTexture(slot);
    glBindTexture(texType, ID);

    // Set Closest or Linear
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Set how it will be repeated
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture clamping to canvas
    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(texType);

    stbi_image_free(bytes);
    glBindTexture(texType, 0);
}

void Texture2D::TextureUnit(Shader& shader, const char* uniform, GLuint unit)
{
    // Set uniform value for texture in fragment shader script
    GLuint tex0Uni = glGetUniformLocation(shader.ID, uniform);
    shader.activateShader();
    glUniform1i(tex0Uni, unit);
}

void Texture2D::Bind()
{
    glBindTexture(type, ID);
}

void Texture2D::Unbind()
{
    glBindTexture(type, 0);
}

void Texture2D::Delete()
{
    glDeleteTextures(1, &ID);
}