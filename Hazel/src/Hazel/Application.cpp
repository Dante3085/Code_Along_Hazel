#include "hzpch.h"
#include "Application.h"

#include "Hazel/Log.h"

#include <GLFW/glfw3.h>

namespace Hazel
{

// TODO: Why is there a this pointer in the #define context ?: 
/*
After precompiler substitutes the text it is inside the Application constructor, 
where this is a pointer to the current Application instance.
*/

// TODO: Why do we need this pointer here ?
/*
Because we create a callable thing with the onEvent member function of Application,
bind needs to explicitly be told on what instance to call that onEvent member function.
This is being done by passing it the this pointer.
In any other normal function call, the this pointer is the implicit first argument.
*/
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(BIND_EVENT_FN(onEvent));
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

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		HZ_CORE_TRACE("{0}", e);
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}
}