#pragma once

#include "Hazel/Core.h"

#include <string>
#include <functional>

namespace Hazel
{
	// Events in Hazel are currently blocking, which means that they
	// need to be immediately dealt with.
	// A better strategy for the future might be to buffer events and 
	// deal with them during the event part of the update stage.

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication   = BIT(0),
		EventCategoryInput         = BIT(1),
		EventCategoryKeyboard      = BIT(2),
		EventCategoryMouse         = BIT(3),
		EventCategoryMouseButton   = BIT(4)
	};

	class HAZEL_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_Handled = false;
	};
}