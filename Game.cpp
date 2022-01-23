#include "pch.h"
#include "Game.h"
#include "utils.h"
#include <iostream>
#include "Agent.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	for (int x{ 0 }; x < m_GridWidth; ++x)
	{
		for (int y{ 0 }; y < m_GridHeight; ++y)
		{
			Square* newSquare = new Square{ x * m_RectSize + m_RectSize / 2, y * m_RectSize + m_RectSize / 2 };
			m_VecSquares.push_back(newSquare);
		}
	}
}

void Game::Cleanup( )
{
	for (unsigned int i{ 0 }; i < m_VecAgentPointers.size(); ++i)
	{
		m_VecAgentPointers.at(i)->~Agent();
		m_VecAgentPointers.at(i) = nullptr;
	}
	m_VecAgentPointers.clear();
	//
	//for (unsigned int i{ 0 }; i < m_VecSquares.size(); ++i)
	//{
	//	//m_VecSquares.at(i) = nullptr;
	//}
	m_VecSquares.clear();

	
}

void Game::Update( float elapsedSec )
{
	for (Agent* currentAgent : m_VecAgentPointers)
	{
		if (currentAgent->Update(elapsedSec))
		{
			for (Square* currentSquare : m_VecSquares)
			{
				if (currentSquare->m_PointingAt.x != 0 &&
					currentAgent->GetPosition().x < currentSquare->m_X + m_RectSize / 2 &&
					currentAgent->GetPosition().x > currentSquare->m_X - m_RectSize / 2 &&
					m_Window.height - currentAgent->GetPosition().y < currentSquare->m_Y + m_RectSize / 2 &&
					m_Window.height - currentAgent->GetPosition().y > currentSquare->m_Y - m_RectSize / 2)
				{
					currentAgent->SetDestination(currentSquare->m_PointingAt);
				}
			}
		}
	}
}

