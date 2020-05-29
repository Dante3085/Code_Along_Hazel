#pragma once

#include "Core.h"

namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Will be defined in Client.
	Application* CreateApplication();
}
