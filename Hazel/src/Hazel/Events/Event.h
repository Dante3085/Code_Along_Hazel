#pragma once

#include "Hazel/Core.h"

namespace Hazel
{
	// Events in Hazel are currently blocking, which means that they
	// need to be immediately dealt with.
	// A better strategy for the future might be to buffer events and 
	// deal with them during the event part of the update stage.

	enum class EventType
	{
		// I need to define HZ_MOUSE_MOVED instead of MOUSE_MOVED because MOUSE_MOVED
		// name-clashes with a #define in wincontypes.h

		NONE = 0,
		WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_LOST_FOCUS, WINDOW_MOVED,
		APP_TICK, APP_UPDATE, APP_RENDER,
		KEY_PRESSED, KEY_RELEASED,
		MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, HZ_MOUSE_MOVED, MOUSE_SCROLLED
	};

	enum EventCategory
	{
		NONE = 0,
		EVENT_CATEGORY_APPLICATION   = BIT(0),
		EVENT_CATEGORY_INPUT         = BIT(1),
		EVENT_CATEGORY_KEYBOARD      = BIT(2),
		EVENT_CATEGORY_MOUSE         = BIT(3),
		EVENT_CATEGORY_MOUSE_BUTTON   = BIT(4)
	};

// ##variable concatenates variable's value with the text left of it.
// #variable puts string quotes around variable's value.
#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::##type; }\
                               virtual EventType getEventType() const override { return getStaticType(); }\
                               virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class HAZEL_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(EventCategory category)
		{
			return getCategoryFlags() & category;
		}

	protected:
		bool m_handled = false;
	};

	class EventDispatcher
	{
		template <typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_event(event)
		{

		}

		template <typename T>
		bool dispatch(EventFn<T> func)
		{
			if (m_event.getEventType() == T::getStaticType())
			{
				m_event.m_handled = func(*(T*)&m_event);
				return true;
			}
			return false;
		}

	private:
		Event& m_event;
	};

	inline std::ostream& operator<<(std::ostream& os, Event const& e)
	{
		return os << e.toString();
	}
}