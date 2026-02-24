#version 330 core
//position
layout (location = 0) in vec3 aPos;
//color
layout (location = 1) in vec3 aColor;
//texture
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;

out vec2 TexCoord;

uniform float scale;

void main()
{
   gl_Position = vec4(aPos.x + aPos.x*scale, aPos.y + aPos.y*scale, aPos.z + aPos.y * scale, 1.0);
   ourColor = aColor;
   TexCoord = aTexCoord;
}