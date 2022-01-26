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

	for (Square* currentSquare : m_VecSquares)
	{
		for (Square* neighbourSquare : m_VecSquares)
		{
			if ((neighbourSquare->m_X + m_RectSize == currentSquare->m_X && neighbourSquare->m_Y == currentSquare->m_Y) ||
				(neighbourSquare->m_X + m_RectSize == currentSquare->m_X && neighbourSquare->m_Y + m_RectSize == currentSquare->m_Y) ||
				(neighbourSquare->m_X + m_RectSize == currentSquare->m_X && neighbourSquare->m_Y - m_RectSize == currentSquare->m_Y) ||
				(neighbourSquare->m_X - m_RectSize == currentSquare->m_X && neighbourSquare->m_Y == currentSquare->m_Y) ||
				(neighbourSquare->m_Y - m_RectSize == currentSquare->m_Y && neighbourSquare->m_X == currentSquare->m_X) ||
				(neighbourSquare->m_Y - m_RectSize == currentSquare->m_Y && neighbourSquare->m_X + m_RectSize == currentSquare->m_X) ||
				(neighbourSquare->m_Y - m_RectSize == currentSquare->m_Y && neighbourSquare->m_X - m_RectSize == currentSquare->m_X) ||
				(neighbourSquare->m_Y + m_RectSize == currentSquare->m_Y && neighbourSquare->m_X == currentSquare->m_X))
			{
				currentSquare->m_Neighbours.push_back(neighbourSquare);
			}
			
		}

	}

	m_Start = m_VecSquares.at(0);
	m_End = m_VecSquares.at(m_VecSquares.size()-1);
	//Dijkstra(m_Start, m_End);
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
		//if (currentAgent->Update(elapsedSec))
		//{
			//std::cout << "\nAgent updating!";
			for (Square* currentSquare : m_VecSquares)
			{
				if (currentSquare->m_PointingAtSquare &&
					currentAgent->GetPosition().x < currentSquare->m_X + m_RectSize / 2 &&
					currentAgent->GetPosition().x > currentSquare->m_X - m_RectSize / 2 &&
					
					currentAgent->GetPosition().y < currentSquare->m_Y + m_RectSize / 2 &&
					currentAgent->GetPosition().y > currentSquare->m_Y - m_RectSize / 2)
				{
					//currentAgent->SetDestination(currentSquare->m_PointingAtSquare->m_Position);
					currentAgent->MoveTowards(currentAgent->GetPosition(), currentSquare->m_PointingAtSquare->m_Position, currentAgent->GetSpeed());
				}
			}
		//}
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
		//utils::DrawRect(Rectf(currentSquare->m_X - m_RectSize / 2, currentSquare->m_Y - m_RectSize / 2, m_RectSize, m_RectSize));
		//utils::DrawEllipse(currentSquare->m_X, currentSquare->m_Y, 2.f, 2.f);
		//
		//switch (currentSquare->m_Direction)
		//{
		//case Square::Direction::Up:
		//	utils::DrawEllipse(currentSquare->m_X, currentSquare->m_Y + ellipseSize*2, ellipseSize, ellipseSize);
		//	utils::DrawEllipse(currentSquare->m_X, currentSquare->m_Y + ellipseSize*4, ellipseSize, ellipseSize);
		//	utils::SetColor(Color4f(1, 0, 1, 1));
		//	break;
		//case Square::Direction::Down:
		//	utils::DrawEllipse(currentSquare->m_X, currentSquare->m_Y - ellipseSize * 2, ellipseSize, ellipseSize);
		//	utils::DrawEllipse(currentSquare->m_X, currentSquare->m_Y - ellipseSize * 4, ellipseSize, ellipseSize);
		//	utils::SetColor(Color4f(0, 0, 0, 1));
		//	break;
		//case Square::Direction::Left:
		//	utils::DrawEllipse(currentSquare->m_X - ellipseSize * 2, currentSquare->m_Y , ellipseSize, ellipseSize);
		//	utils::DrawEllipse(currentSquare->m_X - ellipseSize * 4, currentSquare->m_Y , ellipseSize, ellipseSize);
		//	utils::SetColor(Color4f(0, 1, 1, 1));
		//	break;
		//case Square::Direction::Right:
		//	utils::DrawEllipse(currentSquare->m_X + ellipseSize * 2, currentSquare->m_Y, ellipseSize, ellipseSize);
		//	utils::DrawEllipse(currentSquare->m_X + ellipseSize * 4, currentSquare->m_Y, ellipseSize, ellipseSize);
		//	utils::SetColor(Color4f(0, 1, 0, 1));
		//	break;
		//case Square::Direction::Exit:
		//	utils::SetColor(Color4f(1, 0, 0, 1));
		//	break;
		//default:
		//	break;
		//}
		//
		//if (currentSquare->m_PointingAt.x != 0)
		//{
		//	utils::DrawLine(Point2f(currentSquare->m_X, currentSquare->m_Y), currentSquare->m_PointingAt);
		//}

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

		if (currentSquare->m_PointingAtSquare)
		{
			if (currentSquare->m_PointingAtSquare->m_Position.x == currentSquare->m_Position.x &&
				currentSquare->m_PointingAtSquare->m_Position.y == currentSquare->m_Position.y)
			{
				utils::SetColor(Color4f(1, 0, 0, 1));
				utils::FillRect(Rectf(currentSquare->m_X - m_RectSize / 2, currentSquare->m_Y - m_RectSize / 2, m_RectSize, m_RectSize));
			}
			else
			{
				utils::DrawLine(currentSquare->m_Position, currentSquare->m_PointingAtSquare->m_Position);
				utils::DrawPoint(currentSquare->m_PointingAtSquare->m_Position);
			}
		}
		else 
		{
			utils::SetColor(Color4f(1, 0, 0, 1));
			utils::FillRect(Rectf(currentSquare->m_X - m_RectSize / 2, currentSquare->m_Y - m_RectSize / 2, m_RectSize, m_RectSize));
		}
	}

	utils::SetColor(Color4f(0, 1, 0, 1));
	utils::FillRect(Rectf(m_Start->m_X - m_RectSize / 2, m_Start->m_Y - m_RectSize / 2, m_RectSize, m_RectSize));


	for (Square* currentSquare : m_Path)
	{
		utils::SetColor(Color4f(1.f, 0, 0, 1.f));
		utils::DrawEllipse(Point2f(currentSquare->m_X, currentSquare->m_Y), 10.f, 10.f);
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
			//currentSquare->m_Direction = Square::Direction::Null;

			if (e.x < currentSquare->m_X + m_RectSize / 2 && e.x > currentSquare->m_X - m_RectSize / 2
				&& m_Window.height - e.y < currentSquare->m_Y + m_RectSize / 2 && m_Window.height - e.y > currentSquare->m_Y - m_RectSize / 2)
			{
				//currentSquare->m_Direction = Square::Direction::Exit;
				//CalculateFlowField(currentSquare);
				m_Start = currentSquare;
				//m_Path = Dijkstra(m_Start, m_End);

				for (Square* pathSquare : m_VecSquares)
				{
					if (pathSquare != currentSquare)
					{
						Dijkstra(currentSquare, pathSquare);
					}
				}
				std::cout << "\nClicked position: [" << currentSquare->m_X << ", " << currentSquare->m_Y << "]";
			}
		}

		break;
	case SDL_BUTTON_RIGHT:
		//SpawnAgent(Point2f(float(e.x), float(e.y)));

		for (Square* currentSquare : m_VecSquares)
		{
			currentSquare->m_Direction = Square::Direction::Null;

			if (e.x < currentSquare->m_X + m_RectSize / 2 && e.x > currentSquare->m_X - m_RectSize / 2
				&& m_Window.height - e.y < currentSquare->m_Y + m_RectSize / 2 && m_Window.height - e.y > currentSquare->m_Y - m_RectSize / 2)
			{
				//currentSquare->m_Direction = Square::Direction::Exit;
				//CalculateFlowField(currentSquare);
				m_End = currentSquare;
				m_Path = Dijkstra(m_Start, m_End);

				//SpawnAgent(Point2f(currentSquare->m_X, m_Window.height - currentSquare->m_Y));
			}
		}

		break;
	case SDL_BUTTON_MIDDLE:
		for (Square* currentSquare : m_VecSquares)
		{

			if (e.x < currentSquare->m_X + m_RectSize / 2 && e.x > currentSquare->m_X - m_RectSize / 2
				&& m_Window.height - e.y < currentSquare->m_Y + m_RectSize / 2 && m_Window.height - e.y > currentSquare->m_Y - m_RectSize / 2)
			{

				SpawnAgent(Point2f(currentSquare->m_X, m_Window.height - currentSquare->m_Y));
			}
		}
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

