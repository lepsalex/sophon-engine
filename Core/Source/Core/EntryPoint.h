#pragma once

#ifdef SFN_PLATFORM_WINDOWS

extern Sophon::Application* Sophon::CreateApplication();

int main()
{
	auto app = Sophon::CreateApplication();
	app->Run();
	delete app;
}

#else
#error Sophon only supports Windows!
#endif