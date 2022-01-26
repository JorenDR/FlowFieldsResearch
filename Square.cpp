#include "pch.h"
#include "Square.h"
#include <iostream>

Square::Square(float x, float y, Direction direction, bool obstacle)
	: m_X{ x }
	, m_Y{ y }
	, m_Position{ x, y }
	, m_Direction{ direction }
	, m_IsObstacle{ obstacle }
	, m_PointingAt{ 0, 0 }
	, m_PointingAtSquare{ nullptr }
	, m_Value{ 0 }
{
}

Square::~Square()
{
}
