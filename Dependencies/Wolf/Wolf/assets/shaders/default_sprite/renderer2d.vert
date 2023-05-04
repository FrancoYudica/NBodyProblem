#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aUV;

uniform mat4 u_projection;
uniform mat4 u_view;

out vec4 _Color;

void main()
{
	_Color = vec4(aUV, 0, 1);
   gl_Position = u_projection * u_view * vec4(aPos, 1.0);
};