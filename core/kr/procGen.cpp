//procGen.cpp
#include "procGen.h"

namespace kr
{
	//So for these structs, I'm pretty sure you're supposed to create an ew::MeshData struct within these functions. You then push_back vertex and index data into the struct using
	//vertices.push_back and indices.push_back. vertices and indices are both member variables of the ew::MeshData struct.
	
	ew::MeshData createSphere(float radius, int numSegments)
	{	
		ew::MeshData sphereMesh;
		
		auto thetaStep = (2 * PI) / numSegments;
		auto phiStep = PI / numSegments;
		
		auto theta = thetaStep;
		auto phi = phiStep;

		ew::Vec3 v;

		//Sphere vertices
		for (int row = 0; row <= numSegments; row++)
		{
			phi = row * phiStep;

			for (int col = 0; col <= numSegments; col++)
			{
				theta = col * thetaStep;

				v.x = radius * sin(phi) * sin(theta);
				v.y = radius * cos(phi);
				v.z = radius * sin(phi) * cos(theta);

				sphereMesh.vertices.push_back(v);
			}
		}



		return sphereMesh;
	}

	ew::MeshData createCylinder(float height, float radius, int numSegments)
	{

	}

	ew::MeshData createPlane(float width, float height, int subdivisions)
	{

	}
}