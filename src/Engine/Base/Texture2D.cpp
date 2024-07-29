#include"Texture2D.h"

NAMESPACE_START

GLint getFormat(const TextureFormat& textureFormat) {

    switch (textureFormat)
    {
    case TextureFormat::RGBA:
    case TextureFormat::RGBA32F:
        return GL_RGBA;
    case TextureFormat::Depth24_Stencil8:
        return GL_DEPTH_STENCIL;
    default:
        return GL_RGBA;
    }
}

GLint getInternalformat(const TextureFormat& textureFormat) {

    switch (textureFormat)
    {
    case TextureFormat::RGBA:
        return GL_RGBA;
    case TextureFormat::RGBA32F:
        return GL_RGBA32F;
    case TextureFormat::Depth24_Stencil8:
        return GL_DEPTH24_STENCIL8;
    default:
        return GL_RGBA;
    }
}

GLint getDataType(const TextureFormat& textureFormat) {

    switch (textureFormat)
    {
    case TextureFormat::RGBA:
        return GL_UNSIGNED_BYTE;
    case TextureFormat::RGBA32F:
        return GL_FLOAT;
    case TextureFormat::Depth24_Stencil8:
        return GL_UNSIGNED_INT_24_8;
    default:
        return GL_UNSIGNED_BYTE;
    }
}

GLint getTexelFilter(const TexelFilter& texelFilter) {
    switch (texelFilter)
    {
    case TexelFilter::Linear:
        return GL_LINEAR;
    case TexelFilter::Nearest:
        return GL_NEAREST;
    default:
        return GL_LINEAR;
    }
}


Texture2D::Texture2D(const TextureUsage& usage, const TextureFormat& textureFormat, const int width, const int height) {

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, getInternalformat(textureFormat), width, height, 0, getFormat(textureFormat), getDataType(textureFormat), NULL);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, getTexelFilter(defaultSampler.minFilter));
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, getTexelFilter(defaultSampler.magFilter));

    glBindTexture(GL_TEXTURE_2D, 0);
}

NAMESPACE_END

