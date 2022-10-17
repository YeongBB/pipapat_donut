#include<gl/GLU.h>
#include<iostream>
#include<gl/GL.h>
#include<gl/glut.h>

#define INIT_WIN_X 400
#define INIT_WIN_Y 400
#define MAX(x,y) x>y?x:y;
#define MIN(x,y) x<y?x:y;

GLfloat inner_radious = 0.2f;
GLfloat outer_radious = 0.5f;
GLfloat scale_factor = 0.0001f;
GLint sides = 12;
GLint rings = 24;
GLfloat delta = 0.0;
void Draw();
void MyMouseMotion(int x, int y);
void MyReshape(int NewWidth, int NewHeight);
void MyMouse(int button, int state, int x, int y);
void MyTimer(int Value);
void MyTimer2(int Value);

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glutWireTorus(inner_radious, outer_radious, sides, rings);
	glFlush();
}

void MyMouseMotion(int x, int y)
{
	outer_radious += (GLfloat)(x)*scale_factor;
	outer_radious -= (GLfloat)(y)*scale_factor;
	glutPostRedisplay();
}

void MyReshape(int NewWidth, int NewHeight)
{
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)INIT_WIN_X;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)INIT_WIN_Y;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor, -1.0, 1.0);
	glRotated(70, .3, .3, .3);
}

void MyMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) rings = MIN(86, rings + 1)
		if (button == GLUT_RIGHT_BUTTON) rings = MAX(4, rings - 1)
			glutPostRedisplay();
}

void MyTimer(int Value)
{
	delta = delta + 0.001;
	outer_radious += 0.04f;
	glutPostRedisplay();
	glutTimerFunc(4, MyTimer2, 1);
}

void MyTimer2(int Value)
{
	delta = delta + 0.001;
	outer_radious -= 0.04f;
	glutPostRedisplay();
	glutTimerFunc(4, MyTimer, 1);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(INIT_WIN_X, INIT_WIN_Y);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL TEST");

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutDisplayFunc(Draw);
	glutReshapeFunc(MyReshape);
	glutMouseFunc(MyMouse);
	//glutMotionFunc(MyMouseMotion);	
	glutTimerFunc(2, MyTimer, 1);
	glutMainLoop();

	return 0;
}