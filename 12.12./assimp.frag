#version 330\n

out vec4 frag_colour;

in vec2 uvc;

uniform sampler2D textureUnitID;

void main ()
{
     frag_colour = texture(textureUnitID, uvc);
}