#include "SortingTester.h"


SortingTester::SortingTester() : list(10)
{
	std::cout << "Loading lua" << std::endl;

	lua.lua.open_libraries(sol::lib::coroutine, sol::lib::table);
	lua.lua.new_usertype<SortingTester>("List",
		"size", &SortingTester::list_size,
		"swap", &SortingTester::list_swap,
		"greater", &SortingTester::list_greater,
		"less", &SortingTester::list_less,
		"equal", &SortingTester::list_equal
	);

	lua.lua["list"] = this;
}

void SortingTester::load(const std::string& script)
{
	if(lua.load(script) != safesol::LuaResultType::SUCCESS)
	{
		std::cerr << "Error loading file" << std::endl;
		std::terminate();
	}
}

#include "internal_script.hpp"

void SortingTester::load_internal()
{
	if (lua.script(std_intern_sorting_script) != safesol::LuaResultType::SUCCESS)
	{
		std::cerr << "Error loading internal script" << std::endl;
		std::terminate();
	}
}

void SortingTester::populate(const populate_function& f)
{
	std::cout << "[List(" << list.size() << ")] [ ";
	for (size_t i = 0; i < list.size(); i++)
	{
		f(i, list[i]);
		if(i == list.size()-1)
		{
			std::cout << list[i] << " ]\n";
			break;
		}
		std::cout << list[i] << ", ";
	}
	std::flush(std::cout);
}
