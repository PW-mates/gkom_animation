#include "OpenGLWindow.h"

void FramebufferSizeChangeCallback(GLFWwindow* window, int width, int height);
void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

OpenGLWindow::OpenGLWindow()
{
	_window = nullptr;

    boxVAO = 0;

    windowResolution = glm::vec2(1200, 900);
    fieldOfView = 45;

    cameraPosition = glm::vec3(0, 0, 20);
    cameraDirection = glm::vec3(0, 0, -1);
    cameraUp = glm::vec3(0, 1, 0);
    cameraSpeed = 0.01f;
    isDragging = false;

    startTime = getCurrentTime();
}

OpenGLWindow::~OpenGLWindow()
{
    glfwTerminate();
}

bool OpenGLWindow::InitWindow()
{
    if (!glfwInit())
    {
        std::cerr << "GLFW initialization failed!" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(windowResolution.x, windowResolution.y, "GKOM_OpenGL_2", NULL, NULL);

    if (_window == NULL)
    {
        std::cerr << "GLFW window creation failed!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(_window);

    if (glewInit())
    {
        std::cerr << "GLEW window creation failed!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwSetFramebufferSizeCallback(_window, FramebufferSizeChangeCallback);
    glfwSetScrollCallback(_window, MouseScrollCallback);

    

    return true;
}

void OpenGLWindow::InitScene()
{
    transformationProgram.Load("transformationshader.vs", "transformationshader.fs");

    phongProgram.Load("phongshader.vs", "phongshader.fs");

    boxVAO = LoadBox(&boxVAOPrimitive, &boxVAOVertexCount);
    boxMaterial = DefaultMtl();

    cubeVAO = LoadObj("..\\Resources\\Models\\sphere.obj", &cubeVAOPrimitive, &cubeVAOVertexCount, &cubeMaterial);

    pointLight = DefaultPointLight();
}

void OpenGLWindow::MainLoop()
{
    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    
    Program lightProgram;
    bool useTransformations = false;

    while (!glfwWindowShouldClose(_window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        projectionMatrix = glm::perspective(glm::radians(fieldOfView), windowResolution.x / windowResolution.y, 0.1f, 100.0f);

        cameraMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraDirection, cameraUp);

        if (useTransformations) {
            lightProgram = transformationProgram;
            transformationProgram.Activate();

            glUniformMatrix4fv(transformationProgram.GetUniformID("uCameraMatrix"), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
            glUniformMatrix4fv(transformationProgram.GetUniformID("uProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        }
        else {
            lightProgram = phongProgram;
            phongProgram.Activate();
            glUniformMatrix4fv(phongProgram.GetUniformID("uCameraMatrix"), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
            glUniformMatrix4fv(phongProgram.GetUniformID("uProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
            glUniform3fv(phongProgram.GetUniformID("uViewPos"), 1, glm::value_ptr(cameraPosition));
            // glUniformMatrix4fv(phongProgram.GetUniformID("uViewPos"), 1, GL_FALSE, glm::value_ptr(cameraPosition));

            // Update light properties
            
            glUniform3fv(phongProgram.GetUniformID("uLight.position"), 1, glm::value_ptr(pointLight.position));
            glUniform3fv(phongProgram.GetUniformID("uLight.ambient"), 1, glm::value_ptr(pointLight.ambient));
            glUniform3fv(phongProgram.GetUniformID("uLight.diffuse"), 1, glm::value_ptr(pointLight.diffuse));
            glUniform3fv(phongProgram.GetUniformID("uLight.specular"), 1, glm::value_ptr(pointLight.specular));
            glUniform3fv(phongProgram.GetUniformID("uLight.color"), 1, glm::value_ptr(pointLight.color));
        }

        for (int i = -2; i <= 2; i++)
        {
            for (int j = -2; j <= 2; j++)
            {
                renderObject(lightProgram, boxVAO, boxVAOPrimitive, boxVAOVertexCount, glm::vec3(i * 3.0f, j * 3.0f, 0.0f), boxMaterial);
            }
        }

        renderObject(lightProgram, cubeVAO, cubeVAOPrimitive, cubeVAOVertexCount, glm::vec3(0.0f, 0.0f, 10.0f), cubeMaterial);
        

        processInput();
        processMouseInput();

        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
}

void OpenGLWindow::renderObject(Program& program, GLuint VAO, GLenum primitive, unsigned int count, glm::vec3 position, Material material)
{
    modelMatrix = glm::translate(glm::mat4(2.0f), position);
    glUniformMatrix4fv(program.GetUniformID("uModelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniform3fv(program.GetUniformID("uMaterial.ambient"), 1, glm::value_ptr(cubeMaterial.ambient));
    glUniform3fv(program.GetUniformID("uMaterial.diffuse"), 1, glm::value_ptr(cubeMaterial.diffuse));
    glUniform3fv(program.GetUniformID("uMaterial.specular"), 1, glm::value_ptr(cubeMaterial.specular));
    glUniform1f(program.GetUniformID("uMaterial.shininess"), cubeMaterial.shininess);

    glBindVertexArray(VAO);
    glDrawArrays(primitive, 0, count);
}

void OpenGLWindow::processInput()
{
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(_window, true);
    }

    // Camera movement

    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
    {
        // Move forward
        cameraPosition.z -= cameraSpeed;
    }

    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
    {
        // Move backward
        cameraPosition.z += cameraSpeed;
    }

    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        // Move left
        cameraPosition.x -= cameraSpeed;
    }

    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        // Move right
        cameraPosition.x += cameraSpeed;
    }

    if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        // Move up
        cameraPosition.y -= cameraSpeed;
    }

    if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
    {
        // Move down
        cameraPosition.y += cameraSpeed;
    }

    // Camera direction

    if (glfwGetKey(_window, GLFW_KEY_1) == GLFW_PRESS)
    {
        // Look forward
        cameraDirection = glm::vec3(0, 0, -1);
    }

    if (glfwGetKey(_window, GLFW_KEY_2) == GLFW_PRESS)
    {
        // Look backward
        cameraDirection = glm::vec3(0, 0, 1);
    }

    if (glfwGetKey(_window, GLFW_KEY_3) == GLFW_PRESS)
    {
        // Look left
        cameraDirection = glm::vec3(-1, 0, 0);
    }

    if (glfwGetKey(_window, GLFW_KEY_4) == GLFW_PRESS)
    {
        // Look right
        cameraDirection = glm::vec3(1, 0, 0);
    }

    if (glfwGetKey(_window, GLFW_KEY_5) == GLFW_PRESS)
    {
		// Look up
		cameraDirection = glm::vec3(0, 1, 0);
	}

    if (glfwGetKey(_window, GLFW_KEY_6) == GLFW_PRESS)
    {
		// Look down
		cameraDirection = glm::vec3(0, -1, 0);
	}
}

void OpenGLWindow::processMouseInput() {
    if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
		// Start dragging
        if (!isDragging)
        {
			isDragging = true;
			glfwGetCursorPos(_window, &lastMouseX, &lastMouseY);
		}
        else
        {
			// Compute new orientation
			double mouseX, mouseY;
			glfwGetCursorPos(_window, &mouseX, &mouseY);

			double deltaX = mouseX - lastMouseX;
			double deltaY = mouseY - lastMouseY;

			lastMouseX = mouseX;
			lastMouseY = mouseY;

			double yawSign = cameraUp.y < 0 ? -1.0f : 1.0f;

            if (cameraDirection.x != 0)
            {
                cameraPosition.y -= yawSign * deltaY * cameraSpeed * -1;
                cameraPosition.z -= yawSign * deltaX * cameraSpeed * cameraDirection.x;
            }
            else if (cameraDirection.y != 0)
            {
                cameraPosition.x += yawSign * deltaX * cameraSpeed * cameraDirection.y;
				cameraPosition.z += yawSign * deltaY * cameraSpeed * cameraDirection.y;
            }
            else if (cameraDirection.z != 0)
            {
				cameraPosition.x += yawSign * deltaX * cameraSpeed * cameraDirection.z;
                cameraPosition.y += yawSign * deltaY * cameraSpeed;
            }
		    
        }
	}
	else
	{
		// Stop dragging
		isDragging = false;
	}
}

void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    std::cout << "Scroll offset: " << xoffset << ", " << yoffset << std::endl;
    
}

void FramebufferSizeChangeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}