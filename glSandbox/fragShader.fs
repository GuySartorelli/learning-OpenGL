#version 330 core

in vec4 vertexColor;
in vec2 texCoord;

uniform float intensity;
uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 FragColor;

void main(){
    //FragColor = vertexColor * intensity; //vec4(1.0f, 0.5f, 0.2f, 1.0f);
    FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), intensity) * vertexColor * intensity;
}
