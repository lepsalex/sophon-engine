#include <Sophon.h>

class App : public Sophon::Application
{
public:
	App() {

	}

	~App() {

	}
};

Sophon::Application* Sophon::CreateApplication()
{
	return new App();
}