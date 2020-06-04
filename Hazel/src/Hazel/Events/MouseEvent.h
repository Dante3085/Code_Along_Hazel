#pragma once

#include "Event.h"

namespace Hazel
{
	class HAZEL_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_mouseX(x), m_mouseY(y)
		{

		}

		inline float getX() const { return m_mouseX; }
		inline float getY() const { return m_mouseY; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(HZ_MOUSE_MOVED)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT) // Does ist for both ? Don't really understand the bitwise OR here.

	private:
		float m_mouseX, m_mouseY;
	};

	class HAZEL_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			:m_xOffset(xOffset), m_yOffset(yOffset)
		{

		}

		inline float getXOffset() const { return m_xOffset; }
		inline float getYOffset() const { return m_yOffset; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_xOffset << ", " << m_yOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSE_SCROLLED)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT)

	private:
		float m_xOffset, m_yOffset;
	};

	class HAZEL_API MouseButtonEvent : public Event
	{
	public:
		inline int getMouseButton() const { return m_button; }

		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT)

	protected:
		MouseButtonEvent(int button)
			: m_button(button)
		{

		}

		int m_button;
	};

	class HAZEL_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button)
		{

		}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSE_BUTTON_PRESSED)
	};

	class HAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button)
		{

		}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSE_BUTTON_RELEASED)
	};
}