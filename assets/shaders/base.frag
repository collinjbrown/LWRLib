#version 330 core

in vec4 rgbaColor;
in vec2 texCoords;
in float texStart;
in vec2 archSize;

out vec4 color;

uniform sampler2D batchTextures[32];

void main()
{
    // vec2 coords = vec2(texStart / archSize

    color = rgbaColor * texture(batchTextures[0], texCoords);
}
