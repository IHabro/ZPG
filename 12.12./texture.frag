#version 330

in vec3 worldPosition;
in vec3 worldNormal;
in vec2 uv;

out vec4 frag_colour;

uniform sampler2D Texture;

void main ()
{
     frag_colour = texture(Texture, uv);
}
