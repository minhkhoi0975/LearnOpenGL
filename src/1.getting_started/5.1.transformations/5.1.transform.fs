#version 330 core
out vec4 FragColor;

in VS_OUT
{
	vec2 TexCoord;
} fs_in;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = mix(texture(texture1, fs_in.TexCoord), texture(texture2, fs_in.TexCoord), 0.2);
}