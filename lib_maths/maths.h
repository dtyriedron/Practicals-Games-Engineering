#pragma once

#include <SFML/System.hpp>
#include <cmath>
#include <iostream>
#include <vector>

namespace sf
{
	//create a definition for a sf::vector using size_t types
	typedef Vector2<size_t> Vector2ul;
	//returns the length of a sf::vector
	template <typename T> double length(const Vector2<T> &v)
	{
		return sqrt((v.x)*(v.x) + (v.y)*(v.y));
	}
}