
#include "Glew_Initialization.h"
#include "shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "ColorPicking.h"
#include "Sphere.h"
#include "PhysicsHandler.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"
#include "imgui_internal.h"
#include "Solidbody.h"
#include "Custom_mesh.h"
bool start_Simulation = false;
bool IsWidget;

Shaders shader; // main shader program
Shaders pickingshader; // picking color shader program

GenSphere c_Sphere;//generate sphre vertices

Color_Picking colorPicking; 

Glew_Initialization sys;



std::vector<mesh*> All_Mesh;//all objects

std::vector<mesh*> All_lines;//all objects


glm::vec3 SoftLocation;

glm::mat4 CamMatrix; //camera Matrix

Custom_mesh softbody;

void ManageWidget();

void SetRelativeTransfrom(glm::vec3 loc);
void Render_Scene();
void Render_Picking_Scene();
int  Get_Object(glm::vec4 ColorID);
bool Almost_Equal(glm::vec4 a, glm::vec4 b);
void InitiatePicking();
void ClearUp();
void CheckIfWidget(ImGuiIO& io)
{
	if (io.WantCaptureMouse || ImGui::IsAnyItemHovered())
	{
		IsWidget = true;
	}
	else
	{
		IsWidget = false;
	}
}

bool leftclicked = false;
int Cube_ID = 0;
int Cube2_ID = 0;

