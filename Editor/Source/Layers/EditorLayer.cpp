#include "EditorLayer.h"

namespace Sophon {
    EditorLayer::EditorLayer()
        : Layer("EditorLayer")
        , m_CameraController(1280.0f / 720.0f)
    {
    }

    void EditorLayer::OnAttach()
    {
        SFN_PROFILE_FUNCTION();

        auto textureOptions = Sophon::TextureOptions {
            Sophon::MinMagFilter::LINEAR,
            Sophon::MinMagFilter::LINEAR,
            Sophon::WrapOption::REPEAT,
            Sophon::WrapOption::REPEAT,
        };

        m_CheckerboardTexture = Sophon::Texture2D::Create("Assets/Textures/Checkerboard.png", textureOptions);
        m_LogoTexture = Sophon::Texture2D::Create("Assets/Textures/Opengl-logo.png", textureOptions);
    }

    void EditorLayer::OnDetach()
    {
    }

    void EditorLayer::OnUpdate(Sophon::Timestep ts)
    {
        SFN_PROFILE_FUNCTION();

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
        Sophon::Renderer2D::DrawRotatedQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, 45.0f, { 0.2f, 0.3f, 0.8f, 1.0f });
        Sophon::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, m_CheckerboardTexture, 5.0f, { 0.9f, 0.8f, 0.7f, 1.0f });
        Sophon::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.1f }, { 1.0f, 1.0f }, m_LogoTexture);
        Sophon::Renderer2D::EndScene();
    }

    void EditorLayer::OnImGuiRender()
    {
    }

    void EditorLayer::OnEvent(Sophon::Event& e)
    {
        m_CameraController.OnEvent(e);
    }
}
