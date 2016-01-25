#include "Color.h"

const glm::vec4 Color::black	= glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 Color::white	= glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
const glm::vec4 Color::red		= glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 Color::green	= glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
const glm::vec4 Color::blue		= glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
const glm::vec4 Color::yellow	= glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
const glm::vec4 Color::magenta	= glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
const glm::vec4 Color::cyan		= glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);


Color::Color() : value(white)
{
}


Color::~Color()
{
}

Color::Color(const glm::vec4 val)
	: 
	value(val)
{}
