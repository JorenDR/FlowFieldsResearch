#include "pch.h"
#include "Square.h"

Square::Square(float x, float y, Direction direction, bool obstacle)
	: m_X{ x }
	, m_Y{ y }
	, m_Direction{ direction }
	, m_IsObstacle{ obstacle }
	, m_PointingAt{ 0, 0 }
{
}

Square::~Square()
{
}
