#version 410

in vec3 iPosition;

uniform mat4 uModelViewProjection;


// calculate the vertex position
void main()
{
    gl_Position = uModelViewProjection * vec4(iPosition, 1.0);
}
