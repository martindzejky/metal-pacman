#version 410

in vec3 iPosition;
in vec3 iColor;
in vec2 iTexCoord;

uniform mat4 uModelViewProjection;

out vec3 Color;
out vec2 TexCoord;

// calculate the vertex position
void main()
{
    Color = iColor;
    TexCoord = iTexCoord;
    gl_Position = uModelViewProjection * vec4(iPosition, 1.0);
}