void Game::Draw( ) const
{
	float ellipseSize{ 2.f };
	ClearBackground( );
	utils::SetColor(Color4f( 1, 1, 1, 1 ));

	for (const Square* currentSquare : m_VecSquares)
	{
		utils::SetColor(Color4f(1, 1, 1, 1));
		utils::DrawRect(Rectf(currentSquare->m_X - m_RectSize / 2, currentSquare->m_Y - m_RectSize / 2, m_RectSize, m_RectSize));
		utils::DrawEllipse(currentSquare->m_X, currentSquare->m_Y, 2.f, 2.f);

		switch (currentSquare->m_Direction)
		{
		case Square::Direction::Up:
			utils::DrawEllipse(currentSquare->m_X, currentSquare->m_Y + ellipseSize*2, ellipseSize, ellipseSize);
			utils::DrawEllipse(currentSquare->m_X, currentSquare->m_Y + ellipseSize*4, ellipseSize, ellipseSize);
			utils::SetColor(Color4f(1, 0, 1, 1));
			break;
		case Square::Direction::Down:
			utils::DrawEllipse(currentSquare->m_X, currentSquare->m_Y - ellipseSize * 2, ellipseSize, ellipseSize);
			utils::DrawEllipse(currentSquare->m_X, currentSquare->m_Y - ellipseSize * 4, ellipseSize, ellipseSize);
			utils::SetColor(Color4f(0, 0, 0, 1));
			break;
		case Square::Direction::Left:
			utils::DrawEllipse(currentSquare->m_X - ellipseSize * 2, currentSquare->m_Y , ellipseSize, ellipseSize);
			utils::DrawEllipse(currentSquare->m_X - ellipseSize * 4, currentSquare->m_Y , ellipseSize, ellipseSize);
			utils::SetColor(Color4f(0, 1, 1, 1));
			break;
		case Square::Direction::Right:
			utils::DrawEllipse(currentSquare->m_X + ellipseSize * 2, currentSquare->m_Y, ellipseSize, ellipseSize);
			utils::DrawEllipse(currentSquare->m_X + ellipseSize * 4, currentSquare->m_Y, ellipseSize, ellipseSize);
			utils::SetColor(Color4f(0, 1, 0, 1));
			break;
		case Square::Direction::Exit:
			utils::SetColor(Color4f(1, 0, 0, 1));
			break;
		default:
			break;
		}

		if (currentSquare->m_PointingAt.x != 0)
		{
			utils::DrawLine(Point2f(currentSquare->m_X, currentSquare->m_Y), currentSquare->m_PointingAt);
		}

		//if(currentSquare->m_Direction != Square::Direction::Null) utils::FillRect(Rectf(currentSquare->m_X - m_RectSize / 2, currentSquare->m_Y - m_RectSize / 2, m_RectSize, m_RectSize));

		//if (currentSquare.direction != Square::Direction::Null && currentSquare.direction != Square::Direction::Exit)
		//{
		//	utils::SetColor(Color4f(0, 1, 0, 1));
		//	utils::FillRect(Rectf(currentSquare.x - m_RectSize / 2, currentSquare.y - m_RectSize / 2, m_RectSize, m_RectSize));
		//}
		//
		//if (currentSquare.direction == Square::Direction::Exit)
		//{
		//	utils::SetColor(Color4f(1, 0, 0, 1));
		//	utils::FillRect(Rectf(currentSquare.x - m_RectSize / 2, currentSquare.y - m_RectSize / 2, m_RectSize, m_RectSize));
		//}
	}

	for (Agent* currentAgent : m_VecAgentPointers)
	{
		currentAgent->Draw();
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:

		for (Square* currentSquare : m_VecSquares)
		{
			currentSquare->m_Direction = Square::Direction::Null;

			if (e.x < currentSquare->m_X + m_RectSize / 2 && e.x > currentSquare->m_X - m_RectSize / 2
				&& m_Window.height - e.y < currentSquare->m_Y + m_RectSize / 2 && m_Window.height - e.y > currentSquare->m_Y - m_RectSize / 2)
			{
				currentSquare->m_Direction = Square::Direction::Exit;
				CalculateFlowField(currentSquare);
			}
		}

		break;
	case SDL_BUTTON_RIGHT:
		SpawnAgent(Point2f(float(e.x), float(e.y)));

		break;
	case SDL_BUTTON_MIDDLE:
		break;
	}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::CalculateFlowField(Square* exitPoint)
{
	std::cout << "\n\nChecking Flow Field:\n";

	Point2f pointToCheck{exitPoint->m_X, exitPoint->m_Y};
	
	for (Square* currentSquare : m_VecSquares)
	{
		currentSquare->m_PointingAt = Point2f(0, 0);
	}
	
	std::list<Square*> openList, closedList;
	openList.push_back(exitPoint);
	
	while (!openList.empty())
	{
		Square* currentSquare{ openList.front() };
	
		if (currentSquare->m_Direction == Square::Direction::Null)
		{
			if (currentSquare->m_X + m_RectSize == pointToCheck.x && currentSquare->m_Y == pointToCheck.y)
			{
				currentSquare->m_Direction = Square::Direction::Right;
				currentSquare->m_PointingAt = pointToCheck;
				std::cout << "\nSquare pointing right";
			}
	
			else if (currentSquare->m_X - m_RectSize == pointToCheck.x && currentSquare->m_Y == pointToCheck.y)
			{
				currentSquare->m_Direction = Square::Direction::Left;
				currentSquare->m_PointingAt = pointToCheck;
				std::cout << "\nSquare pointing left";
			}
	
			else if (currentSquare->m_Y - m_RectSize == pointToCheck.y && currentSquare->m_X == pointToCheck.x)
			{
				currentSquare->m_Direction = Square::Direction::Down;
				currentSquare->m_PointingAt = pointToCheck;
				std::cout << "\nSquare pointing down";
			}
	
			else if (currentSquare->m_Y + m_RectSize == pointToCheck.y && currentSquare->m_X == pointToCheck.x)
			{
				currentSquare->m_Direction = Square::Direction::Up;
				currentSquare->m_PointingAt = pointToCheck;
				std::cout << "\nSquare pointing up";
			}
		}
	
		auto neighbours = GetNeighbours(currentSquare);
		for (Square* newSquare : neighbours)
		{
			if (std::find(openList.begin(), openList.end(), newSquare) == openList.end() && std::find(closedList.begin(), closedList.end(), newSquare) == closedList.end())
			{
				openList.push_back(newSquare);
			}
		}
	
		//pointToCheck = Point2f(currentSquare->m_X, currentSquare->m_Y);
		closedList.push_back(currentSquare);
		openList.pop_front();
	}
	

	/*
	
	while (!openList.empty())
	{
		Square* currentSquare{ openList.front() };

		if (currentSquare->m_Direction == Square::Direction::Null)
		{
			if (currentSquare->m_X + m_RectSize == pointToCheck.x && currentSquare->m_Y == pointToCheck.y)
			{
				currentSquare->m_Direction = Square::Direction::Right;
				std::cout << "\nSquare pointing right";
			}

			else if (currentSquare->m_X - m_RectSize == pointToCheck.x && currentSquare->m_Y == pointToCheck.y)
			{
				currentSquare->m_Direction = Square::Direction::Left;
				std::cout << "\nSquare pointing left";
			}

			else if (currentSquare->m_Y - m_RectSize == pointToCheck.y && currentSquare->m_X == pointToCheck.x)
			{
				currentSquare->m_Direction = Square::Direction::Down;
				std::cout << "\nSquare pointing down";
			}

			else if (currentSquare->m_Y + m_RectSize == pointToCheck.y && currentSquare->m_X == pointToCheck.x)
			{
				currentSquare->m_Direction = Square::Direction::Up;
				std::cout << "\nSquare pointing up";
			}
		}

		auto neighbours = GetNeighbours(currentSquare);
		for (Square* newSquare : neighbours)
		{
			if (std::find(openList.begin(), openList.end(), newSquare) == openList.end() && std::find(closedList.begin(), closedList.end(), newSquare) == closedList.end())
			{
				openList.push_back(newSquare);
			}
		}

		closedList.push_back(currentSquare);
		openList.pop_front();
	}

	*/

	/*
	std::vector<Square*> checked, toBeChecked;
	Square* pointingAt = exitPoint;
	
	for (Square* currentSquare : m_VecSquares)
	{
		toBeChecked.push_back(currentSquare);
	}
	
	for (Square* currentSquare : toBeChecked)
	{
		if (currentSquare->m_Direction == Square::Direction::Null)
		{
			if (currentSquare->m_X + m_RectSize == pointingAt->m_X && currentSquare->m_Y == pointingAt->m_Y)
			{
				currentSquare->m_Direction = Square::Direction::Right;
				std::cout << "\nSquare pointing right";
			}
	
			else if (currentSquare->m_X - m_RectSize == pointingAt->m_X && currentSquare->m_Y == pointingAt->m_Y)
			{
				currentSquare->m_Direction = Square::Direction::Left;
				std::cout << "\nSquare pointing left";
			}
	
			else if (currentSquare->m_Y - m_RectSize == pointingAt->m_Y && currentSquare->m_X == pointingAt->m_X)
			{
				currentSquare->m_Direction = Square::Direction::Up;
				std::cout << "\nSquare pointing up";
			}
	
			else if (currentSquare->m_Y + m_RectSize == pointingAt->m_Y && currentSquare->m_X == pointingAt->m_X)
			{
				currentSquare->m_Direction = Square::Direction::Down;
				std::cout << "\nSquare pointing down";
			}
		}
		//std::cout << "\nSquare at [" << currentSquare.x << ", " << currentSquare.y << "] checked";
		pointingAt = currentSquare;
		//toBeChecked.erase(std::remove(toBeChecked.begin(), toBeChecked.end(), currentSquare));
	}
	
	m_VecSquares.clear();
	m_VecSquares = toBeChecked;

	*/

	//unsigned int targetID = exitPoint->m_Y * m_GridWidth + exitPoint->m_X;
	//
	//std::list<unsigned int> openList;
	//
	////Set goal node cost to 0 and add it to the open list
	//openList.push_back(targetID);
	//openList.push_back(targetID);
	//
	//while (openList.size() != 0)
	//{
	//	//Get the next node in the open list
	//	unsigned currentID = openList.front();
	//	openList.pop_front();
	//
	//	unsigned int currentX = currentID % m_GridWidth;
	//	unsigned int currentY = currentID / m_GridWidth;
	//
	//	//Get the N, E, S, and W neighbors of the current node
	//	std::vector<Square*> neighbors = GetNeighbours(currentX, currentY);
	//	int neighborCount = neighbors.size();
	//
	//	//Iterate through the neighbors of the current node
	//	for (int i = 0; i & lt; neighborCount; i++) {             //Calculate the new cost of the neighbor node             // based on the cost of the current node and the weight of the next node             unsigned int endNodeCost = getValueByIndex(currentID)                          + getCostField()-&gt;getCostByIndex(neighbors[i]);
	//
	//		//If a shorter path has been found, add the node into the open list
	//		if (endNodeCost& lt; getValueByIndex(neighbors[i]))
	//		{
	//			//Check if the neighbor cell is already in the list.
	//			//If it is not then add it to the end of the list.
	//			if (!checkIfContains(neighbors[i], openList))
	//			{
	//				openList.push_back(neighbors[i]);
	//			}
	//
	//			//Set the new cost of the neighbor node.
	//			setValueAt(neighbors[i], endNodeCost);
	//		}
	//	}
	//}
}

void Game::SpawnAgent(Point2f position)
{
	Point2f pointToSpawn{ m_VecSquares.at(0)->m_X, m_VecSquares.at(0)->m_Y };

	for (Square* currentSquare : m_VecSquares)
	{
		if (position.x < currentSquare->m_X + m_RectSize / 2 && position.x > currentSquare->m_X - m_RectSize / 2
			&& m_Window.height - position.y < currentSquare->m_Y + m_RectSize / 2 && m_Window.height - position.y > currentSquare->m_Y - m_RectSize / 2)
		{
			pointToSpawn = Point2f(currentSquare->m_X, currentSquare->m_Y);
		}
	}

	Agent* newAgent = new Agent(pointToSpawn, 5.f);
	m_VecAgentPointers.push_back(newAgent);
}

std::vector<Square*> Game::GetNeighbours(Square* square)
{
	std::vector<Square*> neighbours;
	for (auto currentSquare : m_VecSquares)
	{
		if ((currentSquare->m_X + m_RectSize == square->m_X && currentSquare->m_Y == square->m_Y) ||
			(currentSquare->m_X - m_RectSize == square->m_X && currentSquare->m_Y == square->m_Y) ||
			(currentSquare->m_Y - m_RectSize == square->m_Y && currentSquare->m_X == square->m_X) ||
			(currentSquare->m_Y + m_RectSize == square->m_Y && currentSquare->m_X == square->m_X))
		{
			neighbours.push_back(currentSquare);
		}
	}

	return neighbours;
}
