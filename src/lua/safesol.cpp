#include "safesol.h"

safesol::LuaResultType safesol::script(const std::string& script)
{
	sol::load_result result = lua.load(script);
	if (!result.valid()) {
		sol::error err = result;
		std::cout << "Error loading script: " << err.what() << std::endl;
		return LuaResultType::LOAD_ERROR;
	}

	sol::protected_function_result script_result = result();

	if (!script_result.valid()) {
		sol::error err = script_result;
		std::cout << "Error running script: " << err.what() << std::endl;
		return LuaResultType::SCRIPT_ERROR;
	}

	return LuaResultType::SUCCESS;
}

safesol::LuaResultType safesol::script(const char* script)
{
	sol::load_result result = lua.load(script);
	if (!result.valid()) {
		sol::error err = result;
		std::cout << "Error loading script: " << err.what() << std::endl;
		return LuaResultType::LOAD_ERROR;
	}

	sol::protected_function_result script_result = result();

	if (!script_result.valid()) {
		sol::error err = script_result;
		std::cout << "Error running script: " << err.what() << std::endl;
		return LuaResultType::SCRIPT_ERROR;
	}

	return LuaResultType::SUCCESS;
}

safesol::LuaResultType safesol::load(const std::string& file)
{
	sol::load_result result = lua.load_file(file);
	if (!result.valid()) {
		sol::error err = result;
		std::cout << "Error loading file: " << err.what() << std::endl;
		return LuaResultType::LOAD_ERROR;
	}

	sol::protected_function_result script_result = result();

	if (!script_result.valid()) {
		sol::error err = script_result;
		std::cout << "Error running script: " << err.what() << std::endl;
		return LuaResultType::SCRIPT_ERROR;
	}

	return LuaResultType::SUCCESS;
}
