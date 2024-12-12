/**************************************************************
 * 		Sortiva - Sorting Visualisation Tool
 *
 * This project falls under the MIT Licence.
 * But I would find it very nice of you,
 * if you could add my name and the project
 * to some kind of credits.
 * Thank you.
 *
 * Kind regards,
 * Jann Hoffmann.
 *
 * Signature: "Darling, I'm Home!" -  Jann Hoffmann
**************************************************************/

#include <iostream>

// sva logger
#include <logger.hpp>

/* raylib includes */
#include <raylib.h>
#include <raylibs/raygui.h>

constexpr int window_width = 800;
constexpr int window_height = 650;
constexpr char window_title[] = "Sortiva";


enum class logerr_level
{
	Debug = 0,
	Window,
	SVA,
};

void fitWindowToMonitor(int monitor = 0)
{
	if (GetMonitorCount() < monitor) return;
	int width = GetMonitorHeight(monitor);
	int height = GetMonitorHeight(monitor);
	SetWindowMonitor(monitor);
	SetWindowSize(width, height);

	int refresh_rate = GetMonitorRefreshRate(monitor);
	SetTargetFPS(refresh_rate);
}


int main(void)
{
	std::cout << "Darling, I'm Home!\n";

	sva::Logging logerr = sva::Logging(std::cerr);
	logerr.levelName(logerr_level::Debug) = "Debug";
	logerr.levelName(logerr_level::Window) = "Window";
	logerr.levelName(logerr_level::SVA) = "SVA";

	logerr(logerr_level::Debug);

	/* Window and rendering */

	InitWindow(window_width, window_height, window_title);

	fitWindowToMonitor();

	if (!IsWindowReady())
	{
		logerr(logerr_level::Window).logln("Window could not be created...");
		return 0;
	}

	ClearWindowState(ConfigFlags::FLAG_WINDOW_RESIZABLE | ConfigFlags::FLAG_WINDOW_TRANSPARENT);
	SetWindowState(ConfigFlags::FLAG_WINDOW_ALWAYS_RUN | ConfigFlags::FLAG_BORDERLESS_WINDOWED_MODE);

	SetWindowFocused();


	bool m_Running = true;

	int wnd_width = GetRenderWidth();
	int wnd_height = GetRenderHeight();

	Vector2 anchor03 = { static_cast<float>(wnd_width) / 2 , static_cast<float>(wnd_height) / 2 };

	bool CloseQuestionBoxActive = false;
	bool CQB_YesButton = false;
	bool CQB_NoButton = false;

	while (m_Running) {
		if (IsWindowResized())
		{
			wnd_width = GetRenderWidth();
			wnd_height = GetRenderHeight();
			anchor03 = { static_cast<float>(wnd_width) / 2 , static_cast<float>(wnd_height) / 2 };
		}

		if (WindowShouldClose()) CloseQuestionBoxActive = !CloseQuestionBoxActive;

		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

		if (CloseQuestionBoxActive)
		{
			CloseQuestionBoxActive = !GuiWindowBox({ anchor03.x + -168, anchor03.y + -88, 328, 160 }, "#191# Are you sure you want to close this program?");
			CQB_YesButton = GuiButton({ anchor03.x + -152, anchor03.y + 32, 120, 24 }, "Yes");
			CQB_NoButton = GuiButton({ anchor03.x + 24, anchor03.y + 32, 120, 24 }, "No");
			GuiLabel({ anchor03.x + -104, anchor03.y + -40, 208, 24 }, "Are you sure you want to close this?");
			GuiLabel({ anchor03.x + -56, anchor03.y + -8, 120, 24 }, "Press \"Yes\" to close");
			if (CQB_YesButton)
			{
				m_Running = false;
				break;
			}
			if (CQB_NoButton) CloseQuestionBoxActive = false;
		}

		EndDrawing();

	}

	CloseWindow();

	return 0;
}