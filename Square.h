#pragma once
class Square
{
public:
	enum class Direction
	{
		Null,
		Up,
		Down,
		Left,
		Right,
		Exit
	};

	Square(float x = 0, float y = 0, Direction direction = Direction::Null, bool obstacle = false);
	~Square();

	float m_X, m_Y;
	Point2f m_PointingAt;
	Direction m_Direction;
	bool m_IsObstacle;

private:

};

