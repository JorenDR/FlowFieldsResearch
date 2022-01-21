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
			Square* newSquare = new Square{};
			newSquare->x = x * m_RectSize + m_RectSize / 2;
			newSquare->y = y * m_RectSize + m_RectSize / 2;
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
		currentAgent->MoveTowards(Point2f(0,0));
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	utils::SetColor(Color4f( 1, 1, 1, 1 ));

	for (const Square* currentSquare : m_VecSquares)
	{
		utils::SetColor(Color4f(1, 1, 1, 1));
		utils::DrawRect(Rectf(currentSquare->x - m_RectSize / 2, currentSquare->y - m_RectSize / 2, m_RectSize, m_RectSize));

		switch (currentSquare->direction)
		{
		case Direction::Up:
			utils::SetColor(Color4f(1, 0, 1, 1));
			break;
		case Direction::Down:
			utils::SetColor(Color4f(0, 0, 0, 1));
			break;
		case Direction::Left:
			utils::SetColor(Color4f(0, 1, 1, 1));
			break;
		case Direction::Right:
			utils::SetColor(Color4f(0, 1, 0, 1));
			break;
		case Direction::Exit:
			utils::SetColor(Color4f(1, 0, 0, 1));
			break;
		default:
			break;
		}

		if(currentSquare->direction != Direction::Null) utils::FillRect(Rectf(currentSquare->x - m_RectSize / 2, currentSquare->y - m_RectSize / 2, m_RectSize, m_RectSize));

		//if (currentSquare.direction != Direction::Null && currentSquare.direction != Direction::Exit)
		//{
		//	utils::SetColor(Color4f(0, 1, 0, 1));
		//	utils::FillRect(Rectf(currentSquare.x - m_RectSize / 2, currentSquare.y - m_RectSize / 2, m_RectSize, m_RectSize));
		//}
		//
		//if (currentSquare.direction == Direction::Exit)
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
			currentSquare->direction = Direction::Null;

			if (e.x < currentSquare->x + m_RectSize / 2 && e.x > currentSquare->x - m_RectSize / 2
				&& m_Window.height - e.y < currentSquare->y + m_RectSize / 2 && m_Window.height - e.y > currentSquare->y - m_RectSize / 2)
			{
				currentSquare->direction = Direction::Exit;
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
	std::vector<Square*> checked, toBeChecked;
	Square* pointingAt = exitPoint;
	
	for (Square* currentSquare : m_VecSquares)
	{
		toBeChecked.push_back(currentSquare);
	}
	
	for (Square* currentSquare : toBeChecked)
	{
		if (currentSquare->direction == Direction::Null)
		{
			if (currentSquare->x + m_RectSize == pointingAt->x && currentSquare->y == pointingAt->y)
			{
				currentSquare->direction = Direction::Right;
				std::cout << "\nSquare pointing right";
			}
	
			else if (currentSquare->x - m_RectSize == pointingAt->x && currentSquare->y == pointingAt->y)
			{
				currentSquare->direction = Direction::Left;
				std::cout << "\nSquare pointing left";
			}
	
			else if (currentSquare->y - m_RectSize == pointingAt->y && currentSquare->x == pointingAt->x)
			{
				currentSquare->direction = Direction::Up;
				std::cout << "\nSquare pointing up";
			}
	
			else if (currentSquare->y + m_RectSize == pointingAt->y && currentSquare->x == pointingAt->x)
			{
				currentSquare->direction = Direction::Down;
				std::cout << "\nSquare pointing down";
			}
		}
		//std::cout << "\nSquare at [" << currentSquare.x << ", " << currentSquare.y << "] checked";
		pointingAt = currentSquare;
		//toBeChecked.erase(std::remove(toBeChecked.begin(), toBeChecked.end(), currentSquare));
	}
	
	m_VecSquares.clear();
	m_VecSquares = toBeChecked;

	//unsigned int targetID = exitPoint->y * m_GridWidth + exitPoint->x;
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
	Point2f pointToSpawn{ m_VecSquares.at(0)->x, m_VecSquares.at(0)->y };

	for (Square* currentSquare : m_VecSquares)
	{
		if (position.x < currentSquare->x + m_RectSize / 2 && position.x > currentSquare->x - m_RectSize / 2
			&& m_Window.height - position.y < currentSquare->y + m_RectSize / 2 && m_Window.height - position.y > currentSquare->y - m_RectSize / 2)
		{
			pointToSpawn = Point2f(currentSquare->x, currentSquare->y);
		}
	}

	Agent* newAgent = new Agent(pointToSpawn, 5.f);
	m_VecAgentPointers.push_back(newAgent);
}


//std::vector<Square*> Game::GetNeighbours(int x, int y)
//{
//	std::vector<Square*> neighboursToReturn;
//
//	for (Square* currentSquare : m_VecSquares)
//	{
//		if (currentSquare->x + m_RectSize == x && currentSquare->y == y)
//		{
//			neighboursToReturn.push_back(currentSquare);
//		}
//	
//		else if (currentSquare->x - m_RectSize == x && currentSquare->y == y)
//		{
//			neighboursToReturn.push_back(currentSquare);
//		}
//	
//		else if (currentSquare->y - m_RectSize == y && currentSquare->x == x)
//		{
//			neighboursToReturn.push_back(currentSquare);
//		}
//	
//		else if (currentSquare->y + m_RectSize == y && currentSquare->x == x)
//		{
//			neighboursToReturn.push_back(currentSquare);
//		}
//	}
//
//	return neighboursToReturn;
//}
