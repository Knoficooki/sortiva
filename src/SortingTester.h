#pragma once
#define SVA_LIST_CALLBACKS
#include <std.hpp>

#include <functional>
#include "lua/safesol.h"
#include <iostream>


class SortingTester
{
	List<u64> list;
	
	safesol lua;

	Timer timer = Timer(Timer::State::paused);

	using populate_function = std::function<void(size_t, u64&)>;

	template<typename ...Args>
	sol::protected_function_result run_function(const sol::protected_function& function, Args&&... args)
	{
		timer.set_state(Timer::State::running);
		sol::protected_function_result result = function(std::forward<Args>(args)...);
		timer.set_state(Timer::State::paused);
		return result;
	}


	bool list_greater(size_t index1, size_t index2)
	{
		if (active_result)
			++active_result->count_greater;
		return list[index1] > list[index2];
	}

	bool list_less(size_t index1, size_t index2)
	{
		if (active_result)
			++active_result->count_less;
		return list[index1] < list[index2];
	}

	bool list_equal(size_t index1, size_t index2)
	{
		if (active_result)
			++active_result->count_equal;
		return list[index1] == list[index2];
	}
	
	void list_swap(size_t index1, size_t index2)
	{
		if (active_result)
			++active_result->count_swaps;
		// list[index1] ^= list[index2];
		// list[index2] ^= list[index1];
		// list[index1] ^= list[index2];
		auto tmp = list[index1];
		list[index1] = list[index2];
		list[index2] = tmp;
	}

	size_t list_size() const
	{
		return list.size();
	}

	bool is_sorted()
	{
		if (list.size() <= 1)
			return true;
		for (size_t i = 1; i < list.size(); i++)
		{
			if (list[i - 1] > list[i])
				return false;
		}
		return true;
	}

	
	
public:
	struct run_result
	{
		timer_result timer;
		// counts
		u64 count_swaps = 0;
		u64 count_greater = 0;
		u64 count_less = 0;
		u64 count_equal = 0;
		// counts for comparisons
		u64 count_comparisons = 0;
	};
private:
	run_result* active_result = nullptr;
	
public:
	
	SortingTester();

	void load(const std::string& script);
	void load_internal();
	
	template<typename ...Args>
	run_result run(const std::string& function_name, Args&&... args)
	{
		run_result result;
		timer.result.emplace(&result.timer);
		timer.reset(Timer::State::paused);
		active_result = &result;
		
		// Create a bound member function using std::bind
		auto bound_run_function = std::bind(&SortingTester::run_function<Args...>, 
										  this, 
										  std::placeholders::_1,
										  std::forward<Args>(args)...);
		
		safesol::LuaResultType runstate = lua.run_on_caller(function_name, bound_run_function);
		
		if (runstate != safesol::LuaResultType::SUCCESS)
		{
			std::cerr << "Error running function \"" << function_name << "\": " << static_cast<u16>(runstate) << std::endl;
			exit(static_cast<int>(runstate));
		}
		
		if (!is_sorted())
		{
			std::cerr << "[ERROR] The algorithm \"" << function_name << "\" did not sort the list" << std::endl;
			std::cerr << "[List] [ ";
			for (size_t i = 0; i < list.size(); i++)
			{
				if(i == list.size()-1)
				{
					std::cerr << list[i] << " ]";
					continue;
				}
				std::cerr << list[i] << ", ";
			}
			std::flush(std::cerr);
			std::terminate();
		}

		std::cout << "[sorted: List(" << list.size() << ")] [ ";
		for (size_t i = 0; i < list.size(); i++)
		{
			if(i == list.size()-1)
			{
				std::cout << list[i] << " ]\n";
				break;
			}
			std::cout << list[i] << ", ";
		}
		std::flush(std::cout);

		result.count_comparisons = result.count_equal + result.count_greater + result.count_less;

		active_result = nullptr;
		return result;
	}

	
	
	void populate(const populate_function& f);
};
