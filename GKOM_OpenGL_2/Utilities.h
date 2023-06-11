#pragma once

#define _CRT_SECURE_NO_WARNINGS


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

#include <filesystem>
#include <chrono>

#include <sys/stat.h>
#include "json.hpp"
using json = nlohmann::json;
#include "Material.h"
#include "Camera.h"
#include "PointLight.h"
#include "AppConfig.h"
#include "Object.h"


struct RenderConfig {
    unsigned int currentFrame;
    unsigned int frameRate;
    unsigned int frameCount;
    unsigned int stepPerFrame;
    std::string tempFolder;
    std::string outputName;
    bool rendering = false;
};

uint64_t getCurrentTime();

GLuint LoadBox(GLenum* primitive, unsigned int* count);
GLuint LoadObj(const std::string& path, GLenum* primitive, unsigned int* count, Material* material);
Material DefaultMtl();
Material LoadMtl(const std::string& path);
PointLight DefaultPointLight();
void LoadAnimation(std::string programDirectory, AppConfig* appConfig, Camera *camera, std::vector<PointLight>* lights, std::vector<Object>* objects);
