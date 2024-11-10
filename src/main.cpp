#include <iostream>
#include <raylib.h>
#include <raylibs/raygui.h>
#include "sva.hpp"


#include "gui/drawing_helper.hpp"

#define RESOURCES_PATH "G:/School/Belegarbeit/sortiva/res/"

#define SETTINGS_PATH "./.config.cfg"

#define NO_GUI


#ifndef NO_GUI

int screenWidth = 1280;
int screenHeight = 720;

enum GAME_STATES
{
	SVA_STATE_TITLE,
	SVA_STATE_GAMEPLAY,
};

GAME_STATES gameState = SVA_STATE_TITLE;

void UpdateDrawFrame();			// Update and Draw one frame

#include "gui/themes/dark.h"
#include "gui/Views/ViewManager.h"
#endif
#include <filesystem>


#ifdef NO_GUI
#include "SortingTester.h"
#endif


#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<u64> dis(0, 10);

void populate(size_t index, u64& value)
{
	value = dis(gen);
}



int main(int argc, char** argv)
{
	sva_console_init();

#ifdef NO_GUI

	std::cout << "Sortiva - Sorting Algorithm Visualizer" << std::endl;
	std::cout << "No GUI mode" << std::endl;
	
	SortingTester tester;
	tester.populate( populate );

	tester.load_internal();

	SortingTester::run_result result = tester.run("bubble_sort");

	std::cout << "Time: " << result.timer.seconds << " seconds" << std::endl;
	std::cout << "Difftime: " << result.timer.difftime << std::endl;

	
	std::cout << "Count swaps: " << result.count_swaps << std::endl;
	std::cout << "Count comparisons: " << result.count_comparisons << std::endl;
	std::cout << "\tCount greater: " << result.count_greater << std::endl;
	std::cout << "\tCount less: " << result.count_less << std::endl;
	std::cout << "\tCount equal: " << result.count_equal << std::endl;

	std::cout << "\n\n";
	
	
	std::cout << "\nPress any key to exit..." << std::endl;
	getchar();
	return 0;
	
#endif
	
#ifndef NO_GUI
	if(!DirectoryExists(RESOURCES_PATH))
	{
		std::cerr << "Resources folder not found!" << std::endl;
		return -1;
	}
	

	InitWindow(screenWidth, screenHeight, "Sortiva - Sorting Algorithm Visualizer");

	SetWindowIcon(LoadImage(RESOURCES_PATH "/images/sva-logo.png"));

	SetWindowMinSize(screenWidth, screenHeight);
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetExitKey(0);
	
	SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	GuiLoadStyleDark();
	GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

	// Main game loop
	while (!WindowShouldClose())
	{
		if (IsWindowResized())
		{
			screenWidth = GetScreenWidth();
			screenHeight = GetScreenHeight();
		}
		UpdateDrawFrame();
	}
	CloseWindow();
#endif
	return 0;
}

#ifndef NO_GUI
//----------------------------------------------------------------------------------
// Render Functions
//----------------------------------------------------------------------------------

void RenderGameplayState();


Rectangle ButtonRects[] = {
	{50, 150, 150, 40},
	{50, 200, 150, 40},
	{50, 300, 150, 40},
};

void UpdateDrawFrame()
{
	BeginDrawing();

	ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

	switch (gameState)
	{
	case SVA_STATE_TITLE:
		sva::DrawText("Sortiva", {screenWidth/2, 20}, 100, sva::GetThemeColor(TEXT_COLOR_NORMAL), sva::TEXT_ALIGN_CENTER);
		
		if(GuiButton(ButtonRects[0], "Öffnen"))
		{
			gameState = SVA_STATE_GAMEPLAY;
		}
		if(GuiButton(ButtonRects[1], "Speichern"))
		{
			gameState = SVA_STATE_GAMEPLAY;
		}
		if(GuiButton(ButtonRects[2], "Schließen"))
		{
			CloseWindow();
			exit(0);
		}
		
		break;
	case SVA_STATE_GAMEPLAY:
		if(IsKeyPressed(KEY_ESCAPE))
		{
			gameState = SVA_STATE_TITLE;
		}
		RenderGameplayState();
		break;
	}
	EndDrawing();
}
#include <numbers>

#define PI_2 std::numbers::pi_v<float> / 2

#define sin3(x) pow((-cos(PI_2+ ##x)),3)

#include <cmath>

Vector2 heart_position = Vector2{static_cast<float>(screenWidth)/2, static_cast<float>(screenHeight)/2.5f};
Vector2 heart_function(float t, float scale)
{
	return Vector2{
		((16 * static_cast<float>(sin3(t))) * scale) + heart_position.x,
		((13 * cos(t) - 5 * cos(2*t) - 2 * cos(3*t) - cos(4*t)) * -scale) + heart_position.y
	};
}

#define STEPS 1000
#define STEP_SIZE 0.01f

void RenderGameplayState()
{
	for (int i = 0; i < STEPS; i++)
	{
		Vector2 pos = heart_function(static_cast<float>(i) * STEP_SIZE, 20);
		Vector2 pos2 = heart_function(static_cast<float>(i) * STEP_SIZE + STEP_SIZE, 20);
		DrawLine(
			pos.x,
			pos.y,
			pos2.x,
			pos2.y,
			GetColor(GuiGetStyle(DEFAULT, LINE_COLOR))
		);
		
	}
}

#endif