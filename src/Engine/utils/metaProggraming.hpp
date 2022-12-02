#pragma once

namespace MP
{

	template<typename T, typename tuple>
	struct has_type;

	template<typename T>
	struct has_type<T, std::tuple<>> : std::false_type {};

	template<typename T, typename U, typename... args >
	struct has_type<T, std::tuple<U, args...>> : has_type< T, std::tuple<args...> > {};

	template<typename T, typename... args>
	struct has_type<T, std::tuple<T, args...>> : std::true_type {};

	template <typename T>
	struct Class
	{
		using type = T; 
	};

}
