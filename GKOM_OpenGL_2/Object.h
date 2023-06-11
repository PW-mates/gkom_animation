#pragma once

#include <GL/glew.h>
#include "Animation.h"
#include "Material.h"

class Object
{
public:
	Object(GLuint VAO, GLenum VAOPrimitive, unsigned int VAOVertexCount, Material material, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	GLuint VAO;
	GLenum VAOPrimitive;
	unsigned int VAOVertexCount;
	Material material;

	Animation positionAnimation;
	Animation rotationAnimation;
	Animation scaleAnimation;
};