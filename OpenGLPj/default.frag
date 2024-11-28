#version 460 core
out vec4 FragColor;

//Input color from vertex shader
in vec3 color;	

in vec2 texCoord;

uniform sampler2D tex0;

uniform vec4 lightColor;

void main()
{
   FragColor = texture(tex0, texCoord) * lightColor;
}