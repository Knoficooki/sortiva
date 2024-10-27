#include "drawing_helper.hpp"

namespace sva
{
	std::vector<std::string> split(const std::string& str, char delim)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(str);
		while (std::getline(tokenStream, token, delim))
		{
			tokens.push_back(token);
		}
		return tokens;
	}
}


Color sva::GetThemeColor(GuiControlProperty property)
{
	return GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL));
}

void sva::DrawText(const std::string& text, vec2i pos, int size, Color color, TEXT_ALIGNMENT alignment)
{
	switch (alignment)
	{
	case TEXT_ALIGN_LEFT:
		return DrawText(text.c_str(), pos.x, pos.y, size, color);
	case TEXT_ALIGN_RIGHT:
		if (text.find('\n') != std::string::npos)
		{
			std::vector<std::string> lines = split(text, '\n');
			for (auto& line : lines)
			{
				pos.x -= MeasureText(line.c_str(), size);
				DrawText(line.c_str(), pos.x, pos.y, size, color);
				pos.y += size;
			}
			return;
		}
		pos.x -= MeasureText(text.c_str(), size);
		return DrawText(text.c_str(), pos.x, pos.y, size, color);
		
	case TEXT_ALIGN_CENTER:
		if (text.find('\n') != std::string::npos)
		{
			std::vector<std::string> lines = sva::split(text, '\n');
			for (auto& line : lines)
			{
				pos.x -= MeasureText(line.c_str(), size) / 2;
				DrawText(line.c_str(), pos.x, pos.y, size, color);
				pos.y += size;
			}
			return;
		}
		pos.x -= MeasureText(text.c_str(), size) / 2;
		DrawText(text.c_str(), pos.x, pos.y, size, color);
	}
}
