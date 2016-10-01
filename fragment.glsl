#version 150

uniform sampler2D tex;
in vec2 Texcoord;

out vec4 outColor;

void main()
{
    outColor = texture(tex, Texcoord);
}
