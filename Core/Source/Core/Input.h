#pragma once
#include <utility>

namespace Sophon {
class Input {
public:
    static bool IsKeyPressed(int key);
    static bool IsMouseButtonPressed(int key);
    static std::pair<float, float> GetMousePosition();
    static float GetMouseX();
    static float GetMouseY();
};
}