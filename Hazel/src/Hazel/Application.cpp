#include "hzpch.h"

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
		
		if (e.isInCategory(EventCategory::EVENT_CATEGORY_APPLICATION))
		{
			HZ_CORE_ERROR("Is in EventCategoryApplication");
		}
		if (e.isInCategory(EventCategory::EVENT_CATEGORY_INPUT))
		{
			HZ_CORE_ERROR("Is in EventCategoryInput");
		}

		while (true);
	}
}