#pragma once
#include "glut.h"
#include <corecrt_math.h>
#include <string>

#define TREE_BARK_HEIGHT 0.05
#define TREE_BARK_WIDTH 0.005
#define STAR_LINE_DELTA 0.004
#define HOUSE_WIDTH 0.025
#define HOUSE_HEIGHT 0.04
#define HOUSE_WINDOW_LENGTH 0.006
#define HOUSE_WINDOW_HEIGHT 0.0275
#define HOUSE_DOOR_WIDTH 0.01
#define HOUSE_DOOR_HEIGHT 0.0175


void DrawStar(float x, float y);
void DrawCircle(float center_x, float center_y, float radius);
void DrawTree(float base_x, float base_y);
void DrawText(const char* text, int txt_len, void* font, GLfloat x_pos, GLfloat y_pos);
void DrawHouse(float base_x, float base_y);

class MyBasicButton
{


public:
	void Draw();
	void SetColor(float red, float green, float blue);
	MyBasicButton(float pos_t1x, float pos_t1y, float pos_t2x, float pos_t2y, float color_red, float color_green, float color_blue, void(*onClick_Callback)(), std::string text);
	~MyBasicButton();
	void CheckClick(float x, float y);

private:
	float pos_t1x;
	float pos_t1y;
	float pos_t2x;
	float pos_t2y;

	float color_red;
	float color_green;
	float color_blue;
	void(*ClickedCallback)();
	std::string text;
};