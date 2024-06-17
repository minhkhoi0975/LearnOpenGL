#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out VS_OUT
{
	vec2 TexCoord;
} vs_out;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0);
	vs_out.TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}