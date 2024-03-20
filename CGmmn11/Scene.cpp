#include "Scene.h"

int AspectRatioNumerator;
int AspectRatioDenominator;
int CurrentSceneWidth = 800;
int CurrentSceneHeight = 600;

void DrawTree(int x, int y)
{

}

void DrawTrees()
{


}

void DrawBackgound()
{
	//grass
	for (float i = 0.0f; i < 0.4f; i += 0.001)
	{
		glColor3f(0.0f, 0.3f + i, 0.0f);
		glRectf(0.0f, 0.0f + i, 1.0f, i + 0.001);
	}

	//Night sky
	for (float i = 0.4f; i < 1.0f; i += 0.001)
	{
		glColor3f(0.0f, 0.0, 1.0f - i);
		glRectf(0.0f, 0.0f + i, 1.0f, i + 0.001);
	}

	//white rect for test
	glColor3f(0.8f, 0.8f, 0.8f);
	glRectf(0.4f, 0.4f, 0.6f, 0.6f);

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

	glViewport((CurrentSceneWidth - finalW) / 2, (CurrentSceneHeight - finalH) / 2, finalW, finalH);
}
//set callbacks
void DisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	FixAspectRatio();

	DrawBackgound();

	glutSwapBuffers();
}

void ReshapeCallback(int w, int h)
{
	CurrentSceneWidth = w;
	CurrentSceneHeight = h;

	glutPostRedisplay();
}

void MouseEventCallback(int button, int state, int x, int y)
{

	if (!state)
		glutPostRedisplay();
}

void KeyboardEventCallback(unsigned char c, int x, int y)
{

	switch (c)
	{
	case 'q':
	case 'Q':
		exit(0);
	}

}

void myInit(int argc, char** argv)
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

	//gl init stuff
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}

//set system/input events
void setEvents()
{
	glutDisplayFunc(DisplayCallback);
	glutReshapeFunc(ReshapeCallback);
	glutMouseFunc(MouseEventCallback);//keybord so user could exist
	glutKeyboardFunc(KeyboardEventCallback);
}

//start play my beautiful scene
void RunScene(int argc, char** argv)
{
	myInit(argc, argv);
	setEvents();
	glutMainLoop();
}
