#version 150

in vec2 Texcoord;

uniform sampler2D uTexture;

out vec4 oColor;

void main()
{
    oColor = texture(uTexture, Texcoord);
}
