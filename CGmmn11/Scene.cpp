#include "Scene.h"

#define STAR_LINE_DELTA 0.004
#define GRASS_HEIGHT 0.4f
#define GRADIANT_INTERVAL 0.001f
#define AMOUNT_OF_STARS 60
#define AMOUNT_OF_TREES 40
#define MOON_RADIUS 0.05f
#define PI 3.14159265f
#define TREE_BARK_HEIGHT 0.05
#define TREE_BARK_WIDTH 0.005

int AspectRatioNumerator;
int AspectRatioDenominator;
int CurrentSceneWidth = 800;
int CurrentSceneHeight = 600;
float StarPositions[AMOUNT_OF_STARS * 2];
float TreePositions[AMOUNT_OF_TREES * 2];

void DrawBackgound()
{
	//gradiant grass
	for (float i = 0.0f; i < GRASS_HEIGHT; i += GRADIANT_INTERVAL)
	{
		glColor3f(0.0f, 0.3f + i, 0.0f);
		glRectf(0.0f, 0.0f + i, 1.0f, i + GRADIANT_INTERVAL);
	}

	//Night sky
	for (float i = GRASS_HEIGHT; i < 1.0f; i += GRADIANT_INTERVAL)
	{
		glColor3f(0.0f, 0.0, 1.0f - i);
		glRectf(0.0f, 0.0f + i, 1.0f, i + GRADIANT_INTERVAL);
	}


}

void InitStarValues()
{
	float rand_num = 0.0f;
	for (int i = 0; i < AMOUNT_OF_STARS * 2; i++)
	{
		if (i % 2 == 0)
		{
			rand_num = RandInRange(0, 1.0f);//star's x_pos
		}
		else
		{
			rand_num = RandInRange(GRASS_HEIGHT, 1.0f);//star's y_pos
		}
		StarPositions[i] = rand_num;
	}
}

void InitTreeValues()
{
	float rand_num = 0.0f;
	for (int i = 0; i < AMOUNT_OF_TREES * 2; i++)
	{
		if (i % 2 == 0)
		{
			rand_num = RandInRange(0, 1.0f);//tree's x_pos
		}
		else
		{
			rand_num = RandInRange(0, GRASS_HEIGHT);//tree's y_pos
		}
		TreePositions[i] = rand_num;
	}
}

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
	for (float i = radius; i >= 0; i -= 0.0005f)
	{
		float calc_alpha = acosf(i / radius);//calcualte triangle angle
		float calc_y = center_y + sinf(calc_alpha) * radius;//use angle to calculate height

		glVertex2f(center_x + i, calc_y);
	}
	glVertex2f(center_x, center_y + radius);

	//draw all the upper left quadrent of the circle
	for (float i = 0; i <= radius; i += 0.0005f)
	{
		float calc_alpha = acosf(i / radius);
		float calc_y = center_y + sinf(calc_alpha) * radius;

		glVertex2f(center_x - i, calc_y);
	}
	glVertex2f(center_x - radius, center_y);

	//draw all the upper left quadrent of the circle
	for (float i = radius; i >= 0; i -= 0.0005f)
	{
		float calc_alpha = acosf(i / radius);
		float calc_y = center_y - sinf(calc_alpha) * radius;

		glVertex2f(center_x - i, calc_y);
	}
	glVertex2f(center_x, center_y - radius);

	//draw all the upper left quadrent of the circle
	for (float i = 0; i <= radius; i += 0.0005f)
	{
		float calc_alpha = acosf(i / radius);
		float calc_y = center_y - sinf(calc_alpha) * radius;

		glVertex2f(center_x + i, calc_y);
	}
	glEnd();
}

void DrawFullMoon(float center_x, float center_y, float radius)
{
	glColor3f(0.85f, 0.85f, 0.85f);//set moon color to be bright but not as bright as the stars
	DrawCircle(center_x, center_y, radius);

}

//Draws all the stars on the night's sky, random position
void DrawStars()
{
	for (int i = 0; i < AMOUNT_OF_STARS; i++)
	{
		float rand_x = StarPositions[i * 2];
		float rand_y = StarPositions[i * 2 + 1];
		DrawStar(rand_x, rand_y);
	}
}

//Draw tree at position
void DrawTree(float base_x, float base_y)
{
	glColor3f(0.6f, 0.29f, 0.0);
	glRectf(base_x, base_y, base_x + TREE_BARK_WIDTH, base_y + TREE_BARK_HEIGHT);

	glColor3f(0.0f, 0.29f, 0.0);
	DrawCircle(base_x + TREE_BARK_WIDTH / 2.0f, base_y + TREE_BARK_HEIGHT + 0.005, 0.01);
}

//Draws all the stars on the night's sky, random position
void DrawTrees()
{
	for (int i = 0; i < AMOUNT_OF_TREES; i++)
	{
		float rand_x = TreePositions[i * 2];
		float rand_y = TreePositions[i * 2 + 1];
		DrawTree(rand_x, rand_y);
	}
}



//fixes the current aspect ratio
void FixAspectRatio()
{
	int finalW = CurrentSceneWidth;
	int finalH = CurrentSceneHeight;

	//calculate current aspect ratio
	double WinAR = (double)CurrentSceneWidth / (double)CurrentSceneHeight;
	double RefAR = (double)AspectRatioNumerator / (double)AspectRatioDenominator;

	//if window width is highr in ratio then fix it(lower it)
	if (WinAR > RefAR)
	{
		finalW = ((double)AspectRatioNumerator * (double)CurrentSceneHeight) / (double)AspectRatioDenominator;
	}

	//if window Height is highr in ratio then fix it(lower it)
	if (WinAR < RefAR)
	{
		finalH = ((double)AspectRatioDenominator * (double)CurrentSceneWidth) / (double)AspectRatioNumerator;
	}

	//Center view port in window
	int StartPos_X = (CurrentSceneWidth - finalW) / 2;
	int StartPos_Y = (CurrentSceneHeight - finalH) / 2;

	glViewport(StartPos_X, StartPos_Y, finalW, finalH);
}

//Callbacks

//Redraw callback
void DisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	FixAspectRatio();

	DrawBackgound();
	DrawStars();
	DrawFullMoon(0.2f, 0.85f, MOON_RADIUS);
	DrawTrees();
	glutSwapBuffers();
}

//window resize callback
void ReshapeCallback(int w, int h)
{
	CurrentSceneWidth = w;
	CurrentSceneHeight = h;

	glutPostRedisplay();
}

//Mouse events
void MouseEventCallback(int button, int state, int x, int y)
{

}

//Keybard events
void KeyboardEventCallback(unsigned char c, int x, int y)
{

	switch (c)
	{
	case 'q':
	case 'Q':
		exit(0);
	}

}

void MyInit(int argc, char** argv)
{
	//call init on glut
	glutInit(&argc, argv);

	//window stuff
	CurrentSceneWidth = 800;
	CurrentSceneHeight = 600;
	AspectRatioNumerator = CurrentSceneWidth;
	AspectRatioDenominator = CurrentSceneHeight;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(CurrentSceneWidth, CurrentSceneHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Maman11:Towers of annoying");
	InitStarValues();
	InitTreeValues();
	//gl init stuff
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}

//set system/input events
void SetEvents()
{
	glutDisplayFunc(DisplayCallback);
	glutReshapeFunc(ReshapeCallback);
	glutMouseFunc(MouseEventCallback);//keybord so user could exist
	glutKeyboardFunc(KeyboardEventCallback);
}

//start play my beautiful scene
void RunScene(int argc, char** argv)
{
	MyInit(argc, argv);
	SetEvents();
	glutMainLoop();
}
