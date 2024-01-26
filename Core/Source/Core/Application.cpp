#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Sophon {
	Application::Application() {}

	Application::~Application() {}
	void Application::Run() {
		WindowResizeEvent e(100, 100);
		SFN_CORE_ERROR(e);

		while (true);
	}
}  // namespace Sophon