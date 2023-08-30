#include <gl/glut.h>   
#include <stdio.h>
#include <math.h>

#define	PI	3.1415926

float	radius, theta, phi;
float	offset = 3.0;
float	right = 90.0, right_move = 0.0;

GLfloat		vertices[][3] = {
	{ -1.0, -1.0,  1.0 },	// 0 
	{ -1.0,  1.0,  1.0 },	// 1
	{ 1.0,  1.0,  1.0 },	// 2
	{ 1.0, -1.0,  1.0 },	// 3
	{ -1.0, -1.0, -1.0 },	// 4
	{ -1.0,  1.0, -1.0 },	// 5
	{ 1.0,  1.0, -1.0 },	// 6
	{ 1.0, -1.0, -1.0 } };	// 7

GLfloat		colors[][3] = {
	{ 1.0, 0.0, 0.0 },	// red
	{ 1.0, 1.0, 1.0 },	// white
	{ 1.0, 1.0, 0.0 },	// yellow
	{ 0.0, 1.0, 0.0 },	// green
	{ 0.0, 0.0, 1.0 },	// blue
	{ 1.0, 0.0, 1.0 } };	// magenta

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
	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(3, 0, 4, 7);
	polygon(1, 2, 6, 5);
	polygon(4, 5, 6, 7);
	polygon(5, 4, 0, 1);
}

void init(void)
{
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	radius = 5.0;
	theta = 0.0;
	phi = 0.0;

	glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 20.0);
}

void axis(void) {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // x√‡ 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); // y√‡ 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);

	glColor3f(0.0, 0.0, 1.0); // z√‡ 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();
}

void camera(void) {
	float	x, y, z;

	x = radius * cos(theta) * cos(phi);
	y = radius * sin(theta) * cos(phi);
	z = radius * sin(phi);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

void multi_cube(void) {

	/* right arm */
	glPushMatrix();
	glTranslatef(0.0, 0.6 * offset, 0.8 + right_move);
	glRotatef(right, 1.0, 0.0, 0.0);
	glScalef(0.4, 0.3, 0.8);
	cube();
	glPopMatrix();

	/* left arm */
	glPushMatrix();
	glTranslatef(0.0, -0.6 * offset, 0.8);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glScalef(0.4, 0.3, 0.8);
	cube();
	glPopMatrix();

	/* head */
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.5*offset);
	glScalef(0.7, 0.7, 0.7);
	cube();
	glPopMatrix();

	/* left leg */
	glPushMatrix();
	glTranslatef(0.0, 0.5, -0.75 * offset);
	glScalef(0.4, 0.4, 1.0);
	cube();
	glPopMatrix();

	/* right leg */
	glPushMatrix();
	glTranslatef(0.0, -0.5, -0.75 * offset);
	glScalef(0.4, 0.4, 1.0);
	cube();
	glPopMatrix();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera();
	axis();

	cube();
	multi_cube();

	glFlush();
	glutSwapBuffers();
}

void special_key(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:		theta += 0.01;
		break;
	case GLUT_KEY_RIGHT:	theta -= 0.01;
		break;
	case GLUT_KEY_UP:		phi += 0.01;
		break;
	case GLUT_KEY_DOWN:		phi -= 0.01;
		break;
	default: break;
	}
	glutPostRedisplay();
}

void Mykey(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':				radius += 0.1;
		break;
	case 's':				radius -= 0.1;
		break;
	case 'q':				right += 1.0; right_move += 0.01;
		break;
	case 'w':				right -= 1.0; right_move -= 0.01;
		break;

	default: break;
	}
	glutPostRedisplay();
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("cube with a rotating camera");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special_key);
	glutKeyboardFunc(Mykey);
	glutIdleFunc(display);
	glutMainLoop();
}



