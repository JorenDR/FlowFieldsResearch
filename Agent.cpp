#include "pch.h"
#include "Agent.h"
#include "utils.h"
#include <iostream>

Agent::Agent(Point2f position, float speed)
	: m_Position{ position }
	, m_Speed{ speed }
	, m_IsMoving{ false }
	, m_Cooldown{ 0 }
	, m_MaxCooldown{ 2 }
	, m_Destination{ 0,0 }
{
}

Agent::~Agent()
{
}

void Agent::MoveTowards(Point2f target)
{
	m_Position = target;
}

bool Agent::Update(float elapsedSec)
{
	m_Cooldown += elapsedSec;
	if (m_Cooldown >= m_MaxCooldown)
	{
		m_Cooldown = 0;
		if (m_Destination.x != 0)
		{
			MoveTowards(m_Destination);
			std::cout << "\nAgent moved.";
		}
		return true;
	}
	return false;
}

void Agent::Draw()
{
	utils::SetColor(Color4f(1.f, .5f, .5f, 1.f));
	utils::DrawEllipse(m_Position, 5.f, 5.f);
	utils::DrawPoint(m_Destination);
	utils::DrawLine(m_Position, m_Destination);
}

bool Agent::GetIsMoving()
{
	return m_IsMoving;
}

Point2f Agent::GetPosition()
{
	return m_Position;
}

Point2f Agent::GetDestination()
{
	return m_Destination;
}

Point2f Agent::MoveTowards(const Point2f& p1, const Point2f& p2, const float& distance)
{
	m_Destination = p2;
	Point2f vector{ p2.x - p1.x, p2.y - p1.y };
	float length{ sqrt(vector.x * vector.x + vector.y * vector.y) };
	Point2f unitVector{ vector.x / length, vector.y / length };
	m_Position = Point2f(p1.x + unitVector.x * distance, p1.y + unitVector.y * distance);
	return Point2f(p1.x + unitVector.x * distance, p1.y + unitVector.y * distance);

}

float Agent::GetSpeed()
{
	return m_Speed;
}

void Agent::SetDestination(Point2f target)
{
	std::cout << "\nNew destination entered";
	m_Destination = target;
}

void Agent::SetPosition(Point2f newPosition)
{
	m_Position = newPosition;
}
