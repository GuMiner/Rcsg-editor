#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out VS_OUT
{
    vec4 color;
} vs_out;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

void main(void)
{
    vec4 pos = vec4(position, 1);

    // Compute where we are for this shape
    int count = 10;
    float spacing = 1.5;
    int y = gl_InstanceID/count;
    int x = gl_InstanceID - y*count;

    mat4 translateMatrix;
    translateMatrix[0] = vec4(1.0, 0.0, 0.0, 0.0);
    translateMatrix[1] = vec4(0.0, 1.0, 0.0, 0.0);
    translateMatrix[2] = vec4(0.0, 0.0, 1.0, 0.0);
    translateMatrix[3] = vec4((x - count/2)*spacing, (y - count/2)*spacing, 0.0, 1.0);

    gl_Position = proj_matrix * mv_matrix * translateMatrix * mv_matrix * pos;
    
    // Output stuff to the fragment shader
    vs_out.color = vec4(pos.x*4, pos.y*4, pos.z*4, 1);
}