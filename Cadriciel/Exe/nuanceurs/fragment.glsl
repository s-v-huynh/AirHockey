#version 420

layout(binding=0) uniform sampler2D diffuseTex;

varying vec2 texCoord;
in vec4 couleur;

out vec4 color;

void main()
{
    //color = vec4(0.5, 0.5, 0.5, 1.0);
   // color = texture2D(diffuseTex, texCoord.st);
    color = couleur;
}