float Game::Distance(float x1, float y1, float x2, float y2)
{
	// Calculating distance
	return float(sqrt(pow(x2 - x1, 2) +
		pow(y2 - y1, 2) * 1.0));
}

void Game::CalculateFlowField(Square* exitPoint)
{
	std::cout << "\n\nChecking Flow Field:\n";


	/*
	
	std::vector<Square*> path;
	std::vector<Square::SquareRecord> openList;
	std::vector<Square::SquareRecord> closedList;
	Square::SquareRecord currentRecord;

	Square::SquareRecord startRecord;
	startRecord.pSquare = m_VecSquares.at(0);
	openList.push_back(startRecord);

	//2
	while (!openList.empty())
	{
		//2.A
		currentSq = *openList.begin();

		//2.B
		//DONE
		if (currentRecord.pSquare == exitPoint)
		{
			break;
		}

		//2.C
		//DONE
		else
		{
			GraphConnection* nextConnection{};
			for (auto con : m_pGraph->GetNodeConnections(currentRecord.pNode))
			{
				T_NodeType* pNextNode = m_pGraph->GetNode(con->GetTo());

				NodeRecord newRecord{};
				newRecord.pNode = pNextNode;
				newRecord.pConnection = con;
				newRecord.costSoFar = currentRecord.costSoFar + con->GetCost();
				newRecord.estimatedTotalCost = con->GetCost() + currentRecord.costSoFar + GetHeuristicCost(pNextNode, pGoalNode);

				auto isSameNode = [newRecord](const NodeRecord& current) {return current.pNode == newRecord.pNode; };
				auto nextNodeClosed = std::find_if(closedList.begin(), closedList.end(), isSameNode);
				if (nextNodeClosed != closedList.end())
				{
					if (nextNodeClosed->costSoFar < newRecord.costSoFar)
					{
						continue;
					}
					else
					{
						closedList.erase(std::remove(closedList.begin(), closedList.end(), *nextNodeClosed));
					}
				}
				else
				{
					auto nextNodeOpen = std::find_if(openList.begin(), openList.end(), isSameNode);
					if (nextNodeOpen != openList.end())
					{
						if (nextNodeOpen->costSoFar < newRecord.costSoFar)
						{
							continue;
						}
						else
						{
							openList.erase(std::remove(openList.begin(), openList.end(), *nextNodeOpen));
						}
					}
				}
				openList.push_back(newRecord);
			}
		}

		//2.G
		closedList.push_back(currentRecord);
		openList.erase(std::remove(openList.begin(), openList.end(), currentRecord));
	}

	//3
	while (currentRecord.pNode != pStartNode)
	{
		//std::cout << "\nStart";
		path.push_back(currentRecord.pNode);
		for (auto node : closedList)
		{
			if (node.pNode->GetIndex() == currentRecord.pConnection->GetFrom())
			{
				currentRecord = node;
				break;
			}
		}
	}
	path.push_back(pStartNode);

	std::reverse(path.begin(), path.end());

	*/

	
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

	Agent* newAgent = new Agent(pointToSpawn, .2f);
	m_VecAgentPointers.push_back(newAgent);
}

