#ifndef PHYSICS_HANDLER_H
#define PHYSICS_HANDLER_H
#include "Glew_Initialization.h"
#define dt 0.06f
#define G 0.1f

#define goodlength 12.0f
#define thisRad 4.0f
class PhysicsHandler
{
   
	
	public:
		static void Step(Transform & transform)
		{
			//transform.force = transform.force + glm::vec3(0, -9000, 0);
			transform.acceleration = transform.force / transform.mass * dt;

			//transform.acceleration = transform.acceleration + (transform.pressure / transform.density) * dt;
			transform.velocity += transform.acceleration * dt;

			transform.position += transform.velocity * dt;


			if (transform.position.x > limits.x)
			{
				transform.position.x = transform.position.x - (transform.position.x - limits.x);
				transform.velocity = -transform.velocity * Damping;
			}
			else if (transform.position.x < -limits.x)
			{
				transform.position.x = transform.position.x + (-limits.x - transform.position.x);
				transform.velocity = -transform.velocity * Damping;
			}
			/*if (transform.position.y > limits.y)
			{
				transform.position.y = transform.position.y - (transform.position.y - limits.y);
				transform.velocity = -transform.velocity * Damping;
			}*/
			else if (transform.position.y < -limits.y)
			{
				transform.position.y = transform.position.y + (-limits.y - transform.position.y);
				transform.velocity = -transform.velocity * Damping;
			}
			if (transform.position.z > limits.z)
			{
				transform.position.z = transform.position.z - (transform.position.z - limits.z);
			}
			else if (transform.position.z < -limits.z)
			{
				transform.position.z = transform.position.z + (-limits.z - transform.position.z);
			}
			transform.force = glm::vec3(0, 0, 0);
		}

		static void Forces(std::vector<mesh*> &All_Mesh)
		{
			for (int i=0;i< All_Mesh.size();i++)
			{
					
				All_Mesh[i]->transform.force = All_Mesh[i]->transform.force + glm::vec3(0, -9.8, 0);
				
			}
			BadHookeForce(All_Mesh);
		}
		static void HookeForce(std::vector<mesh*>& All_Mesh)
		{
			for (auto obj1 : All_Mesh)
			{	
				for (int i = 0; i < obj1->bro.size(); i++)
				{
					float distance = glm::distance(All_Mesh[obj1->bro[i]]->transform.position, obj1->transform.position);

					float stretch = distance - goodlength;
					glm::vec3 forceDirection = glm::normalize(All_Mesh[obj1->bro[i]]->transform.position - obj1->transform.position);

					// Calculate the spring force
					glm::vec3 springForce = stretch * springConstant * forceDirection;

					// Calculate the damping force
					glm::vec3 relativeVelocity = obj1->transform.velocity - All_Mesh[obj1->bro[i]]->transform.velocity;
					glm::vec3 dampingForce = -Damping * relativeVelocity;

					// Apply the forces
					obj1->transform.force += springForce + dampingForce;
				}
				
				for (auto obj2 : All_Mesh)
				{

					float distance = glm::distance(obj2->transform.position, obj1->transform.position);
					glm::vec3 forceDirection = glm::normalize(obj2->transform.position - obj1->transform.position);
					if (distance < thisRad * 2)
					{
						//obj1->transform.position = obj1->transform.position - forceDirection * (distance - thisRad) / 2.0f;
						//obj2->transform.position = obj2->transform.position + forceDirection * (distance - thisRad) / 2.0f;
					}
				}

			}
		}
		
		static void BadHookeForce(std::vector<mesh*>& All_Mesh)
		{
			for (auto obj1 : All_Mesh)
			{
				for (int i = 0; i < obj1->Bro.size(); i++)
				{
					if (SoftBodySim)
					{
						float distance = glm::distance(All_Mesh[obj1->Bro[i].x]->transform.position, obj1->transform.position);
						if (distance == 0)
						{
							break;
						}

						float stretch = distance - obj1->Bro[i].y;

						glm::vec3 forceDirection = glm::normalize(All_Mesh[obj1->Bro[i].x]->transform.position - obj1->transform.position);

						// Calculate the spring force
						glm::vec3 springForce = stretch * springConstant * forceDirection;


						// Calculate the damping force
						glm::vec3 relativeVelocity = obj1->transform.velocity - All_Mesh[obj1->Bro[i].x]->transform.velocity;
						glm::vec3 dampingForce = -Damping * relativeVelocity;

						// Apply the forces
						obj1->transform.force += springForce + dampingForce;
					}
					else
					{
						float distance = glm::distance(All_Mesh[obj1->Bro[i].x]->transform.position, obj1->transform.position);
						glm::vec3 Direction = glm::normalize(obj1->transform.position -All_Mesh[obj1->Bro[i].x]->transform.position);
						float stretch = distance - obj1->Bro[i].y;

						// Apply damping factor
						//stretch *= Damping;

						if (stretch > 0.01f && stretch != 0)
						{
							obj1->transform.position = obj1->transform.position - Direction * stretch;
						}
						else if (stretch < -0.01f && stretch != 0)
						{
							obj1->transform.position = obj1->transform.position + Direction * stretch;
						}


					}
				}

				for (auto obj2 : All_Mesh)
				{

					float distance = glm::distance(obj2->transform.position, obj1->transform.position);
					glm::vec3 forceDirection = glm::normalize(obj2->transform.position - obj1->transform.position);
					if (distance < thisRad * 2)
					{
						//obj1->transform.position = obj1->transform.position - forceDirection * (distance - thisRad) / 2.0f;
						//obj2->transform.position = obj2->transform.position + forceDirection * (distance - thisRad) / 2.0f;
					}
				}

			}
		}
};
#endif