int shape = 0;
int main()
{
	
	sys.Init_Glfw();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(MainWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO();

	Camera camera;

	shader.Create_Normal_Shaders();
	pickingshader.Create_Picking_Shaders();

	// create custome framebuffer
	colorPicking.Init(sys.width, sys.height, glm::vec3(0, 0, 0));



	//create cubes and assign unique ColorIDs
	std::vector<Vertex> Sphere_vert;
	std::vector<unsigned int> Sphere_ind;
	c_Sphere.generateSphere(0.1f, 7, 7, glm::vec3(1, 0, 0), Sphere_vert, Sphere_ind);

	glm::vec3 allpos = glm::vec3(0, 0, 0);
	for (auto obj : All_Mesh)
	{
		allpos = allpos + obj->transform.position;
		
	}
	glm::vec3 SoftLocation = allpos / 8.0f;

	mesh* floor = new mesh;
	std::vector<Vertex> cube_vertex =
	{
		// positions          // colors           // normals         // texUV
	 { glm::vec3(-0.3,-0.3,-0.3), glm::vec3(1.0,1.0,0.5), glm::vec3(-1,-1,-1), glm::vec2(0, 0) },
	 { glm::vec3(-0.3,-0.3,0.3), glm::vec3(1.0,1.0,0.5), glm::vec3(-1,-1, 1), glm::vec2(1, 0) },
	 { glm::vec3(-0.3,0.3,-0.3),  glm::vec3(1.0,1.0,0.5), glm::vec3(-1, 1,-1), glm::vec2(0, 1) },
	 { glm::vec3(-0.3,0.3,0.3),  glm::vec3(1.0,1.0,0.5), glm::vec3(-1, 1, 1), glm::vec2(1, 1) },
	 { glm::vec3(0.3,-0.3,-0.3),  glm::vec3(1.0,1.0,0.5), glm::vec3(1,-1,-1),  glm::vec2(1, 0) },
	 { glm::vec3(0.3,-0.3,0.3),   glm::vec3(1.0,1.0,0.5), glm::vec3(1,-1, 1),  glm::vec2(0, 0) },
	 { glm::vec3(0.3,0.3,-0.3),  glm::vec3(1.0,1.0,0.5) , glm::vec3(1, 1,-1),  glm::vec2(1, 1) },
	 { glm::vec3(0.3,0.3,0.3),    glm::vec3(1.0,1.0,0.5), glm::vec3(1, 1, 1),  glm::vec2(0, 1) }
	};
	std::vector<unsigned int> cube_indices =
	{
	   0, 1, 2, 1, 2, 3, 4, 5, 6, 5, 6, 7, // front 
	   1, 5, 3, 5, 3, 7, 0, 4, 2, 4, 2, 6, // back 
	   0, 1, 4, 1, 4, 5, 2, 3, 6, 3, 6, 7  // sides
	};

	floor->CreateMesh(cube_vertex, cube_indices);
	floor->transform.position = glm::vec3(0, -25.0f, 0);
	floor->transform.velocity = glm::vec3(0, 0, 0);
	floor->ColorID = glm::vec4(0, 0, 0, 1);
	floor->transform.mass =50.0f;
	floor->transform.scale = glm::vec3(100, 0.1, 100);
	
	softbody.CreateBasicShapes(0);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(MainWindow))
	{
	
		CheckIfWidget(io);
		glfwPollEvents();
		CamMatrix = camera.Camera_Matrix();
		camera.Camera_Controls(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		Render_Scene();
		floor->RenderMesh(shader.shaderprogram, CamMatrix);
		InitiatePicking();


		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//ui implementation
		
		ManageWidget();


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(MainWindow);
		

	}
	delete floor;
	ClearUp();
	glfwDestroyWindow(MainWindow);
	glfwTerminate();
	
}


void Render_Scene()
{
	if (start_Simulation)
	{
		//PhysicsHandler::Forces(All_Mesh);
		PhysicsHandler::Forces(softbody.points);
	}

	for (int i = 0; i < softbody.points.size(); i++)
	{
		if (start_Simulation)
		{
			//PhysicsHandler::Step(All_Mesh[i]->transform);
			PhysicsHandler::Step(softbody.points[i]->transform);
		}

	}
	for (auto Line : All_Mesh)
	{
		//Line->RenderMesh(shader.shaderprogram, CamMatrix);
		
	}
	
	for (auto obj : All_lines)
	{
		obj->DrawLine(shader.shaderprogram, CamMatrix);
	}
	softbody.Rendermesh(shader.shaderprogram, CamMatrix,false);
}
void Render_Picking_Scene()
{
	for (int i = 0; i < All_Mesh.size(); i++)
	{
		All_Mesh[i]->RenderMesh(pickingshader.shaderprogram, CamMatrix);
	}
}
void InitiatePicking()
{
	if (glfwGetMouseButton(MainWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !IsWidget)
	{
		if (!leftclicked)
		{
			Render_Scene();
			Render_Picking_Scene();
			//draw cubes in the custom frame buffer
			colorPicking.EnableWriting();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			Render_Picking_Scene();
			colorPicking.DisableWriting();
			//read color values from custom frame buffer
			Cube_ID = Get_Object(colorPicking.Read_Pixels());

			All_Mesh[Cube_ID]->UpdateColor(glm::vec3(0.9f,0.9f,0.9f));

			for (int i = 0; i < All_Mesh.size(); i++)
			{
				if (i != Cube_ID)
				{
					All_Mesh[i]->UpdateColor(All_Mesh[i]->Color);
				}
			}
			leftclicked = true;
		}

	}
	else if (glfwGetMouseButton(MainWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		if (leftclicked)
		{
			leftclicked = false;
		}

	}
}
int Get_Object(glm::vec4 ColorID)
{
	int e = 0;
	for (int i = 0; i < All_Mesh.size(); i++)
	{
		if (Almost_Equal(All_Mesh[i]->ColorID, ColorID))
		{
			e = i;
			break;

		}
	}
	return e;

}
bool Almost_Equal(glm::vec4 a, glm::vec4 b)
{
	double epsilon = 0.0001;
	bool check_diff = true;
	for (int i = 0; i < 4; i++)
	{
		if (std::abs(a[i] - b[i]) > epsilon)
		{
			check_diff = false;
		}
	}
	return check_diff;
}
void ClearUp()
{
	for (auto obj : All_Mesh)
	{
		obj->ClearMesh();
	}
	for (auto obj : All_lines)
	{
		obj->ClearMesh();
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
void ManageWidget()
{
	ImGui::Begin("Settings");
	ImGui::Text("Object ID");
	ImGui::SameLine();
	ImGui::Text("%0.1d", Cube_ID);
	if (ImGui::InputInt("Shape type", &shape))
	{
		start_Simulation = false;
		for (auto obj : softbody.points)
		{
			obj->ClearMesh();
		}
		softbody.points.clear();
		softbody.CreateBasicShapes(shape);
	}
	if(ImGui::Button("Reset"))
	{
		start_Simulation = false;
		for (auto obj : softbody.points)
		{
			obj->ClearMesh();
		}
		softbody.points.clear();
		softbody.CreateBasicShapes(shape);
	}
	if (ImGui::InputInt("Surface Divide", &softbody.div,1))
	{
		for (auto obj : softbody.points)
		{
			obj->ClearMesh();
		}
		softbody.points.clear();
		softbody.CreateBasicShapes(shape);
	}
	ImGui::Checkbox("Soft Body", &SoftBodySim);
	ImGui::Checkbox("Start Simulation", &start_Simulation);
	
	if (ImGui::CollapsingHeader("Gigglity"))
	{
		ImGui::InputFloat("Giggle strenght", &springConstant);
		ImGui::InputFloat("Damping", &Damping);
	}
	

	if (ImGui::CollapsingHeader("Object Transfrom"))
	{
		float pos3[3] = { All_Mesh[Cube_ID]->transform.position.x, All_Mesh[Cube_ID]->transform.position.y, All_Mesh[Cube_ID]->transform.position.z };
		
		if (ImGui::InputFloat3("position", pos3))
		{
			All_Mesh[Cube_ID]->transform.position.x = pos3[0];
			All_Mesh[Cube_ID]->transform.position.y = pos3[1];
			All_Mesh[Cube_ID]->transform.position.z = pos3[2];
			
		}
		float sca3[3] = { All_Mesh[Cube_ID]->transform.scale.x, All_Mesh[Cube_ID]->transform.scale.y, All_Mesh[Cube_ID]->transform.scale.z };

		if (ImGui::InputFloat3("scale", sca3))
		{
			All_Mesh[Cube_ID]->transform.scale.x = sca3[0];
			All_Mesh[Cube_ID]->transform.scale.y = sca3[1];
			All_Mesh[Cube_ID]->transform.scale.z = sca3[2];
		}
		float vec3[3] = { All_Mesh[Cube_ID]->transform.velocity.x, All_Mesh[Cube_ID]->transform.velocity.y, All_Mesh[Cube_ID]->transform.velocity.z };

		if (ImGui::InputFloat3("velocity", vec3))
		{
			All_Mesh[Cube_ID]->transform.velocity.x = vec3[0];
			All_Mesh[Cube_ID]->transform.velocity.y = vec3[1];
			All_Mesh[Cube_ID]->transform.velocity.z = vec3[2];
			
		}
		float  spos3[3] = { SoftLocation.x ,SoftLocation.y,SoftLocation.z };
		if (ImGui::InputFloat3("Soft location", spos3))
		{
			SoftLocation.x = spos3[0];
			SoftLocation.y = spos3[1];
			SoftLocation.z = spos3[2];
			SetRelativeTransfrom(glm::vec3(0, 0, 0));
		}
			
		if (ImGui::InputFloat("mass", &All_Mesh[Cube_ID]->transform.mass))
		{
			
		}
		
	}
	ImGui::End();
}






void SetRelativeTransfrom(glm::vec3 loc)
{
	for (auto obj : All_Mesh)
	{
		obj->transform.position = SoftLocation + obj->transform.position;
	}
}