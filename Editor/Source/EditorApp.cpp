#include <Sophon.h>
#include <Core/EntryPoint.h>

#include "Layers/EditorLayer.h"

namespace Sophon {
    class EditorApp : public Application {
    public:
        EditorApp(const ApplicationSpecification& spec)
            : Application(spec)
        {
            PushLayer(new EditorLayer());
        }

        ~EditorApp()
        {
        }
    };

    Application* CreateApplication(ApplicationCommandLineArgs args)
    {
        ApplicationSpecification spec;
        spec.Name = "Editor";
        spec.CommandLineArgs = args;

        return new EditorApp(spec);
    }
}
