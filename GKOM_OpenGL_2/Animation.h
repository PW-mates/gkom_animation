#pragma once

#include <vector>
#include <glm/glm.hpp>

struct Keyframe {
    float time;
    glm::vec3 value;
};

class Animation {
public:
    Animation();
    Animation(std::vector<Keyframe> keyframes);
    ~Animation();

    glm::vec3 evaluate(float time);
    void insertKeyframe(float time, glm::vec3 value);
    void editKeyframe(float time, glm::vec3 value);
    void clearKeyframes();
private:
    std::vector<Keyframe> keyframes;
};