std::vector<Square*> Game::GetNeighbours(Square* square)
{
	std::vector<Square*> neighbours;
	for (auto currentSquare : m_VecSquares)
	{
		if (currentSquare)
		{
			if ((currentSquare->m_X + m_RectSize == square->m_X && currentSquare->m_Y == square->m_Y) ||
				(currentSquare->m_X + m_RectSize == square->m_X && currentSquare->m_Y + m_RectSize == square->m_Y) ||
				(currentSquare->m_X + m_RectSize == square->m_X && currentSquare->m_Y - m_RectSize == square->m_Y) ||
				(currentSquare->m_X - m_RectSize == square->m_X && currentSquare->m_Y == square->m_Y) ||
				(currentSquare->m_Y - m_RectSize == square->m_Y && currentSquare->m_X == square->m_X) ||
				(currentSquare->m_Y - m_RectSize == square->m_Y && currentSquare->m_X + m_RectSize == square->m_X) ||
				(currentSquare->m_Y - m_RectSize == square->m_Y && currentSquare->m_X - m_RectSize == square->m_X) ||
				(currentSquare->m_Y + m_RectSize == square->m_Y && currentSquare->m_X == square->m_X))
			{
				neighbours.push_back(currentSquare);
			}
		}
		else
		{
			std::cout << "\nTried to get neighbour, but currenSquare is nullptr";
		}
	}

	return neighbours;
}

