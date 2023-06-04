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

struct Material {
    std::string name;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

struct PointLight {
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
    glm::vec3 color;
};

struct Keyframe {
    float time;
    glm::vec3 value;
};

uint64_t getCurrentTime();

GLuint LoadBox(GLenum* primitive, unsigned int* count);
GLuint LoadObj(const std::string& path, GLenum* primitive, unsigned int* count, Material* material);
Material DefaultMtl();
Material LoadMtl(const std::string& path);
PointLight DefaultPointLight();

class Animation {
public:
    Animation();
    Animation(std::vector<Keyframe> keyframes);
    ~Animation();

    glm::vec3 evaluate(float time);
    void insertKeyframe(float time, glm::vec3 value);
    void editKeyframe(float time, glm::vec3 value);

private:
    std::vector<Keyframe> keyframes;
};