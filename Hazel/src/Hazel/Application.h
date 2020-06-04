#pragma once

#include "Core.h"
#include "Events/Event.h" // Causes errors when compiling Sandbox
#include "Window.h"

namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

	private:
		std::unique_ptr<Window> m_window;
		bool m_running = true;
	};

	// Will be defined in Client.
	Application* createApplication();
}
