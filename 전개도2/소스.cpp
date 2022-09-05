#include <gl/glut.h>
#include <gl/gl.h>
#include <stdio.h>
#include <math.h>
#include <Windows.h>

#define	PI	3.1415926

GLfloat		vertices[][3] = {
	{ -1.0, -1.0,  1.0 },		// 0 
{ -1.0,  1.0,  1.0 },		// 1
{ 1.0,  1.0,  1.0 },		// 2
{ 1.0, -1.0,  1.0 },		// 3
{ -1.0, -1.0, -1.0 },		// 4
{ -1.0,  1.0, -1.0 },		// 5
{ 1.0,  1.0, -1.0 },		// 6
{ 1.0, -1.0, -1.0 } 		// 7
};

GLfloat		colors[][3] = {
	{ 1.0, 0.0, 0.0 },			// red
{ 0.0, 1.0, 0.0 },			// green 
{ 1.0, 1.0, 0.0 },			// yellow
{ 1.0, 1.0, 1.0 },			// white
{ 0.0, 0.0, 1.0 },			// blue
{ 1.0, 0.0, 1.0 }			// magenta
};

int		view_type = 0;
float	c_distance, c_theta, c_phi;
float	up = 1.0;
float	movingRPlus = 0.0, movingRMinus = 0.0;
float	angle0 = 0.0, angle1 = 0.0, angle2 = 0.0, anglePlus = 0.0;
int		temp = 0, step = 1;

void myTimer(int value) {
	movingRPlus += (float)value;
	movingRMinus -= (float)value;

	if (movingRMinus > -90.0 && movingRPlus) {
		angle0 -= value; anglePlus += value;
	}
	else if (movingRMinus > -180.0) angle1 -= value;
	else if (movingRMinus > -270.0) angle2 -= value;
	glutPostRedisplay();
}

void polygon(int a, int b, int c, int d) {
	glColor3fv(colors[a]);
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void cube(void) {
	if (temp == 1) {
		glutTimerFunc(30, myTimer, 1);
	}

	glPushMatrix();

	glTranslatef(0.0, 1.0, -1.0);
	glRotatef(angle2, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.0, 1.0);
	polygon(1, 2, 6, 5);	//¿À¸¥ÂÊ

	glTranslatef(0.0, 1.0, 1.0);
	glRotatef(angle1, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.0, -1.0);
	polygon(0, 3, 2, 1);	//À­¸é

	glTranslatef(0.0, -1.0, 1.0);
	glRotatef(angle0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 1.0, -1.0);
	polygon(3, 0, 4, 7);	//¿ÞÂÊ

	glPopMatrix();

	polygon(4, 5, 6, 7);	//¾Æ·¡

	glPushMatrix();
	glTranslatef(-1.0, 0.0, -1.0);
	glRotatef(angle0, 0.0, 1.0, 0.0);
	glTranslatef(1.0, 0.0, 1.0);
	polygon(5, 4, 0, 1);	//µÞ¸é
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, 0.0, -1.0);
	glRotatef(anglePlus, 0.0, 1.0, 0.0);
	glTranslatef(-1.0, 0.0, 1.0);
	polygon(2, 3, 7, 6);	//¾Õ¸é
	glPopMatrix();
}

void init(void)
{
	c_distance = 7.0;
	c_theta = 0.3;
	c_phi = 0.4;

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 15.0);
	gluPerspective(45.0, 1.0, 1.0, 20.0);
}

void axis(void) {

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // xÃà 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); // yÃà 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);

	glColor3f(0.0, 0.0, 1.0); // zÃà 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();
}

void frame_reset(void) {
	glClearColor(0.6, 0.6, 0.6, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void camera(void) {
	float	x, y, z;
	x = c_distance * cos(c_theta) * cos(c_phi);
	y = c_distance * sin(c_theta) * cos(c_phi);
	z = c_distance * sin(c_phi);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, up);

}


void display(void)
{
	frame_reset();

	camera();
	axis();
	cube();


	glFlush();
	glutSwapBuffers();
}

void MyKey(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':			glFrontFace(GL_CCW);	break;
	case 's':			glFrontFace(GL_CW);	break;
	default:	break;
	}
	glutPostRedisplay();
}

void Special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:			c_theta -= 0.1;	break;
	case GLUT_KEY_RIGHT:		c_theta += 0.1;	break;
	case GLUT_KEY_DOWN:         c_phi -= 0.1;		break;
	case GLUT_KEY_UP:			c_phi += 0.1;		break;
	case GLUT_KEY_F1:			temp = 1; break;

	default:	break;
	}
	if (c_phi > 3.0 * PI / 2.0)
		c_phi -= 2.0 * PI;
	else if (c_phi < -3.0 * PI / 2.0)
		c_phi += 2.0 * PI;

	if (c_phi > PI / 2.0)
		up = -1.0;
	else if (c_phi < -1.0 * PI / 2.0)
		up = -1.0;
	else
		up = 1.0;

	glutPostRedisplay();


}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Magic_Cube");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(MyKey);
	glutSpecialFunc(Special);
	glutMainLoop();
	return 0;
}