#ifndef SOLID_BODY_CLASS
#define SOLID_BODY_CLASS
#include "Mesh.h"
#include "Sphere.h"

class SolidBody
{
public:
	std::vector<mesh*> All_Mesh;
	std::vector<unsigned int> Sphere_in;
	void CleanUp()
	{
		for (auto obj : All_Mesh)
		{
			obj->ClearMesh();
		}
		All_Mesh.clear();
	}
	void BadHookeLaws(std::vector<Vertex> Sphere_vert, std::vector<unsigned int> Sphere_ind,int shape)
	{
		std::vector<glm::vec3>Locations;

		std::vector<unsigned int> indices =
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
		switch (shape)
		{
		case 0:
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
			break;
		case 2:
			std::vector<Vertex> Sphere_ver;
			
			GenSphere sphere;
			sphere.generateSphere(6.0f,11,11, glm::vec3(1, 0, 0), Sphere_ver, Sphere_in);

			for (auto vert : Sphere_ver)
			{
				Locations.push_back(glm::vec4(vert.position,0));
			}
			/*for (int i = 0; i < Locations.size(); i++)
			{
				for (int j = 0; j < Locations.size(); j++)
				{
					if (i != j)
					{
						if ((glm::distance(glm::vec3(Locations[i]), glm::vec3(Locations[j])) <= 0.002))
						{
							Locations.erase(Locations.begin() + j);
						}
					}
				}

			}*/
			std::cout << Locations.size();
			break;
		}
		SurfaceSubdivide(indices,Locations);
		SurfaceSubdivide(indices, Locations);
		//SurfaceSubdivide(indices, Locations);

		for (int i = 0; i < Locations.size(); i++)
		{
			mesh* cube1 = new mesh;
			cube1->CreateMesh(Sphere_vert, Sphere_ind);
			cube1->transform.position = glm::vec3(Locations[i]);
			cube1->transform.velocity = glm::vec3(0, 0, 0);
			cube1->ColorID = glm::vec4(i/10.0f, 0, 0, 0);
			cube1->transform.mass = 3.0f;
			All_Mesh.push_back(cube1);
		}
		for (int i = 0; i < All_Mesh.size(); i++)
		{
			for (int j = 0; j < All_Mesh.size(); j++)
			{
				if (i != j)
				{
					float dis = glm::distance(All_Mesh[i]->transform.position, All_Mesh[j]->transform.position);
					All_Mesh[i]->Bro.push_back(glm::vec2(j, dis));
				}
			}
		}
		
	}

	void SurfaceSubdivide(std::vector<unsigned int>& indices, std::vector<glm::vec3> & Locations)
	{
		std::vector<unsigned int> divided_indices;
		int size = indices.size();
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
	
		Current_Indices = divided_indices;
		indices = Current_Indices;

	}

