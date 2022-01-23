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
	std::cout << "\nAgent destroyed";
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
}

bool Agent::GetIsMoving()
{
	return m_IsMoving;
}

Point2f Agent::GetPosition()
{
	return m_Position;
}

void Agent::SetDestination(Point2f target)
{
	std::cout << "\nNew destination entered";
	m_Destination = target;
}
