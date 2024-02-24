#include <Sophon.h>
#include <Core/EntryPoint.h>

#include "Layers/Sandbox2D.h"

class App : public Sophon::Application {
public:
    App()
    {
        PushLayer(new Sandbox2D());
    }

    ~App()
    {
    }
};

Sophon::Application* Sophon::CreateApplication()
{
    return new App();
}
