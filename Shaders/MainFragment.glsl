#version 410
#define MAX_LIGHTS 16

in vec3 EyePosition;
in vec3 Color;
in vec2 TexCoord;
in mat3 TBN;

in vec3 LightEyePositions[MAX_LIGHTS];
in vec3 LightSpacePositions[MAX_LIGHTS];

uniform sampler2D uTexture;
uniform sampler2D uNormalMap;
uniform sampler2D uReflectionMap;
uniform sampler2D uShadowMap;

uniform int uLightCount;
uniform vec3 uLightColors[MAX_LIGHTS];
uniform float uLightRadiuses[MAX_LIGHTS];

out vec4 oColor;


const float gamma = 2.2;


// calculate the fog color and mix it with the final fragment color
vec4 MixFog(vec4 color) {
    const vec4 fogColor = vec4(0.008, 0.006, 0.002, 1.0);
    const float e = 2.71828182845904523536028747135266249;

    float fogDensity = 0.03;
    float fog = pow(e, -pow(length(EyePosition) * fogDensity, 2));

    return mix(fogColor, color, fog);
}


// gamma-correct a color
vec4 GammaCorrect(vec4 color) {
    return vec4(pow(color.rgb, vec3(1.0 / gamma)), color.a);
}


// get texture color for the fragment and apply vertex color
vec4 TextureColor() {
    vec4 color = texture(uTexture, TexCoord) * vec4(Color, 1.0);
    return vec4(pow(color.rgb, vec3(gamma)), color.a);
}


// look into the normal map and get the normal
vec3 NormalMapNormal() {
    vec3 normalMapColor = texture(uNormalMap, TexCoord).rgb;
    return normalize(normalMapColor * 2.0 - 1.0);
}


// calculate how much this fragment is in the shadow of the light
float Shadow(int light) {
    return 1.0;
}


// ambient light
vec4 AmbientLight() {
    return vec4(0.01, 0.007, 0.004, 1.0);
}


// diffuse light based on the lights in the scene
vec4 DiffuseLight(vec3 normal) {
    vec3 finalColor = vec3(0.0, 0.0, 0.0);

    int maxLightCount = min(uLightCount, MAX_LIGHTS);
    for (int i = 0; i < maxLightCount; ++i) {
        vec3 lightDir = LightEyePositions[i] - EyePosition;
        float lightDistance = length(lightDir);
        float diffuse = max(dot(normal, normalize(lightDir)), 0.0);

        vec3 lightFinal = uLightColors[i] * diffuse;
        float att = clamp(1.0 - lightDistance * lightDistance / (uLightRadiuses[i] * uLightRadiuses[i]), 0.0, 1.0);
        lightFinal *= att * att;

        finalColor += lightFinal * Shadow(i);
    }

    return vec4(finalColor, 1.0);
}


// specular highlights
vec4 SpecularLight(vec3 normal) {
    const float strength = 0.7;
    const int shininess = 64;

    vec3 finalColor = vec3(0.0, 0.0, 0.0);

    int maxLightCount = min(uLightCount, MAX_LIGHTS);
    for (int i = 0; i < maxLightCount; ++i) {
        vec3 reflectionColor = texture(uReflectionMap, TexCoord).rgb;
        float reflection = (reflectionColor.r + reflectionColor.g + reflectionColor.b) / 3;

        vec3 viewDir = normalize(-EyePosition);
        vec3 lightDir = LightEyePositions[i] - EyePosition ;
        float lightDistance = length(lightDir);
        vec3 halfwayDir = normalize(normalize(lightDir) + viewDir);

        float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
        vec3 specColor = uLightColors[i] * spec * strength;
        float att = clamp(1.0 - lightDistance * lightDistance / (uLightRadiuses[i] * uLightRadiuses[i]), 0.0, 1.0);
        vec3 finalSpecColor = specColor * att * att * reflection;

        finalColor += finalSpecColor * Shadow(i);
    }

    return vec4(finalColor, 1.0);
}


// make the final fragment color
void main()
{
    vec4 texColor = TextureColor();

    vec3 normal = texture(uNormalMap, TexCoord).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    normal = normalize(TBN * normal);

    vec4 light =  clamp(AmbientLight() + DiffuseLight(normal) + SpecularLight(normal), 0.0, 1.0);
    vec4 finalColor = texColor * light;

    vec4 fogColor = MixFog(finalColor);
    oColor = GammaCorrect(fogColor);
}
