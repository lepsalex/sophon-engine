#pragma once

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Sophon {
    class MetalContext : public GraphicsContext {
    public:
        MetalContext(GLFWwindow* windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* m_WindowHandle;
    };
}
