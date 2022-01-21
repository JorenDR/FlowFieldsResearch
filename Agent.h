#pragma once
class Agent
{
public:
	Agent(Point2f position, float speed);
	~Agent();

	void MoveTowards(Point2f);
	void Draw();

	bool GetIsMoving();
private:
	Point2f m_Position, m_Destination;
	float m_Speed;
	bool m_IsMoving;
};

