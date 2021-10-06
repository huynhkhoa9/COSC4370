/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "./freeglut-3.2.1/include/GL/freeglut.h"

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0,1,4,1};
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1() {
    // TODO: Your code here!
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  
  float radius = 1.25f;
  float teapotSize = 0.25f;

  for(double i = 0.0f; i < 2 * 3.14f; i += (2*3.14f/10) )
  {
    glPushMatrix();
    glTranslatef(cos(i) * radius,sin(i) * radius, 0);
    glRotatef(i * 180 / 3.14f, 0.0f, 0.0f, 1.0f);
    glutSolidTeapot(teapotSize);

    glPopMatrix();
  }

  glPopMatrix();
}

void problem2() 
{
    // TODO: Your code here!
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  double cubeSize = 0.5f;
  int columns = 15;

  for( float i = 0.0f; i < columns; i++ )
  {
    double value = 0.01f*pow(i, 2);
    
    glPushMatrix();
    glTranslatef((i-7.5f)/2.0f, (value/4) + cubeSize/2.0f , 0.0f);
    glScalef(1.0f, value+1, 1.0f);
    glutSolidCube(cubeSize);
    glPopMatrix();
  }

  glPopMatrix();
}

void problem3() {
    // TODO: Your code here!
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  double teapotSize = 0.25f;

  int eventRow = 6;
  int oddRow = 5;

  for(int r = 0; r < 3; r++)
  {
    for(int i = 0; i < eventRow; i++)
    {
      glPushMatrix();
      glTranslatef(i-(eventRow/2)+0.5f, (r * 1.05f)-1.5f, 0.0f);
      glutSolidTeapot(teapotSize);
      glPopMatrix();
    }

    for(int i = 0; i < oddRow; i++)
    {
      glPushMatrix();
      glTranslatef(i-(oddRow/2), ((r + 0.5f) * 1.05f)-1.5f, 0.0f);
      glutSolidTeapot(teapotSize);
      glPopMatrix();
    }

    oddRow -= 2;
    eventRow-= 2;
  }
    
  glPopMatrix();
}

void problem4() 
{
    // TODO: Your code here!
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  float radius = 1.25f;
  float teapotSize = 0.25f;
  float z = 0.0f;
  
  glRotatef(75, 0, 1, 0);
  glTranslatef(0, 0 , -5);
  
  for(double i = 0.0f; i < 6 * 3.14f; i += (2*3.14f/20) )
  {
    glPushMatrix();
    glTranslatef(cos(i) * radius,sin(i) * radius, z);
    glRotatef(i * 180 / 3.14f, 0.0f, 0.0f, 1.0f);
    glutSolidCube(teapotSize);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(cos(i + 3.14f) * radius,sin(i + 3.14f) * radius, z);
    glRotatef(i * 180 / 3.14f, 0.0f, 0.0f, 1.0f);
    glutSolidCube(teapotSize);
    glPopMatrix();

        z+= 0.125f;
  }
  
  glPopMatrix();
}

void display() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
		glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(1,0,0); // x axis
		glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,1,0); // y axis
		glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,windowWidth,windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot,0,1,0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();
	if (curProblem == 4) problem4();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0])*.1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1,(y-lastPos[1])*.1);
	}


	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	curProblem = key-'0';
    if (key == 'q' || key == 'Q' || key == 27){
        exit(0);
    }
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
