#version 330

in vec3 ex_worldPosition;
in vec3 ex_worldNormal;
in vec2 uv;

out vec4 frag_colour;

uniform sampler2D Texture;

void main ()
{
     frag_colour = texture(Texture, uv);
}
