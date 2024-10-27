#pragma once

#include <cstdint>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

template<typename T>
struct TVector2
{
	using type = T;
	T x, y;
	template<typename G>
	constexpr TVector2(G _x, G _y) {
		x = static_cast<T>(_x);
		y = static_cast<T>(_y);
	}
	constexpr TVector2(T _x, T _y) {
		x = _x;
		y = _y;
	}
	constexpr TVector2() {
		x = 0;
		y = 0;
	}
};

typedef TVector2<float> vec2f;
typedef TVector2<double> vec2d;
typedef TVector2<uintmax_t> vec2u;
typedef TVector2<intmax_t> vec2i;

template<typename T>
constexpr T min(T a, T b)
{
	return a < b ? a : b;
}

template<typename T>
constexpr T max(T a, T b)
{
	return a > b ? a : b;
}

template<typename T>
struct TRect
{
	using type = T;
	T x, y, width, height;

	template<typename G>
	constexpr TRect(
			G _x, G _y,
			G _width, G _height )
		: x(static_cast<T>(_x)), y(static_cast<T>(_y)),
		width(static_cast<T>(_width)), height(static_cast<T>(_height))
	{}

	constexpr TRect(
		T _x, T _y,
		T _width, T _height)
		: x(_x), y(_y),
		width(_width), height(_height)
	{}

	constexpr TRect()
		: x(0), y(0),
		width(0), height(0)
	{}
};

typedef TRect<float> rectf;
typedef TRect<double> rectd;
typedef TRect<uintmax_t> rectu;
typedef TRect<intmax_t> recti;