std::vector<Square*> Game::Dijkstra(Square* startPoint, Square* endPoint)
{
	std::queue<Square*> openList;
	std::map<Square*, Square*> closedList;

	openList.push(startPoint);

	while (!openList.empty())
	{
		Square* pCurrentNode = openList.front();
		openList.pop();

		if (pCurrentNode == endPoint)
		{
			break;
		}

		for (auto con : pCurrentNode->m_Neighbours)
		{
			Square* pNextNode;
			float distanceToEnd{9999};
			for (auto nextNode : pCurrentNode->m_Neighbours)
			{
				float distance{ Distance(nextNode->m_X, nextNode->m_Y, endPoint->m_X, endPoint->m_Y) };
				if (distance < distanceToEnd)
				{
					distanceToEnd = distance;
					pNextNode = nextNode;
				}
			}

			if (closedList.find(pNextNode) == closedList.end())
			{
				openList.push(pNextNode);
				closedList[pNextNode] = pCurrentNode;
			}
		}
	}

	std::vector<Square*> path;
	Square* pCurrentNode = endPoint;

	while (pCurrentNode != startPoint)
	{
		if (path.size() != 0)
		{
			//path.at(path.size() - 1)->m_PointingAtSquare = pCurrentNode;
			pCurrentNode->m_PointingAtSquare = path.at(path.size() - 1);
		}
		else
		{
			pCurrentNode->m_PointingAtSquare = endPoint;
		}

		path.push_back(pCurrentNode);
		pCurrentNode = closedList[pCurrentNode];
	}
	if (path.size() > 2)
		endPoint->m_PointingAtSquare = path.at(1);

	for (unsigned int currentSquare{ 0 }; currentSquare < path.size()-1; ++currentSquare)
	{
		//currentSquare->m_PointingAtSquare = path;
		path.at(currentSquare)->m_PointingAtSquare = path.at(currentSquare + 1);
	}

	path.push_back(startPoint);
	startPoint->m_PointingAtSquare = path.at(path.size() - 1);
	//path.at(0)->m_PointingAtSquare = endPoint;
	//std::reverse(path.begin(), path.end());

	return path;
}

