#pragma once
#include <chrono>
#include <iostream>
#include <optional>
#include <assert.h>

struct timer_result
{
	double seconds = 0;
	double difftime = 0;
};

struct Timer {
	enum State : u8
	{
		running = 0,
		paused = 1
	};
	State state = paused;
	
	std::clock_t begin;
	std::clock_t elapsed = 0;
	std::optional<std::ostream*> out;
	std::optional<timer_result*> result;
	
	Timer() : begin(std::clock()) {}
	Timer(std::ostream& o) : begin(std::clock()), out(&o) {}
	Timer(timer_result& r) : begin(std::clock()), result(&r) {}
	Timer(std::ostream& o, timer_result& r) : begin(std::clock()), out(&o), result(&r) {}
	Timer(State initial_state) : state(initial_state), begin(std::clock())
	{
		if (state == paused)
			begin = 0;
	}

	Timer(std::ostream& o, State initial_state) : state(initial_state), begin(std::clock()), out(&o)
	{
		if (state == paused)
			begin = 0;
	}
	Timer(timer_result& r, State initial_state) : state(initial_state), begin(std::clock()), result(&r)
	{
		if (state == paused)
			begin = 0;
	}
	
	Timer(std::ostream& o, timer_result& r, State initial_state) : state(initial_state), begin(std::clock()), out(&o), result(&r)
	{
		if (state == paused)
			begin = 0;
	}

	void reset(State init_state) {
		if (state == paused)
			begin = 0;
		else
			begin = std::clock();
		elapsed = 0;
		state = init_state;
		lap();
	}

	void set_state(State new_state)
	{
		if (this->state == new_state)
			return;

		if (new_state == running)
		{
			begin = std::clock();
		}
		else // pausing
		{
			assert(begin != 0);
			elapsed += std::clock() - begin;
			begin = 0;
		}

		lap();
		this->state = new_state;
	}

	void lap()
	{
		std::clock_t total_time = elapsed;
		if (state == running)
		{
			total_time += std::clock() - begin;
		}

		if (result)
		{
			result.value()->seconds = static_cast<double>(total_time) / CLOCKS_PER_SEC;
			result.value()->difftime = static_cast<double>(total_time) / CLOCKS_PER_SEC;
		}
		if (out)
		{
			*out.value() << static_cast<double>(total_time) / CLOCKS_PER_SEC << " seconds.\n";
			*out.value() << "Total time = " << static_cast<double>(total_time) / CLOCKS_PER_SEC << std::endl;
		}
	}
	
	~Timer() {
		lap();
	}
};