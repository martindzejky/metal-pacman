#version 410

in vec3 iPosition;
in vec3 iColor;
in vec3 iNormal;
in vec2 iTexcoord;

uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uModel;

out vec3 Color;
out vec3 Normal;
out vec2 Texcoord;

void main()
{
    Color = iColor;
    Normal = iNormal;
    Texcoord = iTexcoord;

    gl_Position = uProjection * uView * uModel * vec4(iPosition, 1.0);
}
