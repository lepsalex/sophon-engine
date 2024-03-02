#include <Sophon.h>
#include <Core/EntryPoint.h>

#include "Layers/Sandbox2D.h"

class App : public Sophon::Application {
public:
    App(const Sophon::ApplicationSpecification& specification)
        : Sophon::Application(specification)
    {
        PushLayer(new Sandbox2D());
    }

    ~App()
    {
    }
};

Sophon::Application* Sophon::CreateApplication(Sophon::ApplicationCommandLineArgs args)
{
    ApplicationSpecification spec;
    spec.Name = "Sandbox App";
    spec.WorkingDirectory = "../Editor";
    spec.CommandLineArgs = args;

    return new App(spec);
}
