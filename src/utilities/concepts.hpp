#pragma once
#include <concepts>
#include <type_traits>
#include <iterator>

template<typename T>
	concept numericType = 
	std::is_arithmetic<T>::value &&
	std::regular<T> && //? Incrementable already includes regular that means is copyable, has default_constructor & operand ==
	// std::incrementable<T> &&
	requires (T a, T b)
	{
		{ a<=>b };
	};
