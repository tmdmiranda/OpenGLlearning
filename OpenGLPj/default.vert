#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

// Output color for fragment shader
out vec3 color;
out vec2 texCoord;

// Uniforms
uniform mat4 camMatrix;

void main()
{
   gl_Position = camMatrix * vec4(aPos, 1.0f);
   // Assigns colors from the vertex data to "color"
   color = aColor;
   texCoord = aTex;
}