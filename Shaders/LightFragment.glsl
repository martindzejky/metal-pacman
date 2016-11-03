#version 410

out vec4 oColor;


// map the depth to the shadow map
void main()
{
    oColor = vec4(vec3(1.0 - gl_FragCoord.z), 1.0);
}
