#version 330 core
out vec4 FragColor;

in vec4 _color;
in vec2 _uv;
in float _radius;
in float _fade;

void main()
{
   vec2 pos = _uv - vec2(0.5);
   float distance = length(pos);
   if (distance > _radius)
   {
      discard;
   }  
   
   FragColor = _color * smoothstep(_radius, _radius - _fade, distance);
};