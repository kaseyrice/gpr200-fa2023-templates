#version 450
	layout(location = 0) in vec3 vPos;
	layout(location = 1) in vec2 UVCoordinate;
	out vec2 UV;
	void main(){
		UV = UVCoordinate;
		gl_Position = vec4(vPos,1.0);
	}
