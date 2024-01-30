#pragma once
template<typename T,typename U>
class Pair {
public:
	Pair() = default;
	Pair(T first, U second) {
		this->first = first;
		this->second = second;
	}
	T first;
	U second;
};