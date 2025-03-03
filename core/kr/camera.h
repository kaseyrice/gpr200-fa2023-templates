//core/myLib.camera.h
#include "../kr/transformations.h"

namespace kr
{
	struct Camera
	{
		ew::Vec3 position; //Camera body position
		ew::Vec3 target; //Position to look at
		float fov; //Vertical field of view in degrees
		float aspectRatio; //Screen width / Screen height
		float nearPlane; //Near plane distance (+Z)
		float farPlane; //Far plane distance (+Z)
		bool orthographic; //Perspective or orthographic?
		float orthoSize; //Height of orthographic frustum
		//World->View
		ew::Mat4 ViewMatrix()
		{
			ew::Vec3 upAxis = (0.0, 1.0, 0.0);
			kr::LookAt(position, target, upAxis);
		};
		//View->Clip
		ew::Mat4 ProjectionMatrix()
		{
			float width = orthoSize * aspectRatio;
			if (orthographic == 1)
			{
				Orthographic(orthoSize, aspectRatio, nearPlane, farPlane);
			}
			else if (orthographic == 0)
			{
				Perspective(fov, aspectRatio, nearPlane, farPlane);
			}
		};
	};
}