#include "Scene.h"

#define PI 3.14159265f
#define GRASS_HEIGHT 0.4f
#define GRADIANT_INTERVAL 0.001f
#define AMOUNT_OF_STARS 60
#define AMOUNT_OF_TREES 40
#define MOON_RADIUS 0.05f
#define MY_NAME "Netanel Cohen Gindi"
#define MY_HEADER "Beautiful Night"


int AspectRatioNumerator;
int AspectRatioDenominator;
int currentWindowWidth;
int currentWindowHeight;
int CurrentSceneWidth = 800;
int CurrentSceneHeight = 600;
float StarPositions[AMOUNT_OF_STARS * 2];
float TreePositions[AMOUNT_OF_TREES * 2];
std::vector<MyBasicButton*> Buttons;
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

//Draws the background: grass and sky
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

//Draws the moon in the scene
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

//Draws the requested text on the top right corner of the window
void DrawHeaders()
{
	glColor3f(0.8f, 0.0f, 0.8f);//write in yellow
	DrawText(MY_HEADER, strlen(MY_HEADER), GLUT_BITMAP_HELVETICA_10, 0.87f, 0.95f);

	glColor3f(1.0f, 0.0f, 0.0f);//write in red
	DrawText(MY_NAME, strlen(MY_NAME), GLUT_BITMAP_TIMES_ROMAN_10, 0.87f, 0.9f);
}


void CleanupAndExit()
{
	while (!Buttons.empty())
	{
		auto button = Buttons.back();
		button->~MyBasicButton();
		Buttons.pop_back();
	}
	exit(0);
}

//Draws and exits button on the bottom right corner of the window
void AddExitButton(float t1_x, float t1_y, float t2_x, float t2_y, const char* text)
{
	auto exit_button = new MyBasicButton(t1_x, t1_y, t2_x, t2_y, 0.1f, 0.1f, 0.1f, CleanupAndExit, text);
	Buttons.push_back(exit_button);
}

//fixes the current aspect ratio
void FixAspectRatio()
{
	int finalW = currentWindowWidth;
	int finalH = currentWindowHeight;
	CurrentSceneWidth = currentWindowWidth;
	CurrentSceneHeight = currentWindowHeight;
	//calculate current aspect ratio
	double WinAR = (double)CurrentSceneWidth / (double)CurrentSceneHeight;
	double RefAR = (double)AspectRatioNumerator / (double)AspectRatioDenominator;

	//if window width is highr in ratio then fix it(lower it)
	if (WinAR > RefAR)
	{
		finalW = ((double)AspectRatioNumerator * (double)CurrentSceneHeight) / (double)AspectRatioDenominator;
	}
	CurrentSceneWidth = finalW;

	//if window Height is highr in ratio then fix it(lower it)
	if (WinAR < RefAR)
	{
		finalH = ((double)AspectRatioDenominator * (double)CurrentSceneWidth) / (double)AspectRatioNumerator;
	}
	CurrentSceneHeight = finalH;

	//Center view port in window
	int StartPos_X = (currentWindowWidth - finalW) / 2;
	int StartPos_Y = (currentWindowHeight - finalH) / 2;
	glViewport(StartPos_X, StartPos_Y, finalW, finalH);
}

//Redraw callback
void DisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	FixAspectRatio();

	DrawBackgound();
	DrawStars();
	DrawFullMoon(0.2f, 0.85f, MOON_RADIUS);
	DrawTrees();
	DrawHeaders();
	for (const auto& button : Buttons)
	{
		button->Draw();
	}
	glutSwapBuffers();
}

//window resize callback
void ReshapeCallback(int w, int h)
{
	currentWindowWidth = w;
	currentWindowHeight = h;


	glutPostRedisplay();
}

//Mouse events
void MouseEventCallback(int button, int state, int x, int y)
{
	if (state == 0)
		return;
	float converted_x = ((float)x - ((float)currentWindowWidth - (float)CurrentSceneWidth) / 2) / (float)CurrentSceneWidth;
	float converted_y = 1.0f - (((float)y - ((float)currentWindowHeight - (float)CurrentSceneHeight) / 2) / (float)CurrentSceneHeight);

	for (const auto& btn : Buttons)
	{
		btn->CheckClick(converted_x, converted_y);
	}
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

//my initiation function
void MyInit(int argc, char** argv)
{
	//call init on glut
	glutInit(&argc, argv);

	//window stuff
	CurrentSceneWidth = 800;
	CurrentSceneHeight = 600;
	currentWindowWidth = CurrentSceneWidth;
	currentWindowHeight = CurrentSceneHeight;

	AspectRatioNumerator = CurrentSceneWidth;
	AspectRatioDenominator = CurrentSceneHeight;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(CurrentSceneWidth, CurrentSceneHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Maman11:Towers of annoying");
	InitStarValues();
	InitTreeValues();
	AddExitButton(0.9f, 0.0f, 1.0f, 0.05f, "Exit");

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

