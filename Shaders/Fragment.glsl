#version 410

in vec2 Texcoord;
in vec3 Color;

uniform sampler2D uTexture;

out vec4 oColor;

void main()
{
    //oColor = vec4(Color, 1.0) * texture(uTexture, Texcoord);
    oColor = vec4(Color, 1.0);
}
