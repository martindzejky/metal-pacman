#version 410

in vec2 Texcoord;
in vec3 Color;

out vec4 oColor;

void main()
{
    oColor = vec4(Color, 1.0);
}
