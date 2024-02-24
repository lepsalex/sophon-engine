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
    Sophon::ShaderLibrary m_ShaderLibrary;
    Sophon::Ref<Sophon::VertexArray> m_TriangleVertexArray;
    Sophon::Ref<Sophon::VertexArray> m_SquareVertexArray;
    Sophon::Ref<Sophon::Texture2D> m_Texture, m_LogoTexture;
    glm::vec4 m_FlatShaderColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
