#version 410

in vec3 iPosition;
in vec2 iTexcoord;
in vec3 iColor;

uniform mat4 uView;
uniform mat4 uProjection;

out vec2 Texcoord;
out vec3 Color;

void main()
{
    Texcoord = iTexcoord;
    Color = iColor;

    gl_Position = uProjection * uView * vec4(iPosition, 1.0);
}
