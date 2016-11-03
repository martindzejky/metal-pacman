#version 410

in vec3 Color;
in vec2 TexCoord;

uniform sampler2D uTexture;

out vec4 oColor;


// get texture color for the fragment and apply vertex color
vec4 TextureColor() {
    return texture(uTexture, TexCoord) * vec4(Color, 1.0);
}


// map the depth to the shadow map
void main()
{
    oColor = TextureColor();
}
