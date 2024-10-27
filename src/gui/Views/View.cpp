#include "View.h"
#include <raylibs/raygui.h>

void View::draw()
{
	BeginDrawing();
	ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
	EndDrawing();
}

void View::update()
{
}
