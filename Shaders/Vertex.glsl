#version 410

in vec3 iPosition;
in vec3 iColor;
in vec3 iNormal;
in vec2 iTexCoord;

uniform mat4 uView;
uniform mat4 uModelView;
uniform mat4 uModelViewProjection;
uniform mat3 uNormal;

out vec3 EyePosition;
out vec3 EyeNormal;
out vec3 Color;
out vec2 TexCoord;

out vec3 EyeSun;

void main()
{
    vec3 sun = normalize(vec3(0.3, 1.0, 0.6));
    EyeSun = normalize(mat3(uView) * sun);

    vec4 position = uModelView * vec4(iPosition, 1.0);
    EyePosition = position.xyz / position.w;
    EyeNormal = normalize(uNormal * iNormal);

    Color = iColor;
    TexCoord = iTexCoord;

    gl_Position = uModelViewProjection * vec4(iPosition, 1.0);
}
