#pragma once
#include "GuiComponent.hpp"
#include <raylibs/raygui.h>
#include <string>


class GuiMovableWindow : public sva::GuiComponent
{
private:
	bool m_DragWindow = false;
	Vector2 m_PanOffset = { 0,0 };
protected:
	Rectangle m_WndRect = { 20,20, 200, 100 };
	bool m_WindowOpen = true;
public:

	virtual int input() override
	{
		if (!m_WindowOpen) return 0;
		Vector2 mouse_pos = GetMousePosition();

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !m_DragWindow)
		{
			if (CheckCollisionPointRec(mouse_pos, { m_WndRect.x, m_WndRect.y, m_WndRect.width - 24, 20 }))
			{
				m_DragWindow = true;
				m_PanOffset = { mouse_pos.x - m_WndRect.x, mouse_pos.y - m_WndRect.y };
			}
		}

		if (m_DragWindow)
		{
			m_WndRect.x = (mouse_pos.x - m_PanOffset.x);
			m_WndRect.y = (mouse_pos.y - m_PanOffset.y);
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) m_DragWindow = false;
		}
		return rinput(mouse_pos);
	}

	virtual int rinput(Vector2& mouse_position) { return 0; };

	virtual int draw() override
	{
		if (!m_WindowOpen) return 0;

		m_WindowOpen = !GuiWindowBox(m_WndRect, "Example Movable Window");

		return 0;
	}
};

class SafeClosePopup final : public GuiMovableWindow
{
	Vector2 anchor03 = { 0,0 };

	bool m_CQB_YesButton = false;
	bool m_CQB_NoButton = false;
public:
	void onAttach() override
	{
		m_WindowOpen = false;
	}

	int draw() override
	{
		if (WindowShouldClose())
		{
			m_WindowOpen = !m_WindowOpen;
			onResize();
		}

		if (m_WindowOpen)
		{
			anchor03 = { m_WndRect.x + 168, m_WndRect.y + 88 };

			m_WindowOpen = !GuiWindowBox(m_WndRect, "#191# Are you sure you want to close this program?");
			m_CQB_YesButton = GuiButton({ anchor03.x + -152, anchor03.y + 32, 120, 24 }, "#112#Yes");
			m_CQB_NoButton = GuiButton({ anchor03.x + 24, anchor03.y + 32, 120, 24 }, "#113#No");
			GuiLabel({ anchor03.x + -104, anchor03.y + -40, 208, 24 }, "Are you sure you want to close this?");
			GuiLabel({ anchor03.x + -56, anchor03.y + -8, 120, 24 }, "Press \"Yes\" to close");
			if (m_CQB_YesButton)
			{
				*m_WndRunning = false;
				return 1;
			}
			if (m_CQB_NoButton) m_WindowOpen = false;

		}
		return 0;
	}

	int rinput(Vector2& mouse_position) override
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !CheckCollisionPointRec(mouse_position, m_WndRect))
		{
			SetMousePosition(anchor03.x, anchor03.y);
		}
		return 0;
	}


	void onResize() override
	{
		anchor03 = { static_cast<float>(m_WndWidth) / 2 , static_cast<float>(m_WndHeight) / 2 };
		m_WndRect = { anchor03.x + -168, anchor03.y + -88, 328, 160 };
	}
};

class SettingsComponent final : public sva::GuiComponent
{
	Vector2 anchor01 = { 0,0 };

	int ActiveMonitorID = 0;

	std::string m_ScreenListString;

public:
	void onAttach() override
	{
		for (int i = 0; i < GetMonitorCount(); ++i)
		{
			m_ScreenListString += GetMonitorName(i);
			m_ScreenListString += ";";
		}
		m_ScreenListString.pop_back();

		fitWindowToMonitor();
	}

	void onResize() override
	{
		anchor01 = { static_cast<float>(m_WndWidth) / 4, static_cast<float>(m_WndHeight) / 4 };
	}

	int draw() override
	{
		if (GetCurrentMonitor() != ActiveMonitorID)
		{
			fitWindowToMonitor(ActiveMonitorID);
			m_ScreenListString.clear();
			for (int i = 0; i < GetMonitorCount(); ++i)
			{
				m_ScreenListString += GetMonitorName(i);
				m_ScreenListString += ";";
			}
			m_ScreenListString.pop_back();
		}

		GuiGroupBox({ anchor01.x + 0, anchor01.y + 0, 264, 104 }, "Settings");
		GuiLabel({ anchor01.x + 16, anchor01.y + 24, 72, 24 }, "#181#Screen:");
		GuiComboBox({ anchor01.x + 88, anchor01.y + 24, 160, 24 }, m_ScreenListString.c_str(), &ActiveMonitorID);
		return 0;
	}

private:
	static void fitWindowToMonitor(int monitor = 0)
	{
		if (GetMonitorCount() < monitor) return;
		int width = GetMonitorHeight(monitor);
		int height = GetMonitorHeight(monitor);
		SetWindowMonitor(monitor);
		SetWindowSize(width, height);

		int refresh_rate = GetMonitorRefreshRate(monitor);
		SetTargetFPS(refresh_rate);
		ToggleBorderlessWindowed();
	}
};
