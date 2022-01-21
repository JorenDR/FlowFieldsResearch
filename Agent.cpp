#include "pch.h"
#include "Agent.h"
#include "utils.h"
#include <iostream>

Agent::Agent(Point2f position, float speed)
	: m_Position{ position }
	, m_Speed{ speed }
	, m_IsMoving{ false }
{
}

Agent::~Agent()
{
	std::cout << "\nAgent destroyed";
}

void Agent::MoveTowards(Point2f)
{
	//m_Position += m_Speed;
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
