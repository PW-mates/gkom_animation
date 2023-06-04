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

GLuint LoadBox(GLenum* primitive, unsigned int* count);
GLuint LoadObj(const std::string& path, GLenum* primitive, unsigned int* count);