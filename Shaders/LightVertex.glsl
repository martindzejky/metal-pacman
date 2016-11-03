#version 410

in vec3 iPosition;

uniform mat4 uModel;


// calculate the vertex position
void main()
{
    gl_Position = uModel * vec4(iPosition, 1.0);
}
