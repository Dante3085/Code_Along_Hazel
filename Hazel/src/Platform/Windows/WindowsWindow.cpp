#include "hzpch.h"
#include "WindowsWindow.h"

namespace Hazel
{
	static bool s_GLFWInitialized = false;

	Window* Window::create(WindowProps const& props)
	{
		return new WindowsWindow(props);
	}


	WindowsWindow::WindowsWindow(WindowProps const& props)
	{
		init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		shutdown();
	}

	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WindowsWindow::setVSync(bool enabled)
	{
		enabled ? glfwSwapInterval(1) : glfwSwapInterval(0);
		m_data.vSynch = enabled;
	}

	bool WindowsWindow::isVSync() const
	{
		return m_data.vSynch;
	}

	void WindowsWindow::init(WindowProps const& props)
	{
		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

		HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(m_window);
	}

}