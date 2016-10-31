#version 410

in vec3 EyePosition;
in vec3 EyeNormal;
in vec3 Color;
in vec2 TexCoord;

in vec3 EyeSun;

uniform sampler2D uTexture;

out vec4 oColor;

void main()
{
    const float e = 2.71828182845904523536028747135266249;
    vec4 fogColor = vec4(0.0, 0.0, 0.0, 1.0);
    float fogDensity = 0.03;
    float fog = pow(e, -pow(length(EyePosition) * fogDensity, 2));

    vec4 textureColor = texture(uTexture, TexCoord) * vec4(Color, 1.0);

    float sunDotNormal = clamp(dot(EyeSun, EyeNormal), 0.0, 1.0);
    float light =  0.2 + sunDotNormal * 0.8;

    vec4 finalColor = vec4(textureColor.xyz * light, 1.0);
    oColor = mix(fogColor, finalColor, fog);
}
