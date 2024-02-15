#include "sfnpch.h"

#include "Core/Input.h"

namespace Sophon {
bool Input::IsKeyPressed(const int key)
{
}
bool Input::IsMouseButtonPressed(int key)
{

}
std::pair<float, float> Input::GetMousePosition()
{

}
float Input::GetMouseX()
{
    auto [x, y] = GetMousePosition();
    return x;
}
float Input::GetMouseY()
{
    auto [x, y] = GetMousePosition();
    return y;
}
}