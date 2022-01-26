#pragma once
#include <vector>
#include <list>
#include <queue>
#include <map>
#include "Square.h"

class Agent;

class Game final
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( ) const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS

	const Window m_Window;
	static const int m_GridWidth{ 40 }, m_GridHeight{ 20 };
	float m_RectSize{ 20 };
	std::vector<Square*> m_VecSquares;
	std::vector<Square*> m_Path;
	std::vector<Agent*> m_VecAgentPointers;

	Square* m_Start;
	Square* m_End;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	float Distance(float x1, float y1, float x2, float y2);

	void SpawnAgent(Point2f position);
	std::vector<Square*> GetNeighbours(Square* square);
	std::vector<Square*> Dijkstra(Square* startPoint, Square* endPoint);
};