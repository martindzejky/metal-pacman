#version 150

in vec2 iPosition;
in vec2 iTexcoord;

out vec2 Texcoord;

void main()
{
    Texcoord = iTexcoord;
    gl_Position = vec4(iPosition, 0.0, 1.0);
}
