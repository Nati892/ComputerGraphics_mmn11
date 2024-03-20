#include "Scene.h"

//set callbacks
int CurrentSceneWidth = 800;
int CurrentSceneHeight = 600;
void DisplayCallback()
{


	glutSwapBuffers();
}

void ReshapeCallback(int w, int h)
{
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
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(CurrentSceneWidth, CurrentSceneHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Window title");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}

void setEvents()
{
	glutDisplayFunc(DisplayCallback);
	glutReshapeFunc(ReshapeCallback);
	glutMouseFunc(MouseEventCallback);//keybord so user could exist
	glutKeyboardFunc(KeyboardEventCallback);
}


void RunScene(int argc, char** argv)
{

	myInit(argc, argv);
	setEvents();
	glutMainLoop();
}