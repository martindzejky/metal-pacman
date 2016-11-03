#version 410
#define MAX_LIGHTS 16

in vec3 iPosition;
in vec3 iColor;
in vec3 iNormal;
in vec2 iTexCoord;
in vec3 iTangent;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uModelView;
uniform mat4 uModelViewProjection;
uniform mat3 uNormal;

uniform int uLightCount;
uniform vec3 uLightPositions[MAX_LIGHTS];
uniform mat4 uLightSpaces[MAX_LIGHTS];

out vec3 EyePosition;
out vec3 Color;
out vec2 TexCoord;
out mat3 TBN;

out vec3 LightEyePositions[MAX_LIGHTS];
out vec3 LightSpacePositions[MAX_LIGHTS];


// calculate all things necessary for the fragment shader
// and also the vertex position
void main()
{
    int maxLightCount = min(uLightCount, MAX_LIGHTS);
    for (int i = 0; i < maxLightCount; ++i) {
        vec4 lightPosition = uView * vec4(uLightPositions[i], 1.0);
        LightEyePositions[i] = lightPosition.xyz / lightPosition.w;

        vec4 fragLightSpacePosition = uLightSpaces[i] * uModel * vec4(iPosition, 1.0);
        LightSpacePositions[i] = fragLightSpacePosition.xyz / fragLightSpacePosition.w;
    }

    vec4 position = uModelView * vec4(iPosition, 1.0);
    EyePosition = position.xyz / position.w;

    Color = iColor;
    TexCoord = iTexCoord;

    vec3 bitangent = cross(iTangent, iNormal);
    vec3 T = normalize(uNormal * iTangent);
    vec3 B = normalize(uNormal * bitangent);
    vec3 N = normalize(uNormal * iNormal);
    TBN = mat3(T, B, N);

    gl_Position = uModelViewProjection * vec4(iPosition, 1.0);
}
