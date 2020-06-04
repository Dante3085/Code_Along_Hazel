#pragma once

#include "Hazel/Window.h"

#include <GLFW/glfw3.h>

namespace Hazel
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(WindowProps const& props);
		virtual ~WindowsWindow();

		virtual void onUpdate() override;

		virtual unsigned int getWidth() const override { return m_data.width; }
		virtual unsigned int getHeight() const override { return m_data.height; }

		// Window attributes
		inline void setEventCallback(EventCallbackFn const& callback) override { m_data.eventCallback = callback; }
		void setVSync(bool enabled) override;
		bool isVSync() const override;

	private:
		virtual void init(WindowProps const& props);
		virtual void shutdown();

	private:
		GLFWwindow* m_window;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool vSynch;

			EventCallbackFn eventCallback;
		};

		WindowData m_data;
	};
}

