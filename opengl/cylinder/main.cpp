#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include <SOIL.h>
#include <string>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "PlatformUtils.h"
#include "Camera.h"
#include <vector>
#include "Mesh.h"

int ScreenWidth = 640;
int ScreenHeight = 480;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

GLfloat lastX = ScreenWidth / 2.0;
GLfloat lastY = ScreenHeight / 2.0;

Camera camera = Camera();
bool keys[1024];

void DoCameraMovements()
{
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

bool firstMouse = true;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = ypos - lastY;
    lastX = xpos;
    lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

int main(int argc, char **argv)
{
    
    if(!glfwInit())
    {
        std::cout << "glfw init failed!" << std::endl;
        return 0;
    }
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    const char* texture_file[2] = {
        "container.jpg",
        "awesomeface.png"
    };
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(ScreenWidth, ScreenHeight, "Hello OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout<<"failed to init glew"<<std::endl;
        return -1;
    }
    
    std::cout << "OpenGL Vendor:" << glGetString(GL_VENDOR) << std::endl;
    std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    
    glfwSetKeyCallback(window, key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
    
    int width,height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
   
	/******set up cylinder vertices******/
	std::vector<Vertex> TopVertices;
	std::vector<Vertex> BottomVertices;
	std::vector<Vertex> SideVertices;

	const float PI = 3.1415926535897932384626433832795;
	float HalfHight = 0.5f;

	Vertex TopCenter = Vertex(0.0f, HalfHight, 0.0f, 0.0f, 0.0f, 1.0f, 0.5, 0.5);
	Vertex BottomCenter = Vertex(0.0f, -HalfHight, 0.0f, 0.0f, 0.0f, 1.0f, 0.5, 0.5);
	TopVertices.push_back(TopCenter);
	BottomVertices.push_back(BottomCenter);


	GLint SideCount = 36;

	for (int i = 0; i <= SideCount; ++i)
	{
		// gen top mesh
		GLfloat angle = i * PI * 2 / SideCount;
		Vertex vertex(cos(angle), HalfHight, sin(angle), 0.0f, 1.0f, 0.0f,
			(cos(angle) + 1) / 2.0, (sin(angle) / 2.0));
		TopVertices.push_back(vertex);

		// gen middle rectangle
		Vertex vertexDown(cos(angle), -HalfHight, sin(angle), cos(angle), 0, sin(angle),
			i / (float)SideCount, 0.0f);
		Vertex vertexUp(cos(angle), HalfHight, sin(angle), cos(angle), 0, sin(angle),
			i / (float)SideCount, 1.0f);

		std::cout << vertexDown << vertexUp;
		SideVertices.push_back(vertexDown);
		SideVertices.push_back(vertexUp);

		// gen bottom mesh
		angle = -angle;
		Vertex bvertex(cos(angle), -HalfHight, sin(angle), 0.0f, 0.0f, 1.0f,
			(cos(angle) + 1) / 2.0, (sin(angle) / 2.0));
		BottomVertices.push_back(bvertex);

	}

 
	//SideVertices.push_back(Vertex(0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	//SideVertices.push_back(Vertex(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	//SideVertices.push_back(Vertex(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));

	//SideVertices.push_back(Vertex(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	//SideVertices.push_back(Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	//SideVertices.push_back(Vertex(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));

	std::cout << TopVertices.size() << " " << SideVertices.size() << " " << BottomVertices.size() << std::endl;

	/******end set up cylinder vertices******/

	GLuint TopVAO, BottomVAO, SideVAO;
	GLuint TopVBO, BottomVBO, SideVBO;
	glGenVertexArrays(1, &TopVAO);
	glGenVertexArrays(1, &BottomVAO);
	glGenVertexArrays(1, &SideVAO);

	glGenBuffers(1, &TopVBO);
	glGenBuffers(1, &BottomVBO);
	glGenBuffers(1, &SideVBO);

	// Top
	glBindVertexArray(TopVAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, TopVBO);
	glBufferData(GL_ARRAY_BUFFER, TopVertices.size() * sizeof(Vertex), &TopVertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glBindVertexArray(0);


	glBindVertexArray(BottomVAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, BottomVBO);
	glBufferData(GL_ARRAY_BUFFER, BottomVertices.size() * sizeof(Vertex), &BottomVertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glBindVertexArray(0);


	glBindVertexArray(SideVAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, SideVBO);
	glBufferData(GL_ARRAY_BUFFER, SideVertices.size() * sizeof(Vertex), &SideVertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glBindVertexArray(0);

	std::string cyvs_path = common::GetShaderPath("cylinder.vs");
	std::string cyps_path = common::GetShaderPath("cylinder.ps");

	Shader cylinderShader(cyvs_path.c_str(), cyps_path.c_str());
	
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	Mesh mesh;
   
    while (!glfwWindowShouldClose(window)) {
		GLfloat current = glfwGetTime();
		deltaTime = current - lastFrame;
		lastFrame = current;

        glfwPollEvents();
		DoCameraMovements();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cylinderShader.Use();

		GLint modelLoc = glGetUniformLocation(cylinderShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(cylinderShader.Program, "view");
		GLint projectLoc = glGetUniformLocation(cylinderShader.Program, "projection");
        glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection = camera.GetProjectionMatrix();

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectLoc, 1, GL_FALSE, glm::value_ptr(projection));

		
		glm::mat4 model;
		//model = glm::rotate(model, (GLfloat)glfwGetTime()*0.5f, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		/*
		glBindVertexArray(TopVAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, TopVertices.size());
		glBindVertexArray(0);
	
		glBindVertexArray(SideVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, SideVertices.size());
		glBindVertexArray(0);

		glBindVertexArray(BottomVAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, BottomVertices.size());
		glBindVertexArray(0);
		*/
		mesh.DrawTest(cylinderShader);

        // bind textures
		/*
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glUniform1i(glGetUniformLocation(outShader.Program,"texture0"), 0);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glUniform1i(glGetUniformLocation(outShader.Program,"texture1"), 1);
        
        outShader.Use();
        
		GLint modelLoc = glGetUniformLocation(outShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(outShader.Program, "view");
		GLint projectLoc = glGetUniformLocation(outShader.Program, "projection");
        glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection = camera.GetProjectionMatrix();

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectLoc, 1, GL_FALSE, glm::value_ptr(projection));
		*/
	/*
		for (int i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[0]); ++i)
		{ 
			//std::cout << "this length" << sizeof(cubePositions) / sizeof(cubePositions[0]) << std::endl;
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (GLfloat)glfwGetTime()*0.5f, glm::vec3(0.5f, 1.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glBindVertexArray(VAO);
			
	//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			}
        glBindVertexArray(0);
		*/
		
        
        
        glfwSwapBuffers(window);
    }
    
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
    
    //delete [] textures;
    
    glfwTerminate();
	return 0;
}

