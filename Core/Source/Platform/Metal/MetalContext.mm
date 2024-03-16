#include "sfnpch.h"

#include <Metal/Metal.hpp>
#include <Metal/Metal.h>
#include <QuartzCore/CAMetalLayer.hpp>
#include <QuartzCore/CAMetalLayer.h>
#include <QuartzCore/QuartzCore.hpp>

#include "Platform/Metal/MetalContext.hpp"

namespace Sophon {
    struct MetalContext::pImplContext {
        MTL::Device* metalDevice;
        GLFWwindow* glfwWindow;
        NSWindow* metalWindow;
        CAMetalLayer* metalLayer;
    };

    MetalContext::MetalContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        SFN_CORE_ASSERT(windowHandle, "MetalContext::MetalContext: windowHandle is null!")
        m_pImplContext = CreateScope<pImplContext>();
    }

    // required due to incomplete types (pImplContext)
    MetalContext::~MetalContext() = default;

    void MetalContext::Init()
    {
        InitDevice();
        InitWindow();
        
        glfwMakeContextCurrent(m_WindowHandle);
        
        // TODO: Get status and debug info from Metal
    }

    void MetalContext::InitDevice()
    {
        SFN_PROFILE_FUNCTION();
        m_pImplContext->metalDevice = MTL::CreateSystemDefaultDevice();
    }

    void MetalContext::InitWindow()
    {
        SFN_PROFILE_FUNCTION();
        m_pImplContext->metalWindow = glfwGetCocoaWindow(m_WindowHandle);
        m_pImplContext->metalLayer = [CAMetalLayer layer];
        m_pImplContext->metalLayer.device = (__bridge id<MTLDevice>)m_pImplContext->metalDevice;
        m_pImplContext->metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
        m_pImplContext->metalWindow.contentView.layer = m_pImplContext->metalLayer;
        m_pImplContext->metalWindow.contentView.wantsLayer = YES;
    }

    void MetalContext::SwapBuffers()
    {
        SFN_PROFILE_FUNCTION();
    }
}
