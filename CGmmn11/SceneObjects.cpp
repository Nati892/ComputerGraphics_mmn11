#include "SceneObjects.h"

//draws a star
void DrawStar(float x, float y)
{
	glColor3f(0.9f, 0.9f, 0.9f);//set star color to white
	glBegin(GL_LINES);

	//horizontal line
	glVertex2f(x - STAR_LINE_DELTA, y);
	glVertex2f(x + STAR_LINE_DELTA, y);

	//vertical line
	glVertex2f(x, y - STAR_LINE_DELTA);
	glVertex2f(x, y + STAR_LINE_DELTA);

	glEnd();
}

//Draws a circle
void DrawCircle(float center_x, float center_y, float radius)
{
	glBegin(GL_POLYGON);
	//draw all the upper right quadrent of the circle
	//iterating x from right corner to middle point
	//and calculating the height using trigo
	for (float i = radius; i >= 0; i -= 0.0002f)
	{
		float calc_alpha = acosf(i / radius);//calcualte triangle angle
		float calc_y = center_y + sinf(calc_alpha) * radius;//use angle to calculate height

		glVertex2f(center_x + i, calc_y);
	}
	glVertex2f(center_x, center_y + radius);

	//draw all the upper left quadrent of the circle
	for (float i = 0; i <= radius; i += 0.0002f)
	{
		float calc_alpha = acosf(i / radius);
		float calc_y = center_y + sinf(calc_alpha) * radius;

		glVertex2f(center_x - i, calc_y);
	}
	glVertex2f(center_x - radius, center_y);

	//draw all the upper left quadrent of the circle
	for (float i = radius; i >= 0; i -= 0.0002f)
	{
		float calc_alpha = acosf(i / radius);
		float calc_y = center_y - sinf(calc_alpha) * radius;

		glVertex2f(center_x - i, calc_y);
	}
	glVertex2f(center_x, center_y - radius);

	//draw all the upper left quadrent of the circle
	for (float i = 0; i <= radius; i += 0.0002f)
	{
		float calc_alpha = acosf(i / radius);
		float calc_y = center_y - sinf(calc_alpha) * radius;

		glVertex2f(center_x + i, calc_y);
	}
	glEnd();
}


//Draw tree at position
void DrawTree(float base_x, float base_y)
{
	glColor3f(0.6f, 0.29f, 0.0);
	glRectf(base_x, base_y, base_x + TREE_BARK_WIDTH, base_y + TREE_BARK_HEIGHT);

	glColor3f(0.0f, 0.29f, 0.0);
	DrawCircle(base_x + TREE_BARK_WIDTH / 2.0f, base_y + TREE_BARK_HEIGHT + 0.005, 0.01);
}

//Draws text at the given position
void DrawText(const char* text, int text_length, void* font, GLfloat x_pos, GLfloat y_pos)
{
	glRasterPos2f(x_pos, y_pos);
	//glTranslatef(x_pos,y_pos,1.0f);


	for (int i = 0; i < text_length; i++)
	{
		glutBitmapCharacter(font, text[i]);
	}
}

//button class
void MyBasicButton::Draw()
{
	//Draw rect
	glColor3f(this->color_red, this->color_green, this->color_blue);
	glRectf(this->pos_t1x, this->pos_t1y, this->pos_t2x, this->pos_t2y);
	if (text.length() > 0)
	{
		//Draw text
		glColor3f(1.0f, 1.0f, 1.0f);//write in white
		DrawText(text.c_str(), text.length(), GLUT_BITMAP_TIMES_ROMAN_10, pos_t1x + (pos_t2x - pos_t1x) / 2 - (text.length() * 0.003), pos_t1y + (pos_t2y - pos_t1y) / 2);//Trying to make the text in the middle of the button, not perfect.
	}
}

void MyBasicButton::SetColor(float red, float green, float blue)
{
	this->color_red = red;
	this->color_green = green;
	this->color_blue = blue;
}

/// <summary>
/// 
/// </summary>
/// <param name="pos_t1x">Bottom rect bottom left corner points x</param>
/// <param name="pos_t1y">Bottom rect bottom left corner points y</param>
/// <param name="pos_t2x">Bottom rect top right corner points x</param>
/// <param name="pos_t2y">Bottom rect top right corner points x</param>
/// <param name="color_red">button color red component float_vec3 format</param>
/// <param name="color_green">button color green component float_vec3 format</param>
/// <param name="color_blue">button color blue component float_vec3 format</param>
/// <param name="onClick_Callback">onclick callback function</param>
/// <param name="text">text opn button</param>
MyBasicButton::MyBasicButton(float pos_t1x, float pos_t1y, float pos_t2x, float pos_t2y, float color_red, float color_green, float color_blue, void(*onClick_Callback)(), std::string text)
{
	this->pos_t1x = pos_t1x;
	this->pos_t1y = pos_t1y;
	this->pos_t2x = pos_t2x;
	this->pos_t2y = pos_t2y;
	this->color_red = color_red;
	this->color_green = color_green;
	this->color_blue = color_blue;
	this->ClickedCallback = onClick_Callback;
	this->text = text;
}


MyBasicButton::~MyBasicButton()
{
	//no pointers to free here, nothing to clean up
}

void MyBasicButton::CheckClick(float x, float y)
{
	//check if click is on the button
	if (x >= pos_t1x && x <= pos_t2x && y >= pos_t1y && y <= pos_t2y)
	{
		if (this->ClickedCallback != nullptr)
		{
			ClickedCallback();

		}
	}
}