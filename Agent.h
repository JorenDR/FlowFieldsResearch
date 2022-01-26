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
	Point2f GetDestination();
	Point2f MoveTowards(const Point2f& p1, const Point2f& p2, const float& distance);

	float GetSpeed();

	void SetDestination(Point2f target);
	void SetPosition(Point2f newPosition);
private:
	Point2f m_Position, m_Destination;
	float m_Speed;
	bool m_IsMoving;
	float m_Cooldown, m_MaxCooldown;
};

