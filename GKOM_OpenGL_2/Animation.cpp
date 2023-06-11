#include "Animation.h"
#include <algorithm>

Animation::Animation() {
    keyframes = std::vector<Keyframe>();
}

Animation::Animation(std::vector<Keyframe> keyframes)
    : keyframes(keyframes)
{
    std::sort(this->keyframes.begin(), this->keyframes.end(),
        [](const Keyframe& a, const Keyframe& b) { return a.time < b.time; });
}

Animation::~Animation() {
    keyframes.clear();
}

glm::vec3 Animation::evaluate(float time) {
    if (keyframes.empty()) return glm::vec3(0.0f);

    if (time <= keyframes.front().time) return keyframes.front().value;
    if (time >= keyframes.back().time) return keyframes.back().value;

    auto next_keyframe = std::lower_bound(keyframes.begin(), keyframes.end(), time,
        [](const Keyframe& keyframe, float time) { return keyframe.time < time; });
    auto prev_keyframe = next_keyframe - 1;

    float t = (time - prev_keyframe->time) / (next_keyframe->time - prev_keyframe->time);
    return glm::mix(prev_keyframe->value, next_keyframe->value, t);
}

void Animation::insertKeyframe(float time, glm::vec3 value) {
    keyframes.push_back({ time, value });
    std::sort(keyframes.begin(), keyframes.end(),
        [](const Keyframe& a, const Keyframe& b) { return a.time < b.time; });
}

void Animation::editKeyframe(float time, glm::vec3 value) {
    auto it = std::find_if(keyframes.begin(), keyframes.end(),
        [time](const Keyframe& keyframe) { return keyframe.time == time; });
    if (it != keyframes.end()) {
        it->value = value;
    }
}

void Animation::clearKeyframes()
{
	keyframes.clear();
}