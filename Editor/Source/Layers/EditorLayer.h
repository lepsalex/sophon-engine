#pragma once

#include "Sophon.h"

namespace Sophon {
    class EditorLayer : public Layer {
    public:
        EditorLayer();
        virtual ~EditorLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;

        void OnUpdate(Sophon::Timestep ts) override;
        virtual void OnImGuiRender() override;
        void OnEvent(Sophon::Event& e) override;

    private:
        bool OnKeyPressed(KeyPressedEvent& e);
        bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

    private:
        OrthographicCameraController m_CameraController;
        Ref<Sophon::Texture2D> m_CheckerboardTexture, m_LogoTexture;

        Ref<Framebuffer> m_Framebuffer;
        bool m_ViewportFocused = false, m_ViewportHovered = false;
        glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
        glm::vec2 m_ViewportBounds[2];
    };
}
