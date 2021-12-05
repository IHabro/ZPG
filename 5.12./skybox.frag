#version 330

in vec3 TexCoords;

out vec4 gl_FragColor;

uniform samplerCube Texture;

void main()
{
	gl_FragColor = texture(Texture, TexCoords);
}