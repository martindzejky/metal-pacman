#version 410

in vec3 Color;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D uTexture;
uniform mat4 uModel;

out vec4 oColor;

void main()
{
    vec4 correctNormal = uModel * vec4(Normal, 1.0);
    float light = 0.5 + correctNormal.x * 0.1 + correctNormal.y * 0.3 + correctNormal.z * 0.1;
    oColor = texture(uTexture, TexCoord) * vec4(Color * light, 1.0);
}
