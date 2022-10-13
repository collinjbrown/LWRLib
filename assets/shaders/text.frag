#version 330 core

in vec4 rgbaColor;
in vec2 texCoords;

out vec4 color;

uniform sampler2D batchTextures[32];

void main()
{
    color = rgbaColor * texture(batchTextures[1], texCoords);
}
