#include "Object.h"

Object::Object(GLuint VAO, GLenum VAOPrimitive, unsigned int VAOVertextCount, Material material, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->VAO = VAO;
	this->VAOPrimitive = VAOPrimitive;
	this->VAOVertexCount = VAOVertextCount;
	this->material = material;

	this->positionAnimation = Animation();
	this->rotationAnimation = Animation();
	this->scaleAnimation = Animation();

	this->positionAnimation.insertKeyframe(1, position);
	this->rotationAnimation.insertKeyframe(1, rotation);
	this->scaleAnimation.insertKeyframe(1, scale);
}