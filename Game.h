#pragma once
#include <vector>
#include <list>

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

	enum class Direction
	{
		Null,
		Up,
		Down,
		Left,
		Right,
		Exit
	};

	struct Square
	{
		float x{ 0 }, y{ 0 };
		Direction direction = Direction::Null;
		bool obstacle{ false };
	};

	const Window m_Window;
	static const int m_GridWidth{ 20 }, m_GridHeight{ 10 };
	float m_RectSize{ 40 };
	std::vector<Square*> m_VecSquares;
	std::vector<Agent*> m_VecAgentPointers;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	void CalculateFlowField(Square* exitPoint);
	void SpawnAgent(Point2f position);
	//std::vector<Square*> GetNeighbours(int x, int y);
};