//transformations.h
#pragma once
#include "../ew/ewMath/mat4.h"
#include "../ew/ewMath/vec3.h"
#include "../ew/ewMath/ewMath.h"

namespace kr
{
	//Identity matrix
	inline ew::Mat4 Identity()
	{
		return ew::Mat4
		(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	};

	//Scale on x, y, z axes
	inline ew::Mat4 Scale(ew::Vec3 s)
	{
		return ew::Mat4
		(
			s.x, 0, 0, 0,
			0, s.y, 0, 0,
			0, 0, s.z, 0,
			0, 0, 0, 1
		);
	};

	//Rotation around x axis (pitch) in radians
	inline ew::Mat4 RotateX(float rad)
	{
		return ew::Mat4
		(
			1, 0, 0, 0,
			0, cos(rad), -sin(rad), 0,
			0, sin(rad), cos(rad), 0,
			0, 0, 0, 1
		);
	};

	//Rotation around y axis (yaw) in radians
	inline ew::Mat4 RotateY(float rad)
	{
		return ew::Mat4
		(
			cos(rad), 0, sin(rad), 0,
			0, 1, 0, 0,
			-sin(rad), 0, cos(rad), 0,
			0, 0, 0, 1
		);
	};

	//Rotation around z axis (roll) in radians
	inline ew::Mat4 RotateZ(float rad)
	{
		return ew::Mat4
		(
			cos(rad), -sin(rad), 0, 0,
			sin(rad), cos(rad), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	};

	//Translate x, y, z
	inline ew::Mat4 Translate(ew::Vec3 t)
	{
		return ew::Mat4
		(
			1, 0, 0, t.x,
			0, 1, 0, t.y,
			0, 0, 1, t.z,
			0, 0, 0, 1
		);
	};

	struct Transform
	{
		ew::Vec3 position = ew::Vec3(0.0f, 0.0f, 0.0f);
		ew::Vec3 rotation = ew::Vec3(0.0f, 0.0f, 0.0f); //Euler angles (degrees)
		ew::Vec3 scale = ew::Vec3(1.0f, 1.0f, 1.0f);
		ew::Mat4 getModelMatrix() const
		{
			//I had to change Translate and Scale to kr::Translate and kr::Scale to get this line to work on a library computer. This might not be necessary on a lab computer?
			return kr::Translate(position) * RotateY(ew::Radians(rotation.y)) * RotateX(ew::Radians(rotation.x)) * RotateY(ew::Radians(rotation.z)) * kr::Scale(scale);
		}
	};

	//Creates a right handed view space
	//eye = eye (camera) position
	//target = position  to look at
	//up = up axis, usually(0, 1, 0)
	inline ew::Mat4 LookAt(ew::Vec3 eye, ew::Vec3 target, ew::Vec3 up)
	{
		//use ew::Cross for cross product!
		ew::Vec3 upAxis = (0.0f, 1.0f, 0.0f);

		auto f = ew::Normalize(target - eye);
		auto r = ew::Normalize(ew::Cross(up, f));
		auto u = ew::Normalize(ew::Cross(f, r));

		return ew::Mat4
		(
			r.x, r.y, r.z, 0.0,
			u.x, u.y, u.z, 0.0,
			f.x, f.y, f.z, 0.0,
			0.0, 0.0, 0.0, 1.0
		);
	};

	//Orthographic projection
	inline ew::Mat4 Orthographic(float height, float aspect, float near, float far)
	{
		float width = aspect * height;
		float r = width / 2;
		float t = height / 2;
		float l = -r;
		float b = -t;
		return ew::Mat4
		(
			2.0 / (r - l), 0.0, 0.0, -((r + l) / (r - l)),
			0.0, 2.0 / (t - b), 0.0, -((t + b) / (t - b)),
			0.0, 0.0, -2.0 / (far - near), -((far + near) / (far - near)),
			0.0, 0.0, 0.0, 1.0
		);
	};

	//Perspective projection
	//fov = vertial aspect ratio (radians)
	inline ew::Mat4 Perspective(float fov, float aspect, float near, float far)
	{
		return ew::Mat4
		(
			1 / tan(ew::Radians(fov)/2.0) * aspect, 0.0, 0.0, 0.0,
			0.0, 1 / tan(ew::Radians(fov) / 2.0), 0.0, 0.0,
			0.0, 0.0, (near + far) / (near - far), (2 * far * near) / (near - far),
			0.0, 0.0, -1.0, 0.0
		);
	};
}