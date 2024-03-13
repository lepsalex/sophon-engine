#include "sfnpch.h"
#include "Utils/PlatformUtils.h"

#include <GLFW/glfw3.h>

namespace Sophon {
    float Time::GetTime()
    {
        return static_cast<float>(glfwGetTime());
    }
}
