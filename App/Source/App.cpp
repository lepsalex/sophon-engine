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
        if (Sophon::Input::IsKeyPressed(Sophon::Key::Space))
            SFN_CLIENT_TRACE("Space is being pressed!");
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