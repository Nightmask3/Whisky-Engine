#pragma once

#include "..\..\Dependencies\glm\glm\glm.hpp"

class Color
{
public:
	Color();
	~Color();
	Color(const glm::vec4);

	glm::vec4 Value() const { return value; }

public:
	static const glm::vec4 black, white, red, green, blue, magenta, yellow, cyan;

private:
	glm::vec4 value;
};

