#version 410

in vec3 Color;
in vec3 Normal;
in vec2 Texcoord;

uniform sampler2D uTexture;

out vec4 oColor;

void main()
{
    oColor = texture(uTexture, Texcoord) * vec4(Color, 1.0);
}
