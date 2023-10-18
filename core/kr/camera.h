//core/myLib.camera.h

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
		ew::Mat4 ViewMatrix()
		{
			//LookAt(position, target, );
		};
		//World->View
		ew::Mat4 ProjectionMatrix()
		{
			float width = orthoSize * aspectRatio;
			if (orthographic == 1)
			{
				Orthographic(orthoSize, aspectRatio, nearplane, farPlane);
			}
			else if (orthographic == 0)
			{
				Perspective(fov, aspectRatio, nearPlane, farPlane);
			}
		};
		
		//View->Clip
	};
}