#version 450
out vec4 FragColor;
in vec2 UV;

#define NUM_SPRITES 3

uniform sampler2D _char[NUM_SPRITES];

uniform sampler2D _char1_1;
uniform sampler2D _char1_2;
uniform sampler2D _char1_3;


void main(){
	for (int i = 0; i < NUM_SPRITES; i++){
	FragColor = texture(_char[i], UV);
	}
}