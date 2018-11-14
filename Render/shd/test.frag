#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;
in vec3 normal;

uniform sampler2D texture1;
uniform vec3 lightVec;

void main() {
	float intensity = dot(normal, lightVec);
    FragColor = intensity * texture(texture1, TexCoord);
}