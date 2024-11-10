#pragma once
#include <std.hpp>
#include <sol/sol.hpp>

class safesol
{
public:
	enum class LuaResultType : u8
	{
		SUCCESS = 0,
		LOAD_ERROR = 1,
		SCRIPT_ERROR,
		RUN_ERROR,
		UNKNOWN_ERROR
	};
	
	sol::state lua;

	
	LuaResultType script(const std::string& script);
	LuaResultType script(const char* script);
	
	LuaResultType load(const std::string& file);

	template<typename ...Args>
	sol::protected_function_result default_caller(const sol::protected_function& function, Args&&... args)
	{
		return function(std::forward<Args>(args)...);
	}

	template<typename ...Args>
	LuaResultType run(const std::string& function_name, Args&&... args)
	{
		return run_on_caller(function_name, default_caller, std::forward<Args>(args)...);
	}

	template<typename ...Args, typename Caller = std::function<sol::protected_function_result(const sol::protected_function&, Args&&...)>>
	LuaResultType run_on_caller(const std::string& function_name, const Caller& caller, Args&&... args)
	{
		std::cout << "Looking for function: " << function_name << std::endl;
		
		auto function = lua[function_name];
		if (!function.valid()) {
			std::cout << "Error: function " << function_name << " not found" << std::endl;
			return LuaResultType::RUN_ERROR;
		}

		std::cout << "Found function, attempting to run" << std::endl;
		
		auto result = caller(function, std::forward<Args>(args)...);
		if (!result.valid()) {
			sol::error err = result;
			std::cout << "Error running function " << function_name << ": " << err.what() << std::endl;
			return LuaResultType::RUN_ERROR;
		}

		return LuaResultType::SUCCESS;
	}
};
