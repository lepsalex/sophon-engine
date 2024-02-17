#include <Sophon.h>

class ExampleLayer : public Sophon::Layer {
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        // SFN_CLIENT_INFO("ExampleLayer::Update");
        auto [xpos, ypos] = Sophon::Input().GetMousePosition();
        SFN_CLIENT_INFO("MouseX: {0}, MouseY: {1}", xpos, ypos);
    }

    void OnEvent(Sophon::Event& event) override
    {
        // SFN_CLIENT_TRACE("{0}", event);
    }
};

class App : public Sophon::Application {
public:
    App()
    {
        PushLayer(new ExampleLayer());
    }

    ~App()
    {
    }
};

Sophon::Application* Sophon::CreateApplication()
{
    return new App();
}