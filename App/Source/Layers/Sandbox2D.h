#pragma once

#include "Sophon.h"

class Sandbox2D : public Sophon::Layer {
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(Sophon::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(Sophon::Event& e) override;

private:
    Sophon::OrthographicCameraController m_CameraController;
    Sophon::Ref<Sophon::Texture2D> m_CheckerboardTexture, m_LogoTexture;
};
