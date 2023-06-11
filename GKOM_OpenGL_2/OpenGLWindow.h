#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <chrono>

#include "Program.h"
#include "Utilities.h"
#include "AppConfig.h"
#include "Object.h"

class OpenGLWindow
{
public:

	OpenGLWindow();
	~OpenGLWindow();

	bool InitWindow();

	void InitScene();

	void MainLoop();

private:

	GLFWwindow* _window;

	Program transformationProgram;
	Program phongProgram;

	void renderObject(Program& program, GLuint VAO, GLenum primitive, unsigned int count, Material material, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	void processInput();
	void processMouseInput();

	void capture_frame(const std::string& filename);
	void renderToFile(const std::string& filename);

	glm::vec2 windowResolution;
	float fieldOfView;

	glm::mat4 projectionMatrix;
	glm::mat4 cameraMatrix;
	glm::mat4 modelMatrix;

	// Camera
	Camera camera;
	bool perspectiveCamera;

	glm::vec3 cameraPosition;
	glm::vec3 cameraDirection;
	glm::vec3 cameraUp;
	float cameraSpeed;

	// Light
	std::vector<PointLight> pointLights;

	// Objects
	std::vector<Object> objects;
	uint64_t startTime;

	// Mouse input
	bool isDragging;
	double lastMouseX;
	double lastMouseY;

	RenderConfig renderConfig;
	AppConfig appConfig;
};
