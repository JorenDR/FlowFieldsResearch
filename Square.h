#pragma once
#include <vector>
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

	struct SquareRecord
	{
		Square* pConnectedTo = nullptr;
		Square* pConnectedFrom = nullptr;
	};

	Square(float x = 0, float y = 0, Direction direction = Direction::Null, bool obstacle = false);
	~Square();

	float m_X, m_Y;
	Point2f m_PointingAt;
	Point2f m_Position;
	Square* m_PointingAtSquare;
	Direction m_Direction;
	bool m_IsObstacle;
	int m_Value;

	std::vector<Square*> m_Neighbours;

private:

};