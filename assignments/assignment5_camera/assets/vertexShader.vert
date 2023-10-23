#version 450
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;

out vec3 Normal;
uniform mat4 _Model;
uniform mat4 _View; //view matrix passed in as mat4 uniform
uniform mat4 _Projection; //projection matrix passed in as mat4 uniform

void main(){
	Normal = vNormal;
	//Transformation from model to clip space.
	//There could be something wrong with this, updating gl_position made the cubes disappear. I added the "_Projection * _View *" part.
	gl_Position = _Projection * _View * _Model * vec4(vPos,1.0);
}