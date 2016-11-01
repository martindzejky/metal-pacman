#version 410

in vec3 EyePosition;
in vec3 EyeNormal;
in vec3 Color;
in vec2 TexCoord;

in vec3 LightEyePosition;

uniform sampler2D uTexture;

out vec4 oColor;


const vec3 lightColor = vec3(1.0, 0.6, 0.3);
const float lightRadius = 16.0;


// calculate the fog color and mix it with the final fragment color
vec4 MixFog(vec4 color) {
    const vec4 fogColor = vec4(0.1, 0.05, 0.01, 1.0);
    const float e = 2.71828182845904523536028747135266249;

    float fogDensity = 0.03;
    float fog = pow(e, -pow(length(EyePosition) * fogDensity, 2));

    return mix(fogColor, color, fog);
}


// get texture color for the fragment and apply vertex color
vec4 TextureColor() {
    return texture(uTexture, TexCoord) * vec4(Color, 1.0);
}


// ambient light
vec4 AmbientLight() {
    return vec4(0.1, 0.1, 0.1, 1.0);
}


// diffuse light based on the lights in the scene
vec4 DiffuseLight() {
    vec3 lightDir = LightEyePosition - EyePosition;
    float lightDistance = length(lightDir);
    float diffuse = max(dot(EyeNormal, normalize(lightDir)), 0.0);

    vec3 lightFinal = lightColor * diffuse;
    float att = clamp(1.0 - lightDistance * lightDistance / (lightRadius * lightRadius), 0.0, 1.0);
    lightFinal *= att * att;

    return vec4(lightFinal, 1.0);
}


// specular highlights
vec4 SpecularLight() {
    const float strength = 0.3;
    const int shininess = 32;

    vec3 viewDir = normalize(-EyePosition);
    float viewDistance = length(EyePosition);
    vec3 lightDir = EyePosition - LightEyePosition;
    float lightDistance = length(lightDir);
    vec3 reflectDir = reflect(normalize(lightDir), EyeNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specColor = lightColor * spec * strength;
    float att = clamp(1.0 - lightDistance * viewDistance / (lightRadius * lightRadius), 0.0, 1.0);

    return vec4(specColor * att * att, 1.0);
}


// make the final fragment color
void main()
{
    vec4 texColor = TextureColor();

    vec4 light =  clamp(AmbientLight() + DiffuseLight() + SpecularLight(), 0.0, 1.0);
    vec4 finalColor = texColor * light;

    oColor = MixFog(finalColor);
}
