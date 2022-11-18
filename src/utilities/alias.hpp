#pragma once
#include <utilities/config.hpp>

template <typename T>
using Vector = std::vector<T>;

template <typename T>
using uniqPtr = std::unique_ptr<T>;

template <typename T, std::size_t V>
using Array = std::array<T, V>;

template <typename key, typename value>
using unorderMap = std::unordered_map<key,value>;

template <class T>
using Stack = std::stack<T>;

template <typename... T>
using Tuple = std::tuple<T...>;