#pragma once
#include <iostream>
#include <vector>

inline const char* ASCII_TITLE = R"(
	 __                  
	(_  _  ___|_ o     _ 
	__)(_) |  |_ | \_/(_|



)";

inline void sva_console_init()
{
	std::cout << ASCII_TITLE;
}