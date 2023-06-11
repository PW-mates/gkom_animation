#pragma once

#include <glm/glm.hpp>

#include "Animation.h"

struct Camera {
    glm::vec3 up;

    Animation positionAnimation;
    Animation directionAnimation;
};
