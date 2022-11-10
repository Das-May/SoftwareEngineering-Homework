#include "SceneModel.h"

float* GetGroundVertices(float width, float height)
{

	float vertices[] = {
		// positions				// texture coords
		-width / 2, 0, height / 2,		0.0f, 1.0f,		// top left
		-width / 2, 0, -height / 2,		0.0f, 1.0f,		// down left
		width / 2, 0, height / 2,		0.0f, 1.0f,		// top right

		width / 2, 0, -height / 2,		0.0f, 1.0f		// down right
		- width / 2, 0, height / 2,		0.0f, 1.0f,		// top left
		-width / 2, 0, -height / 2,		0.0f, 1.0f,		// down left
	};
	return vertices;
}
