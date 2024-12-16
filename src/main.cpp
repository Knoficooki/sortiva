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


/* raylib includes */
#include <raylib.h>
#include <sol/debug.hpp>

#include "gui/ComponentStack.hpp"
#include "gui/CoreComponents.hpp"

#include <spdlog/spdlog.h>

constexpr int window_width = 800;
constexpr int window_height = 650;
constexpr char window_title[] = "Sortiva";


enum class logerr_level
{
	Debug = 0,
	Window,
	SVA,
};


int main(void)
{
#ifdef _DEBUG
	spdlog::set_level(spdlog::level::debug);
	spdlog::set_pattern("\n\t%^%v%$\n");
#endif
	spdlog::debug("Darling, I'm Home");
	spdlog::set_pattern("[%T %z] [%^%l%$] [thread %t] %v");

	/* Window and rendering */

	InitWindow(window_width, window_height, window_title);

	if (!IsWindowReady())
	{
		spdlog::critical("Window could not be created...");
		return 0;
	}

	ClearWindowState(ConfigFlags::FLAG_WINDOW_RESIZABLE | ConfigFlags::FLAG_WINDOW_TRANSPARENT);
	SetWindowState(ConfigFlags::FLAG_WINDOW_ALWAYS_RUN);

	SetWindowFocused();

	spdlog::debug("Window created successfully.");


	bool is_running = true;
	ComponentStack::s_WndRunning = &is_running;

	ComponentStack::s_WndWidth = GetRenderWidth();
	ComponentStack::s_WndHeight = GetRenderHeight();

	int run_result = 0;

	ComponentStack::push<SettingsComponent>();

	// always on top...
	SafeClosePopup safe_close_popup;
	safe_close_popup.attach(&is_running);
	safe_close_popup.wndrsize(ComponentStack::s_WndWidth, ComponentStack::s_WndHeight);


	while (is_running) {


		if (IsWindowResized())
		{
			ComponentStack::s_WndWidth = GetRenderWidth();
			ComponentStack::s_WndHeight = GetRenderHeight();

			safe_close_popup.wndrsize(ComponentStack::s_WndWidth, ComponentStack::s_WndHeight);
			ComponentStack::resize();
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);

		run_result = safe_close_popup.input();
		if (run_result != 0) break;

		run_result = ComponentStack::run();
		if (run_result != 0) break;

		run_result = safe_close_popup.draw();
		if (run_result != 0) break;

		EndDrawing();
	}


	CloseWindow();

	switch (run_result)
	{
	case 2:
		spdlog::warn("Program exiting abnormally.");
		break;
	default:
		break;
	}

	return 0;
}