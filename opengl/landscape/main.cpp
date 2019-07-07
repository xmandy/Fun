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
#include "landscape.h"
#include "Mesh.h"
#include "Line.h"


int ScreenWidth = 1280;
int ScreenHeight = 960;

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

	// Landscape code starts here
   
    // create texures
    int tWidth, tHeight;
    
    int texture_length = 2;
    
    GLuint *textures = new GLuint[texture_length];
    glGenTextures(texture_length, textures);

    for (int i = 0; i < texture_length; ++i) {
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        // set texture wrapping mode
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        // set texture filtering mode
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		std::string path;
		common::GetTexturePath(path, texture_file[i]);
        
        unsigned char *image = SOIL_load_image(path.c_str(), &tWidth, &tHeight, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        SOIL_free_image_data(image);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
   
	std::cout << "111" << camera.Front.x << " " << camera.Front.y << " " << camera.Front.z << std::endl;

	Mesh mesh;

    glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

 	std::string cyvs_path = common::GetShaderPath("cylinder.vs");
	std::string cyps_path = common::GetShaderPath("cylinder.ps");

	Shader cylinderShader(cyvs_path.c_str(), cyps_path.c_str());

	Landscape landscape_obj(common::GetTexturePath("landscape/terrain_01.jpg"),
		BDT::Size(50, 50), 50, common::GetShaderPath("cylinder.vs"),
		common::GetShaderPath("cylinder.ps")
	);
	landscape_obj.SetUp();

	std::vector<BDT::LineVertex> LineVertices;
	// x, y, z in red green blue color
	LineVertices.push_back(BDT::LineVertex(glm::vec3(0, 0, 0), glm::vec3(255, 0, 0)));
	LineVertices.push_back(BDT::LineVertex(glm::vec3(10, 0, 0), glm::vec3(255, 0, 0)));
	LineVertices.push_back(BDT::LineVertex(glm::vec3(0, 0, 0), glm::vec3(0, 255, 0)));
	LineVertices.push_back(BDT::LineVertex(glm::vec3(0, 10, 0), glm::vec3(0, 255, 0)));
	LineVertices.push_back(BDT::LineVertex(glm::vec3(0, 0, 0), glm::vec3(0, 0, 255)));
	LineVertices.push_back(BDT::LineVertex(glm::vec3(0, 0, 10), glm::vec3(0, 0, 255)));

	Line CoordLines(LineVertices, common::GetShaderPath("line.vs"), common::GetShaderPath("default.ps"),
		GL_LINES);
	CoordLines.SetUp();

	camera.ScreenWidth = ScreenWidth;
	camera.ScreenHeight = ScreenHeight;
   
	while (!glfwWindowShouldClose(window)) {
		GLfloat current = glfwGetTime();
		deltaTime = current - lastFrame;
		lastFrame = current;

		glfwPollEvents();
		DoCameraMovements();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// bind textures
/*
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glUniform1i(glGetUniformLocation(outShader.Program,"texture0"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glUniform1i(glGetUniformLocation(outShader.Program,"texture1"), 1);
		*/


		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection = camera.GetProjectionMatrix();

		glm::mat4 model;

		CoordLines.Draw(model, view, projection);
		landscape_obj.Draw(model, view, projection);
		
        glfwSwapBuffers(window);
    }
    
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    
    delete [] textures;
    
    glfwTerminate();
	return 0;
}

