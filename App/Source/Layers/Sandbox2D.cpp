#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D")
    , m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
    auto textureOptions = Sophon::TextureOptions {
        Sophon::MinMagFilter::NEAREST,
        Sophon::MinMagFilter::NEAREST,
        Sophon::WrapOption::REPEAT,
        Sophon::WrapOption::REPEAT,
    };

    m_CheckerboardTexture = Sophon::Texture2D::Create("Assets/Textures/Checkerboard.png", textureOptions);
    m_LogoTexture = Sophon::Texture2D::Create("Assets/Textures/Opengl-logo.png", textureOptions);
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Sophon::Timestep ts)
{
    // UPDATE
    m_CameraController.OnUpdate(ts);

    // RENDER
    {
        SFN_PROFILE_SCOPE("Render Prep");
        Sophon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        Sophon::RenderCommand::Clear();
    }


    SFN_PROFILE_SCOPE("Render Draw");
    Sophon::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Sophon::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
    Sophon::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
    Sophon::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, m_CheckerboardTexture);
    Sophon::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.1f }, { 1.0f, 1.0f }, m_LogoTexture);
    Sophon::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
}

void Sandbox2D::OnEvent(Sophon::Event& e)
{
    m_CameraController.OnEvent(e);
}
