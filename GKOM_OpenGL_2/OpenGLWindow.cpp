#include "OpenGLWindow.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define _CRT_SECURE_NO_WARNINGS
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


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
    totalFrames = 5000;
    objects = std::vector<Object>();
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
    Object obj = Object(cubeVAO, cubeVAOPrimitive, cubeVAOVertexCount, cubeMaterial, glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    obj.positionAnimation.insertKeyframe(1000, glm::vec3(0, 0, 15));
    obj.positionAnimation.insertKeyframe(3000, glm::vec3(10, 0, 0));
    obj.positionAnimation.insertKeyframe(5000, glm::vec3(0, 0, 10));
    obj.rotationAnimation.insertKeyframe(1000, glm::vec3(0, 0, 0));
    obj.rotationAnimation.insertKeyframe(3000, glm::vec3(0, 0, 90));
    obj.rotationAnimation.insertKeyframe(5000, glm::vec3(0, 90, 0));
    obj.scaleAnimation.insertKeyframe(1000, glm::vec3(1, 1, 1));
    obj.scaleAnimation.insertKeyframe(3000, glm::vec3(0, 0, 0));
    obj.scaleAnimation.insertKeyframe(5000, glm::vec3(3, 3, 3));
    objects.push_back(obj);

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
        if (getCurrentTime() - startTime > totalFrames) {
			startTime = getCurrentTime();
		}
        float currentFrame = (getCurrentTime() - startTime);
        if (renderConfig.rendering) {
            currentFrame = renderConfig.currentFrame * renderConfig.stepPerFrame;
        }
        

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

        glm::vec3 defaultScaleVector = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 defaultRotationVector = glm::vec3(0.0f, 0.0f, 0.0f);
        for (int i = -2; i <= 2; i++)
        {
            for (int j = -2; j <= 2; j++)
            {
                renderObject(lightProgram, boxVAO, boxVAOPrimitive, boxVAOVertexCount, boxMaterial, glm::vec3(i * 3.0f, j * 3.0f, 0.0f), defaultRotationVector, defaultScaleVector);
            }
        }

        // renderObject(lightProgram, cubeVAO, cubeVAOPrimitive, cubeVAOVertexCount, glm::vec3(0.0f, 0.0f, 10.0f), cubeMaterial);
        
        for (auto obj: objects)
        {
            glm::vec3 objPosition = obj.positionAnimation.evaluate(currentFrame);
            glm::vec3 objRotation = obj.rotationAnimation.evaluate(currentFrame);
            glm::vec3 objScale = obj.scaleAnimation.evaluate(currentFrame);
			renderObject(lightProgram, obj.VAO, obj.VAOPrimitive, obj.VAOVertexCount, obj.material, objPosition, objRotation, objScale);
		}

        processInput();
        processMouseInput();

        if (renderConfig.rendering) {
            struct stat info;
            if (stat(renderConfig.tempFolder.c_str(), &info) == -1) {
				std::filesystem::create_directory(renderConfig.tempFolder);
			}
            capture_frame(renderConfig.tempFolder +"/"+ "frame"+ std::to_string(renderConfig.currentFrame) + ".png");
			renderConfig.currentFrame++;
            if (renderConfig.currentFrame > renderConfig.frameCount) {
				renderConfig.rendering = false;
                renderToFile(renderConfig.outputName);
			}
            if (renderConfig.currentFrame % 10 == 0) {
                std::cout << "Rendered " << renderConfig.currentFrame << " / " << renderConfig.frameCount << "  frames." << std::endl;
            }
		}

        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
}

void OpenGLWindow::renderObject(Program& program, GLuint VAO, GLenum primitive, unsigned int count, Material material, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    modelMatrix = glm::translate(glm::mat4(2.0f), position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, scale);

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

    if (glfwGetKey(_window, GLFW_KEY_C) == GLFW_PRESS)
    {
		// Save one frame to file
        capture_frame("output.png");
	}

    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
    {
		// Render to video
        renderConfig.currentFrame = 0;
        renderConfig.frameRate = 30;
        renderConfig.frameCount = totalFrames / 1000 * renderConfig.frameRate;
        renderConfig.stepPerFrame = totalFrames / renderConfig.frameCount;
        renderConfig.tempFolder = "./temp";
        renderConfig.outputName = "output.mp4";
        renderConfig.rendering = true;

        std::cout << "Start capturing video" << std::endl;
	}

    // Camera direction

    if (glfwGetKey(_window, GLFW_KEY_1) == GLFW_PRESS)
    {
        // Look forward
        cameraDirection = glm::vec3(0, 0, -1);
        cameraPosition = glm::vec3(0, 0, 20);
    }

    if (glfwGetKey(_window, GLFW_KEY_2) == GLFW_PRESS)
    {
        // Look backward
        cameraDirection = glm::vec3(0, 0, 1);
        cameraPosition = glm::vec3(0, 0, -20);
    }

    if (glfwGetKey(_window, GLFW_KEY_3) == GLFW_PRESS)
    {
        // Look left
        cameraDirection = glm::vec3(-1, 0, 0);
        cameraPosition = glm::vec3(20, 0, 0);
    }

    if (glfwGetKey(_window, GLFW_KEY_4) == GLFW_PRESS)
    {
        // Look right
        cameraDirection = glm::vec3(1, 0, 0);
        cameraPosition = glm::vec3(-20, 0, 0);
    }

    if (glfwGetKey(_window, GLFW_KEY_5) == GLFW_PRESS)
    {
		// Look up
		cameraDirection = glm::vec3(0, 1, 0);
        cameraPosition = glm::vec3(0, -20, 0);
	}

    if (glfwGetKey(_window, GLFW_KEY_6) == GLFW_PRESS)
    {
		// Look down
		cameraDirection = glm::vec3(0, -1, 0);
        cameraPosition = glm::vec3(0, 20, 0);
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
            
            if (glfwGetKey(_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
            {
                std::cout << "Alt key pressed" << std::endl;
                cameraDirection.x += yawSign * deltaX * cameraSpeed * -1;
                cameraDirection.y += yawSign * deltaY * cameraSpeed * -1;
            }
            else {
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

void OpenGLWindow::capture_frame(const std::string& filename)
{
    int width = windowResolution.x, height = windowResolution.y;
    std::vector<unsigned char> buffer(width * height * 3);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());

    // Flip image vertically
    std::vector<unsigned char> flipped_buffer(width * height * 3);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < 3; c++) {
                flipped_buffer[3 * (y * width + x) + c] = buffer[3 * ((height - 1 - y) * width + x) + c];
            }
        }
    }

    stbi_write_png(filename.c_str(), width, height, 3, flipped_buffer.data(), 3 * width);
}

void OpenGLWindow::renderToFile(const std::string& path)
{
    std::string size = std::to_string((int)windowResolution.x) + "x" + std::to_string((int)windowResolution.y);
    system(("ffmpeg.exe -r 30 -f image2 -s " + size + " -i ./temp/frame%d.png -vcodec libx264 -crf 25 -pix_fmt yuv420p output.mp4").c_str());
    std::filesystem::remove_all(renderConfig.tempFolder);
    std::cout << "Video saved to " << path << std::endl;
}