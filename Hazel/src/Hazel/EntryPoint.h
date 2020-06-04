#pragma once

#ifdef HZ_PLATFORM_WINDOWS

// Says that the implementation for Hazel::createApplication() will be in a different file.
extern Hazel::Application* Hazel::createApplication();

int main(int argc, char** argv)
{
	Hazel::Log::init();

	HZ_CORE_WARN("Initialized Log!");
	int a = 5;
	HZ_INFO("Hello Var={0}", a);

	auto app = Hazel::createApplication();
	app->run();
	delete app;
}

#endif