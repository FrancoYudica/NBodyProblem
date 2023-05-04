#version 330 core
out vec4 FragColor;
in vec4 _Color;

void main()
{
   FragColor = _Color;
};