	void GoodHookeLaws(std::vector<Vertex> Sphere_vert, std::vector<unsigned int> Sphere_ind)
	{
		mesh* cube1 = new mesh;
		cube1->CreateMesh(Sphere_vert, Sphere_ind);
		cube1->transform.position = glm::vec3(10, 0, 0);
		cube1->transform.velocity = glm::vec3(0, 0, 0);
		cube1->ColorID = glm::vec4(1, 0, 0, 0);
		cube1->transform.mass = 10.0f;
		All_Mesh.push_back(cube1);
		cube1->bro.push_back(1);
		cube1->bro.push_back(3);
		cube1->bro.push_back(2);
		cube1->bro.push_back(7);
		mesh* cube2 = new mesh;
		cube2->CreateMesh(Sphere_vert, Sphere_ind);
		cube2->transform.position = glm::vec3(0, 0, 0);
		cube2->transform.velocity = glm::vec3(0, 0, 0);
		cube2->ColorID = glm::vec4(0, 1, 0, 0);
		cube2->transform.mass = 10.0f;
		All_Mesh.push_back(cube2);
		cube2->bro.push_back(0);
		cube2->bro.push_back(2);
		cube2->bro.push_back(3);
		cube2->bro.push_back(6);
		mesh* cube3 = new mesh;
		cube3->CreateMesh(Sphere_vert, Sphere_ind);
		cube3->transform.position = glm::vec3(10, 0, 10);
		cube3->transform.velocity = glm::vec3(0, 0, 0);
		cube3->ColorID = glm::vec4(0, 1, 0, 0);
		cube3->transform.mass = 10.0f;
		All_Mesh.push_back(cube3);
		cube3->bro.push_back(0);
		cube3->bro.push_back(1);
		cube3->bro.push_back(3);
		cube3->bro.push_back(5);
		mesh* cube4 = new mesh;
		cube4->CreateMesh(Sphere_vert, Sphere_ind);
		cube4->transform.position = glm::vec3(0, 0, 10);
		cube4->transform.velocity = glm::vec3(0, 0, 0);
		cube4->ColorID = glm::vec4(0, 1, 0, 0);
		cube4->transform.mass = 10.0f;
		All_Mesh.push_back(cube4);
		cube4->bro.push_back(1);
		cube4->bro.push_back(0);
		cube4->bro.push_back(2);
		cube4->bro.push_back(4);

		mesh* cube5 = new mesh;
		cube5->CreateMesh(Sphere_vert, Sphere_ind);
		cube5->transform.position = glm::vec3(10, 10, 0);
		cube5->transform.velocity = glm::vec3(0, 0, 0);
		cube5->ColorID = glm::vec4(1, 0, 0, 0);
		cube5->transform.mass = 10.0f;
		All_Mesh.push_back(cube5);
		cube5->bro.push_back(5);
		cube5->bro.push_back(7);
		cube5->bro.push_back(6);
		cube5->bro.push_back(3);
		mesh* cube6 = new mesh;
		cube6->CreateMesh(Sphere_vert, Sphere_ind);
		cube6->transform.position = glm::vec3(0, 10, 0);
		cube6->transform.velocity = glm::vec3(0, 0, 0);
		cube6->ColorID = glm::vec4(0, 1, 0, 0);
		cube6->transform.mass = 10.0f;
		All_Mesh.push_back(cube6);
		cube6->bro.push_back(4);
		cube6->bro.push_back(6);
		cube6->bro.push_back(7);
		cube6->bro.push_back(2);
		mesh* cube7 = new mesh;
		cube7->CreateMesh(Sphere_vert, Sphere_ind);
		cube7->transform.position = glm::vec3(10, 10, 10);
		cube7->transform.velocity = glm::vec3(0, 0, 0);
		cube7->ColorID = glm::vec4(0, 1, 0, 0);
		cube7->transform.mass = 10.0f;
		All_Mesh.push_back(cube7);
		cube7->bro.push_back(4);
		cube7->bro.push_back(5);
		cube7->bro.push_back(7);
		cube7->bro.push_back(1);
		mesh* cube8 = new mesh;
		cube8->CreateMesh(Sphere_vert, Sphere_ind);
		cube8->transform.position = glm::vec3(0, 10, 10);
		cube8->transform.velocity = glm::vec3(0, 0, 0);
		cube8->ColorID = glm::vec4(0, 1, 0, 0);
		cube8->transform.mass = 10.0f;
		All_Mesh.push_back(cube8);
		cube8->bro.push_back(5);
		cube8->bro.push_back(4);
		cube8->bro.push_back(6);
		cube8->bro.push_back(0);


	}
	~SolidBody()
	{
		for (auto obj : All_Mesh)
		{
			delete obj;
		}
	}
	void render(GLuint &shaderprogram, glm::mat4 &camMatrix)
	{
		for (auto obj : All_Mesh)
		{
			obj->RenderMesh(shaderprogram, camMatrix);
		}
	}
};

#endif
