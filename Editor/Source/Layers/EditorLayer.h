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
       OrthographicCameraController m_CameraController;
       Ref<Sophon::Texture2D> m_CheckerboardTexture, m_LogoTexture;
    };
}

