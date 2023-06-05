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

	GLuint boxVAO;
	GLenum boxVAOPrimitive;
	Material boxMaterial;

	std::vector<Object> objects;

	GLuint cubeVAO;
	GLenum cubeVAOPrimitive;
	Material cubeMaterial;

	PointLight pointLight;

	unsigned int boxVAOVertexCount;
	unsigned int cubeVAOVertexCount;

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

	glm::vec3 cameraPosition;
	glm::vec3 cameraDirection;
	glm::vec3 cameraUp;
	float cameraSpeed;

	uint64_t startTime;
	unsigned int totalFrames;

	// Mouse input
	bool isDragging;
	double lastMouseX;
	double lastMouseY;

	RenderConfig renderConfig;
};
