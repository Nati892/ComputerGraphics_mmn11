#include "Scene.h"

#define STAR_LINE_DELTA 0.004
#define GRASS_HEIGHT 0.4f
#define GRADIANT_INTERVAL 0.001f
#define AmountOfStars 60
#define MOON_RADIUS 0.05f
#define PI 3.14159265f

int AspectRatioNumerator;
int AspectRatioDenominator;
int CurrentSceneWidth = 800;
int CurrentSceneHeight = 600;
float StarPositions[AmountOfStars * 2];

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

	//white rect for test
	glColor3f(0.8f, 0.8f, 0.8f);
	glRectf(0.4f, 0.4f, 0.6f, 0.6f);

}

void InitStarValues()
{
	float rand_num = 0.0f;
	for (int i = 0; i < AmountOfStars * 2; i++)
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

void DrawFullMoon(float x, float y)
{
	glColor3f(0.85f, 0.85f, 0.85f);//set moon color to be bright but not as bright as the stars
	glBegin(GL_POLYGON);

	//draw all the upper right quadrent of the circle
	//iterating x from right corner to middle point
	//and calculating the height using trigo
	std::cout << "start" << std::endl;
	for (float i = MOON_RADIUS; i >= 0; i -= 0.0005f)
	{
		float calc_alpha = acosf(i / MOON_RADIUS);
		float calc_y = y + sinf(calc_alpha) * MOON_RADIUS;

		glVertex2f(x + i, calc_y);
	}
	glVertex2f(x , y+MOON_RADIUS);

	//draw all the upper left quadrent of the circle
	for (float i = 0; i <= MOON_RADIUS; i += 0.0005f)
	{
		float calc_alpha = acosf(i / MOON_RADIUS);
		float calc_y = y + sinf(calc_alpha) * MOON_RADIUS;

		glVertex2f(x - i, calc_y);
	}
	glVertex2f(x - MOON_RADIUS, y);

	//draw all the upper left quadrent of the circle
	for (float i = MOON_RADIUS; i >= 0; i -= 0.0005f)
	{
		float calc_alpha = acosf(i / MOON_RADIUS);
		float calc_y = y - sinf(calc_alpha) * MOON_RADIUS;

		glVertex2f(x - i, calc_y);
	}
	glVertex2f(x , y-MOON_RADIUS);

	//draw all the upper left quadrent of the circle
	for (float i = 0; i <= MOON_RADIUS; i += 0.0005f)
	{
		float calc_alpha = acosf(i / MOON_RADIUS);
		float calc_y = y - sinf(calc_alpha) * MOON_RADIUS;

		glVertex2f(x + i, calc_y);
	}
	glEnd();
}

//draws all the stars on the night's sky, random position
void DrawStars()
{
	for (int i = 0; i < AmountOfStars; i++)
	{
		float rand_x = StarPositions[i * 2];
		float rand_y = StarPositions[i * 2 + 1];
		DrawStar(rand_x, rand_y);
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
	DrawFullMoon(0.2f, 0.85f);

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
