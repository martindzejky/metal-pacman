#version 410

in vec3 EyePosition;
in vec3 Color;
in vec2 TexCoord;
in mat3 TBN;

in vec3 LightEyePosition;

uniform sampler2D uTexture;
uniform sampler2D uNormalMap;
uniform sampler2D uReflectionMap;

out vec4 oColor;


const float gamma = 2.2;

const vec3 lightColor = vec3(0.9, 0.7, 0.3);
const float lightRadius = 6.0;


// calculate the fog color and mix it with the final fragment color
vec4 MixFog(vec4 color) {
    const vec4 fogColor = vec4(0.01, 0.008, 0.002, 1.0);
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


// ambient light
vec4 AmbientLight() {
    return vec4(0.03, 0.01, 0.004, 1.0);
}


// diffuse light based on the lights in the scene
vec4 DiffuseLight(vec3 normal) {
    vec3 lightDir = LightEyePosition - EyePosition;
    float lightDistance = length(lightDir);
    float diffuse = max(dot(normal, normalize(lightDir)), 0.0);

    vec3 lightFinal = lightColor * diffuse;
    float att = clamp(1.0 - lightDistance * lightDistance / (lightRadius * lightRadius), 0.0, 1.0);
    lightFinal *= att * att;

    return vec4(lightFinal, 1.0);
}


// specular highlights
vec4 SpecularLight(vec3 normal) {
    const float strength = 0.7;
    const int shininess = 64;

    vec3 reflectionColor = texture(uReflectionMap, TexCoord).rgb;
    float reflection = (reflectionColor.r + reflectionColor.g + reflectionColor.b) / 3;

    vec3 viewDir = normalize(-EyePosition);
    vec3 lightDir = LightEyePosition - EyePosition ;
    float lightDistance = length(lightDir);
    vec3 halfwayDir = normalize(normalize(lightDir) + viewDir);

    float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
    vec3 specColor = lightColor * spec * strength;
    float att = clamp(1.0 - lightDistance * lightDistance / (lightRadius * lightRadius), 0.0, 1.0);

    return vec4(specColor * att * att * reflection, 1.0);
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
