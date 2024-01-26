#pragma once

#ifdef SFN_PLATFORM_WINDOWS

extern Sophon::Application* Sophon::CreateApplication();

int main() {
	// todo: temp will be moved
	Sophon::Log::Init();
	SFN_CORE_WARN("Init Log!");
	SFN_CLIENT_INFO("Other Log!");

	auto app = Sophon::CreateApplication();
	app->Run();
	delete app;
}

#else
#error Sophon only supports Windows!
#endif