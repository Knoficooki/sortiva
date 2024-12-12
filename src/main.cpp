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

#include "gui/ComponentStack.hpp"
#include "gui/CoreComponents.hpp"

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
	std::cout << "Darling, I'm Home!\n";

	sva::Logging logerr = sva::Logging(std::cerr);
	logerr.levelName(logerr_level::Debug) = "Debug";
	logerr.levelName(logerr_level::Window) = "Window";
	logerr.levelName(logerr_level::SVA) = "SVA";

	logerr(logerr_level::Debug);

	/* Window and rendering */

	InitWindow(window_width, window_height, window_title);

	if (!IsWindowReady())
	{
		logerr(logerr_level::Window).logln("Window could not be created...");
		return 0;
	}

	ClearWindowState(ConfigFlags::FLAG_WINDOW_RESIZABLE | ConfigFlags::FLAG_WINDOW_TRANSPARENT);
	SetWindowState(ConfigFlags::FLAG_WINDOW_ALWAYS_RUN);

	SetWindowFocused();


	bool m_Running = true;
	ComponentStack::s_WndRunning = &m_Running;

	ComponentStack::s_WndWidth = GetRenderWidth();
	ComponentStack::s_WndHeight = GetRenderHeight();

	int run_result = 0;

	ComponentStack::push<SettingsComponent>();

	// always on top...
	SafeClosePopup safe_close_popup;
	safe_close_popup.attach(&m_Running);
	safe_close_popup.wndrsize(ComponentStack::s_WndWidth, ComponentStack::s_WndHeight);


	while (m_Running) {


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
		logerr(logerr_level::SVA).logln("Program exiting abnormally.");
		break;
	default:
		break;
	}

	return 0;
}