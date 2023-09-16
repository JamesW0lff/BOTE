#include "GameState.h"
#include "HeartState.h"
#include "CircleState.h"
#include "ShapeState.h"

using namespace BOTE;

#pragma region WIN MAIN
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	// Create multiple game states, each drawing a different colored shape.
	// - Draw a heart
	// - Draw a circle (using a for loop + sin/cos to compute vertices
	// - Draw something with more than 5 triangles

	// GameApp().AddState<GameState>("GameState");
	GameApp().AddState<HeartState>("HeartState");
	GameApp().AddState<CircleState>("CircleState");
	GameApp().AddState<ShapeState>("ShapeState");
	
	BOTE::GameApp().Run({ L"Hello Shapes" });

	return 0;
}
#pragma endregion