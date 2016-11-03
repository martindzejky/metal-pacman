#version 410

layout (triangles) in;
layout (triangle_strip, max_vertices=18) out;

uniform mat4 uProjection;
uniform mat4 uView[6];

out vec4 Position;


// emit a face for every cube map face
void main()
{
    for(int face = 0; face < 6; ++face)
    {
        gl_Layer = face;
        for(int i = 0; i < 3; ++i) // for each triangle's vertices
        {
            Position = gl_in[i].gl_Position;
            gl_Position = uProjection * uView[face] * Position;
            EmitVertex();
        }
        EndPrimitive();
    }
}
