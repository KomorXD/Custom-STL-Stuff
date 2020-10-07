#pragma once

#include "Allocator.hpp"

namespace nstd {

	// Returns an address of an obj even if the operator& is overloaded
	template<typename T>
	T* addressof(const T& obj) {
		return reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(obj)));
	}
}