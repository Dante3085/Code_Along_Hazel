#include "hzpch.h"
#include "WindowsWindow.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

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
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
		{
			WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);
			windowData->width = width;
			windowData->height = height;

			WindowResizeEvent resizeEvent(width, height);
			windowData->eventCallback(resizeEvent);
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);
			
			WindowCloseEvent closeEvent;
			windowData->eventCallback(closeEvent);


		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int keyboardKey, int scancode, 
			                            int keyAction, int modifierBitfield)
		{
			WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);

			switch (keyAction)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent keyPressedEvent(keyboardKey, 0);
					windowData->eventCallback(keyPressedEvent);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent keyReleasedEvent(keyboardKey);
					windowData->eventCallback(keyReleasedEvent);
					break;
				}
				case GLFW_REPEAT:
				{
					// TODO: Extract exact repeat count in future.
					KeyPressedEvent keyPressedEvent(keyboardKey, 1);
					windowData->eventCallback(keyPressedEvent);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int mouseButton, int action, 
			                                    int modifierBitfield)
		{
			WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);
			
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent mouseButtonPressedEvent(mouseButton);
					windowData->eventCallback(mouseButtonPressedEvent);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent mouseButtonReleasedEvent(mouseButton);
					windowData->eventCallback(mouseButtonReleasedEvent);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent mouseScrolledEvent((float)xOffset, (float)yOffset);
			windowData->eventCallback(mouseScrolledEvent);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent mouseMovedEvent((float)xPos, (float)yPos);
			windowData->eventCallback(mouseMovedEvent);
		});
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(m_window);
	}

}