#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"

namespace Hazel
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		
		if (e.IsInCategory(EventCategory::EventCategoryApplication))
		{
			HZ_CORE_ERROR("Is in EventCategoryApplication");
		}
		if (e.IsInCategory(EventCategory::EventCategoryInput))
		{
			HZ_CORE_ERROR("Is in EventCategoryInput");
		}

		while (true);
	}
}