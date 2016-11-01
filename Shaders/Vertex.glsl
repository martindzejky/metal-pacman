#version 410

in vec3 iPosition;
in vec3 iColor;
in vec3 iNormal;
in vec2 iTexCoord;
in vec3 iTangent;

uniform mat4 uView;
uniform mat4 uModelView;
uniform mat4 uModelViewProjection;
uniform mat3 uNormal;

out vec3 EyePosition;
out vec3 EyeNormal;
out vec3 Color;
out vec2 TexCoord;
out mat3 TBN;

out vec3 LightEyePosition;


// calculate all things necessary for the fragment shader
// and also the vertex position
void main()
{
    const vec3 lightWorldPosition = vec3(1.0, 2.4, -4.0);
    vec4 lightPosition = uView * vec4(lightWorldPosition, 1.0);
    LightEyePosition = lightPosition.xyz / lightPosition.w;

    vec4 position = uModelView * vec4(iPosition, 1.0);
    EyePosition = position.xyz / position.w;
    EyeNormal = normalize(uNormal * iNormal);

    Color = iColor;
    TexCoord = iTexCoord;

    vec3 bitangent = cross(iTangent, iNormal);
    vec3 T = normalize(uNormal * iTangent);
    vec3 B = normalize(uNormal * bitangent);
    vec3 N = normalize(uNormal * iNormal);
    TBN = mat3(T, B, N);

    gl_Position = uModelViewProjection * vec4(iPosition, 1.0);
}
