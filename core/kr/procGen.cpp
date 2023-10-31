//procGen.cpp
#include "procGen.h"

namespace kr
{
	//So for these structs, I'm pretty sure you're supposed to create an ew::MeshData struct within these functions. You then push_back vertex and index data into the struct using
	//vertices.push_back and indices.push_back. vertices and indices are both member variables of the ew::MeshData struct.
	
	ew::MeshData createSphere(float radius, int numSegments)
	{	
		ew::MeshData sphereMesh;
		
		ew::Vec3 v;

		auto thetaStep = (2 * ew::PI) / numSegments;
		auto phiStep = ew::PI / numSegments;
		
		auto theta = thetaStep;
		auto phi = phiStep;

		//Sphere vertices
		for (int row = 0; row <= numSegments; row++)
		{
			phi = row * phiStep;

			for (int col = 0; col <= numSegments; col++)
			{
				theta = col * thetaStep;

				v.x = radius * cos(theta) * sin(phi);
				v.y = radius * cos(phi);
				v.z = radius * sin(theta) * sin(phi);

				//sphereMesh.vertices.push_back(v);
			}
		}



		return sphereMesh;
	}

	ew::MeshData createCylinder(float height, float radius, int numSegments)
	{
		ew::MeshData cylinderMesh;

		ew::Vec3 v;

		float topY = height / 2;
		float bottomY = -topY;

		//Top center
		//cylinderMesh.vertices.push_back({ ew::Vec3(0, topY, 0) });

		//Top ring

		//Bottom ring

		//Bottom center
		//cylinderMesh.vertices.push_back({ ew::Vec3(0, bottomY, 0) });

		auto thetaStep = (2 * ew::PI) / numSegments;
		auto theta = thetaStep;

		for (int i = 0; i <= numSegments; i++);
		{
			theta = i * thetaStep;

			v.x = cos(theta) * radius;
			v.z = sin(theta) * radius;
			v.y = topY;

			//cylinderMesh.vertices.push_back(v);
		}
	}

	ew::MeshData createPlane(float width, float height, int subdivisions)
	{
		ew::MeshData planeMesh;

		ew::Vec3 v;
		
		for (int row = 0; row <= subdivisions; row++)
		{
			for (int col = 0; col <= subdivisions; col++)
			{
				v.x = width * (col / subdivisions);
				v.z = -height * (row / subdivisions);
				//planeMesh.vertices.push_back(v);
			}
		}

		int columns = subdivisions + 1;

		for (int row = 0; row < subdivisions; row++)
		{
			for (int col = 0; col < subdivisions; col++)
			{
				int start = row * columns + col;

				//Bottom right triangle
				planeMesh.indices.push_back(start);
				planeMesh.indices.push_back(start + 1);
				planeMesh.indices.push_back(start + columns + 1);

				//Top left triangle
				planeMesh.indices.push_back(start);
				planeMesh.indices.push_back(start + columns);
				planeMesh.indices.push_back(start + columns + 1);
			}
		}

		return planeMesh;
	}
}