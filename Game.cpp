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
		delete m_VecAgentPointers.at(i);
		m_VecAgentPointers.at(i) = nullptr;
	}
	m_VecAgentPointers.clear();
	
	for (unsigned int i{ 0 }; i < m_VecSquares.size(); ++i)
	{
		delete m_VecSquares.at(i);
		m_VecSquares.at(i) = nullptr;
	}
	m_VecSquares.clear();
}

void Game::Update( float elapsedSec )
{
	for (Agent* currentAgent : m_VecAgentPointers)
	{
		for (Square* currentSquare : m_VecSquares)
		{
			if (currentSquare->m_PointingAtSquare &&
				currentAgent->GetPosition().x < currentSquare->m_X + m_RectSize / 2 &&
				currentAgent->GetPosition().x > currentSquare->m_X - m_RectSize / 2 &&

				currentAgent->GetPosition().y < currentSquare->m_Y + m_RectSize / 2 &&
				currentAgent->GetPosition().y > currentSquare->m_Y - m_RectSize / 2)
			{
				if (currentSquare->m_PointingAtSquare)
				{
					currentAgent->MoveTowards(currentAgent->GetPosition(), currentSquare->m_PointingAtSquare->m_Position, currentAgent->GetSpeed());
				}
			}
		}

		//std::cout << "\nPosition: [" << currentAgent->GetPosition().x << ", " << currentAgent->GetPosition().y << "]";
		//std::cout << "\nDestination: [" << currentAgent->GetDestination().x << ", " << currentAgent->GetDestination().y << "]";
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
	if (e.keysym.sym == SDLK_SPACE)
	{
		for (Agent* currentAgent : m_VecAgentPointers)
		{
			delete currentAgent;
			currentAgent = nullptr;
		}
		m_VecAgentPointers.clear();
	}
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

				for (auto currentSquare : m_Start->m_Neighbours)
				{
					currentSquare->m_PointingAtSquare = m_Start;
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
				//m_End = currentSquare;
				//m_Path = Dijkstra(m_Start, m_End);

				for (Square* neighbour : currentSquare->m_Neighbours)
				{
					SpawnAgent(Point2f(neighbour->m_X, m_Window.height - neighbour->m_Y));
				}

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
				for (Square* neighbour : currentSquare->m_Neighbours)
				{
					SpawnAgent(Point2f(neighbour->m_X, m_Window.height - neighbour->m_Y));
				}
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

