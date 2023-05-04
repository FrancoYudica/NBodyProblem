#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec2 a_uv;
layout (location = 3) in float a_radius;
layout (location = 4) in float a_fade;

uniform mat4 u_projection;
uniform mat4 u_view;

out vec4 _color;
out vec2 _uv;
out float _radius;
out float _fade;

void main()
{
   _color = a_color;
   _uv = a_uv;
   _radius = a_radius;
   _fade = a_fade;
   gl_Position = u_projection * u_view * vec4(a_pos, 1.0);
};