//procGen.cpp
#include "procGen.h"

namespace kr
{	
	ew::MeshData createSphere(float radius, int numSegments)
	{	
		ew::MeshData sphereMesh;
		ew::Vertex vertex;
		ew::Vec3 v;

		auto thetaStep = (2 * ew::PI) / numSegments;
		auto phiStep = ew::PI / numSegments;
		
		auto theta = thetaStep;
		auto phi = phiStep;

		//Sphere Vertices
		for (int row = 0; row <= numSegments; row++)
		{
			phi = row * phiStep;

			for (int col = 0; col <= numSegments; col++)
			{
				theta = col * thetaStep;

				v.x = radius * cos(theta) * sin(phi);
				v.y = radius * cos(phi);
				v.z = radius * sin(theta) * sin(phi);

				vertex.pos = v;
				vertex.normal = ew::Vec3(1, 0, 0);
				vertex.uv = ew::Vec2(col / numSegments, row / numSegments);

				sphereMesh.vertices.push_back(vertex);
			}
		}

		//Sphere Caps
		int poleStart = 0;
		int sideStart = numSegments + 1;

		for (int i = 0; i < numSegments; i++)
		{
			sphereMesh.indices.push_back(sideStart + i);
			sphereMesh.indices.push_back(poleStart + i);
			sphereMesh.indices.push_back(sideStart + i + 1);

			sphereMesh.indices.push_back(numSegments - i);
			sphereMesh.indices.push_back(sphereMesh.vertices.size() - i); 
			sphereMesh.indices.push_back(numSegments - i - 1);
		}

		//Sphere Row Indices
		int columns = numSegments + 1;

		//Skip top and bottom poles
		for (int row = 1; row < numSegments - 1; row++)
		{
			for (int col = 0; col < numSegments; col++)
			{
				int start = row * columns + col;

				//Triangle 1
				sphereMesh.indices.push_back(start);
				sphereMesh.indices.push_back(start + 1);
				sphereMesh.indices.push_back(start + columns);

				//Triangle 2
				sphereMesh.indices.push_back(start + columns);
				sphereMesh.indices.push_back(start + 1);
				sphereMesh.indices.push_back(start + columns + 1);
			}
		}

		return sphereMesh;
	}

	ew::MeshData createCylinder(float height, float radius, int numSegments)
	{
		ew::MeshData cylinderMesh;
		ew::Vertex vertex;
		ew::Vec3 v;

		//Vertices
		float topY = height / 2;
		float bottomY = -topY;

		//Top center
		cylinderMesh.vertices.push_back({ ew::Vec3(0, topY, 0) });

		//Top ring

		//Bottom ring

		//Bottom center
		cylinderMesh.vertices.push_back({ ew::Vec3(0, bottomY, 0) });

		auto thetaStep = (2 * ew::PI) / numSegments;
		auto theta = thetaStep;

		for (int i = 0; i <= numSegments; i++)
		{
			theta = i * thetaStep;

			v.x = cos(theta) * radius;
			v.z = sin(theta) * radius;
			v.y = topY;

			vertex.pos = v;

			cylinderMesh.vertices.push_back(vertex);
		}

		//Cap Indices
		//start = index of first ring vertex
		//center = index of center vertex

		//Side Indices
		//sideStart = index of first top ring vertex
		int columns = numSegments + 1;

		for (int i = 0; i < columns; i++)
		{
			//start = sideStart + 1;

			//Triangle 1

			//Triangle 2
		}

		return cylinderMesh;
	}

	ew::MeshData createPlane(float width, float height, int subdivisions)
	{
		ew::MeshData planeMesh;
		ew::Vertex vertex;
		ew::Vec3 v;		

		//Vertices
		for (int row = 0; row <= subdivisions; row++)
		{
			for (int col = 0; col <= subdivisions; col++)
			{
				v.x = width * (col / subdivisions);
				v.y = 0;
				v.z = -height * (row / subdivisions);
				vertex.pos = v;
				vertex.normal = ew::Vec3(1, 0, 0);
				vertex.uv = ew::Vec2(col / subdivisions, row / subdivisions);
				planeMesh.vertices.push_back(vertex);
			}
		}

		//Indices
		int columns = subdivisions + 1;

		for (int row = 0; row <= subdivisions; row++)
		{
			for (int col = 0; col <= subdivisions; col++)
			{
				int start = row * columns + col;

				//Bottom right triangle
				planeMesh.indices.push_back(start);
				planeMesh.indices.push_back(start + 1);
				planeMesh.indices.push_back(start + columns + 1);

				//Top left triangle
				planeMesh.indices.push_back(start);
				planeMesh.indices.push_back(start + columns + 1);
				planeMesh.indices.push_back(start + columns);
			}
		}

		return planeMesh;
	}
}