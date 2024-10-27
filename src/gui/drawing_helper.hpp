#pragma once
#include <raylib.h>
#include <raylibs/raygui.h>
#include <string>
#include <vector>
#include <sstream>

namespace sva
{
	template<typename T>
	struct TVector2
	{
		T x, y;
	};
	typedef TVector2<int> vec2i;
	typedef TVector2<float> vec2f;
	
	enum TEXT_ALIGNMENT
	{
		TEXT_ALIGN_LEFT,
		TEXT_ALIGN_CENTER,
		TEXT_ALIGN_RIGHT
	};


	Color GetThemeColor(GuiControlProperty property);
	
	void DrawText(const std::string& text, vec2i pos, int size, Color color = GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL)), TEXT_ALIGNMENT alignment = TEXT_ALIGN_LEFT);
}