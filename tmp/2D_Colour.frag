//Working version for 2D objects

#version 330
in vec4 colour;
out vec4 frag_colour;
void main ()
{
		frag_colour = vec4(1.0, 0.0, 0.0, 1.0);
		frag_colour = vec4(colour);
}