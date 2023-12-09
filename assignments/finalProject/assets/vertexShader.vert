#version 450
	layout(location = 0) in vec3 vPos;
	layout(location = 1) in vec2 UVCoordinate;

	out vec2 TexCoords;
	out vec2 UV;

	uniform mat4 model;
	uniform mat4 projection;

	void main(){
		UV = UVCoordinate;
		TexCoords = UVCoordinate;
		gl_Position = projection * model * vec4(vPos, 1.0);
	}
