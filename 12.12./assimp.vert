#version 330\n

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vc;
layout(location = 2) in vec2 uv;

out vec2 uvc;

uniform mat4 modelMatrix;

void main ()
{
    gl_Position = modelMatrix * vec4 (vp, 1.0);
    uvc=uv;
}
