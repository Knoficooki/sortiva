#pragma once

#define SHOW(variable) std::cout << #variable << " = " << (variable) << std::endl;

#ifdef _DEBUG
	#define DEBUG
	#define ASSERT(condition, message) while(!(condition)) { std::cerr << "Assertion failed: " << #condition << "\n\t" << (message); exit(1); }
	#define FATAL_ASSERT(condition, message) ASSERT(condition, message)
#else
	#define RELEASE
	#define FATAL_ASSERT(condition, message) ASSERT(condition, message) exit(1);
	#define ASSERT(condition, message) if(!(condition)) { std::cerr << "Assertion failed: " << #condition << "\nIn File: " << __FILE__ << "\nOn line: " << __LINE__ << "\n\t" << (message); }
#endif

#include "types.hpp"
#include "list.hpp"
#include "flagman.hpp"

#ifdef DEBUG
#include "Profiling/Timer.hpp"

#endif
