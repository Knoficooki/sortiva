#pragma once
#include "types.hpp"

template <typename EnumType>
class FlagManager
{
	EnumType flags;
public:
	static constexpr size_t size = sizeof(EnumType) * 8;
	FlagManager(EnumType flags) : flags(flags) {}

	[[nodiscard]]
	bool get(EnumType flag) const { return (flags & flag) == flag; }
	void set(EnumType flag) { flags |= flag; }
	void clear(EnumType flag) { flags &= ~flag; }
	void toggle(EnumType flag) { flags ^= flag; }

	[[nodiscard]]
	bool any() const { return flags; }
	
	void set_all() { flags = EnumType(-1); }
	void clear_all() { flags = 0; }

	bool operator==(const FlagManager& other) const { return flags == other.flags; }
	bool operator!=(const FlagManager& other) const { return flags != other.flags; }

	// return true if every bit in *this is set in other
	bool of(FlagManager& other) const { return (flags & other.flags) == flags; }
	// return true if every bit in *this is set in other
	bool of(EnumType other) const { return (flags & other) == flags; }
};

template <typename EnumType>
using Flagman = FlagManager<EnumType>;
