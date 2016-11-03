#version 410

in vec4 Position;

uniform vec3 uLightPosition;
uniform float uFarPlane;

// map the depth to the shadow map
void main()
{
    float lightDistance = length(Position.xyz - uLightPosition);
    gl_FragDepth = lightDistance / uFarPlane;
}
