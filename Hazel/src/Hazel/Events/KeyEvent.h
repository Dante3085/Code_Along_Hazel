#pragma once

#include "Event.h"

namespace Hazel
{
	class HAZEL_API KeyEvent : public Event
	{
	public:
		inline int getKeyCode() const { return m_keyCode; }

		EVENT_CLASS_CATEGORY( EVENT_CATEGORY_KEYBOARD | EVENT_CATEGORY_INPUT )

	protected:
		KeyEvent(int keycode)
			: m_keyCode(keycode)
		{

		}

		int m_keyCode;
	};

	class HAZEL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_repeatCount(repeatCount)
		{

		}

		inline int getRepeatCount() const { return m_repeatCount; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEY_PRESSED) // Macro just expands to implementation of virtual/pure virtual functions, because we are lazy.
	private:
		int m_repeatCount;
	};

	class HAZEL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode)
		{

		}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEY_RELEASED)
	};
}