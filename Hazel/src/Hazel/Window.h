#pragma once

#include "hzpch.h"

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel
{
	struct WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(std::string const& title = "Hazel Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: title(title), width(width), height(height)
		{

		}
	};

	// Platform independent.
	// Abstract representation of a Window.
	// Interface representing a desktop system based Window.
	// Interface because no data and no implemented functions. Just pure virtual functions.
	class HAZEL_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		// Window attributes
		virtual void setEventCallback(EventCallbackFn const& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		// Has to be implemented per platform.
		static Window* create(WindowProps const& props = WindowProps());
	};
}