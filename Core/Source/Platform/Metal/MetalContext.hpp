#pragma once

#include "Renderer/GraphicsContext.h"

#import <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#import <GLFW/glfw3native.h>

namespace Sophon {
    class MetalContext : public GraphicsContext {
    public:
        MetalContext(GLFWwindow* windowHandle);
        ~MetalContext();

        virtual void Init() override;
        virtual void SwapBuffers() override;
    private:
        void InitDevice();
        void InitWindow();

    private:
        GLFWwindow* m_WindowHandle;
        
        struct pImplContext;
        Scope<pImplContext> m_pImplContext;
    };
}
