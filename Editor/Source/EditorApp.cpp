#include <Sophon.h>
#include <Core/EntryPoint.h>

#include "Layers/EditorLayer.h"

namespace Sophon {
    class EditorApp : public Application {
    public:
        EditorApp()
        {
            PushLayer(new EditorLayer());
        }

        ~EditorApp()
        {
        }
    };

    Application* CreateApplication()
    {
        return new EditorApp();
    }
}
