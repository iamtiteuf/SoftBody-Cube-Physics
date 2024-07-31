#ifndef CUSTOM_MESH_H
#define CUSTOM_MESH_H
#include "Glew_Initialization.h"
#include "Mesh.h"
#include "Sphere.h"
class Custom_mesh
{
public:
	
	std::vector<Vertex> vertices;
	std::vector<unsigned int>indices;
	std::vector<glm::vec3>Locations;
	Transform transform;
	std::vector<mesh*>points;
	int div = 0;
	void CreateBasicShapes(int shape)
	{
		switch (shape)
		{
		case 0:
			indices =
			{
			  0, 1, 2,
			  1, 2, 3,
			  4, 5, 6,
			  5, 6, 7,// front 
			  1, 5, 3,
			  5, 3, 7,
			  0, 4, 2,
			  4, 2, 6,// back 
			  0, 1, 4,
			  1, 4, 5,
			  2, 3, 6,
			  3, 6, 7 // sides
			};
			Locations =
			{
				glm::vec4(10,0,0,2),
				glm::vec4(0,0,0,3),
				glm::vec4(10,10,0,0),
				glm::vec4(0,10,0,1),
				glm::vec4(10,0,-10,6),
				glm::vec4(0,0,-10,7),
				glm::vec4(10,10,-10,4),
				glm::vec4(0,10,-10,5)
			};
			break;
		case 1:
			Locations =
			{
				glm::vec4(10,0,0,0),//0
				glm::vec4(0,0,0,0),//1
				glm::vec4(10,0,-10,0),//2
				glm::vec4(0,0,-10,0),//3
				glm::vec4(5,-10,-5,0)//4
			};
			indices =
			{
				0,1,2,
				1,3,2,
				0,1,4,
				1,3,4,
				0,4,2,
				2,3,4

			};
			break;
		case 2:
			std::vector<Vertex> Sphere_ver;
			std::vector<unsigned int> Sphere_in;
			sphere.generateSphere(6.0f, 11, 11, glm::vec3(1, 0, 0), Sphere_ver, Sphere_in);

			for (auto vert : Sphere_ver)
			{
				Locations.push_back(glm::vec4(vert.position, 0));
			}
			break;
		}

		for (int i = 0; i < div; i++)
		{
			SurfaceSubdivide();
		}

		for (int i = 0; i < Locations.size(); i++)
		{
			std::vector<Vertex> Sphere_vert;
			std::vector<unsigned int> Sphere_ind;
			sphere.generateSphere(0.1f, 5, 5, glm::vec3(1, 0, 0), Sphere_vert, Sphere_ind);
			mesh* cube1 = new mesh;
			cube1->CreateMesh(Sphere_vert, Sphere_ind);
			cube1->transform.position = glm::vec3(Locations[i]);
			cube1->transform.velocity = glm::vec3(0, 0, 0);
			cube1->ColorID = glm::vec4(i / 10.0f, 0, 0, 0);
			cube1->transform.mass = 3.0f;
			points.push_back(cube1);
		}
		for (int i = 0; i < points.size(); i++)
		{
			for (int j = 0; j < points.size(); j++)
			{
				if (i != j)
				{
					float dis = glm::distance(points[i]->transform.position, points[j]->transform.position);
					points[i]->Bro.push_back(glm::vec2(j, dis));
				}
			}
		}

	}
	void SurfaceSubdivide()
	{
		std::vector<unsigned int> divided_indices;
		for (int i = 0; i < indices.size(); i = i + 3)
		{
			//divided_indices.push_back(indices[i]);
			//divided_indices.push_back(indices[i + 1]);
			//divided_indices.push_back(indices[i + 2]);

			/*glm::vec3 mid = (Locations[indices[i]] + Locations[indices[i + 1]] + Locations[indices[i + 2]]) / 3.0f;
			Locations.push_back(mid);

			divided_indices.push_back(indices[i]);
			divided_indices.push_back(indices[i + 1]);
			divided_indices.push_back(Locations.size() - 1);

			divided_indices.push_back(indices[i + 1]);
			divided_indices.push_back(indices[i + 2]);
			divided_indices.push_back(Locations.size() - 1);

			divided_indices.push_back(indices[i]);
			divided_indices.push_back(Locations.size() - 1);
			divided_indices.push_back(indices[i + 2]);*/

			divided_indices.push_back(indices[i]);
			divided_indices.push_back(indices[i + 1]);
			divided_indices.push_back(indices[i + 2]);

			// Calculate the midpoints of the edges
			glm::vec3 mid1 = (Locations[indices[i]] + Locations[indices[i + 1]]) / 2.0f;
			glm::vec3 mid2 = (Locations[indices[i + 1]] + Locations[indices[i + 2]]) / 2.0f;
			glm::vec3 mid3 = (Locations[indices[i + 2]] + Locations[indices[i]]) / 2.0f;

			// Add the new vertices to the Locations array
			Locations.push_back(mid1);
			Locations.push_back(mid2);
			Locations.push_back(mid3);

			// Add the new triangles to the divided_indices
			divided_indices.push_back(indices[i]);
			divided_indices.push_back(Locations.size() - 3);
			divided_indices.push_back(Locations.size() - 1);

			divided_indices.push_back(indices[i + 1]);
			divided_indices.push_back(Locations.size() - 2);
			divided_indices.push_back(Locations.size() - 3);

			divided_indices.push_back(indices[i + 2]);
			divided_indices.push_back(Locations.size() - 1);
			divided_indices.push_back(Locations.size() - 2);
		}
		indices = divided_indices;
	}

	void Rendermesh(GLuint Shaderprog, glm::mat4 CamMatrix,bool rend_sphere)
	{
		vertices.clear();
		for (auto obj : points)
		{
		vertices.push_back({ obj->transform.position, glm::vec3(0.5,0.5,0.5), glm::vec3(-1,-1,-1), glm::vec2(0, 0) });
		if (rend_sphere)
		{
			obj->RenderMesh(Shaderprog, CamMatrix);
		}
		}
		
		body->Wire = true;
		body->CreateMesh(vertices, indices);
	    body->RenderMesh(Shaderprog, CamMatrix);
		body->ClearMesh();
	}
	~Custom_mesh()
	{
		for (auto obj : points)
		{
			obj->ClearMesh();
		}
		delete body;
	}

private:
	mesh* body = new mesh;
	GenSphere sphere;
};

#endif
