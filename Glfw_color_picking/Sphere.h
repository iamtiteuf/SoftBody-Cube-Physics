#ifndef SPHERE_CLASS
#define SPHERE_CLASS
#include "Glew_Initialization.h"

class GenSphere
{
	public:
       void generateSphere(float radius, unsigned int rings, unsigned int sectors, glm::vec3 color, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
            float const R = 1.0f / (float)(rings - 1);
            float const S = 1.0f / (float)(sectors - 1);

             //Add top vertex
            vertices.push_back({ glm::vec3(0, 1, 0), color, glm::vec3(0, 1, 0), glm::vec2(0, 0) });

             //Generate vertices per stack / slice
            for (unsigned int r = 1; r < rings; ++r) {
                float const y = sin(-glm::pi<float>() / 2 + glm::pi<float>() * r * R);
                for (unsigned int s = 0; s < sectors; ++s) {
                    float const x = cos(2 * glm::pi<float>() * s * S) * sin(glm::pi<float>() * r * R);
                    float const z = sin(2 * glm::pi<float>() * s * S) * sin(glm::pi<float>() * r * R);

                    glm::vec3 position = glm::vec3(x, y, z) * radius;
                    glm::vec2 texUV = glm::vec2(s * S, r * R);

                    Vertex vertex;
                    vertex.position = position;
                    vertex.color = color;
                    vertex.texUV = texUV;
                    vertices.push_back(vertex);
                }
            }

            // Add bottom vertex
            vertices.push_back({ glm::vec3(0, -1, 0), color, glm::vec3(0, -1, 0), glm::vec2(0, 0) });

             //Add triangles for the top and bottom poles
            for (unsigned int s = 0; s < sectors; ++s) {
                unsigned int i0 = s;
                unsigned int i1 = (s + 1) % sectors;
                indices.push_back(0);
                indices.push_back(i0 + 1);
                indices.push_back(i1 + 1);

                i0 = s + (rings - 2) * sectors;
                i1 = (s + 1) % sectors + (rings - 2) * sectors;
                indices.push_back(vertices.size() - 1);
                indices.push_back(i0);
                indices.push_back(i1);
            }

             //Add quads per stack / slice
            for (unsigned int r = 0; r < rings - 2; ++r) {
                for (unsigned int s = 0; s < sectors; ++s) {
                    unsigned int i0 = r * sectors + s;
                    unsigned int i1 = r * sectors + (s + 1) % sectors;
                    unsigned int i2 = (r + 1) * sectors + (s + 1) % sectors;
                    unsigned int i3 = (r + 1) * sectors + s;

                    indices.push_back(i0);
                    indices.push_back(i1);
                    indices.push_back(i2);

                    indices.push_back(i0);
                    indices.push_back(i2);
                    indices.push_back(i3);
                }
            }
        }
		/*void generateSphere(float radius, unsigned int rings, unsigned int sectors, glm::vec3 color, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
			float const R = 1.0f / (float)(rings - 1);
			float const S = 1.0f / (float)(sectors - 1);

			vertices.resize(rings * sectors);
			std::vector<Vertex>::iterator v = vertices.begin();

			for (unsigned int r = 0; r < rings; ++r) {
				for (unsigned int s = 0; s < sectors; ++s) {
					float const y = sin(-glm::pi<float>() / 2 + glm::pi<float>() * r * R);
					float const x = cos(2 * glm::pi<float>() * s * S) * sin(glm::pi<float>() * r * R);
					float const z = sin(2 * glm::pi<float>() * s * S) * sin(glm::pi<float>() * r * R);

					v->position = glm::vec3(x, y, z) * radius;
					v->color = color;
					v->texUV = glm::vec2(s * S, r * R);
					v++;
				}
			}

			indices.resize(rings * sectors * 6);
			std::vector<unsigned int>::iterator i = indices.begin();
			for (unsigned int r = 0; r < rings - 1; ++r) {
				for (unsigned int s = 0; s < sectors - 1; ++s) {
					*i++ = r * sectors + s;
					*i++ = r * sectors + (s + 1);
					*i++ = (r + 1) * sectors + (s + 1);
					*i++ = (r + 1) * sectors + s;
					*i++ = r * sectors + s;
					*i++ = (r + 1) * sectors + (s + 1);
				}
			}
		}*/
};
#endif