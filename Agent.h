#pragma once
class Agent
{
public:
	Agent(Point2f position, float speed);
	~Agent();

	void MoveTowards(Point2f target);
	bool Update(float elapsedSec);
	void Draw();

	bool GetIsMoving();
	Point2f GetPosition();

	void SetDestination(Point2f target);
private:
	Point2f m_Position, m_Destination;
	float m_Speed;
	bool m_IsMoving;
	float m_Cooldown, m_MaxCooldown;
};

