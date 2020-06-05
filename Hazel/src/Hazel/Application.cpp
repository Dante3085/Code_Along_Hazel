#include "hzpch.h"
#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"

#include <GLFW/glfw3.h>

namespace Hazel
{
	Application::Application()
	{
		m_window = std::unique_ptr<Window>(Window::create());
	}

	Application::~Application()
	{
	}

	void Application::run() 
	{
		while (m_running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->onUpdate();
		}
	}
}