#pragma once

#include <glm/glm.hpp>

#include "Animation.h"

struct PointLight {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 color;

	Animation positionAnimation;
};