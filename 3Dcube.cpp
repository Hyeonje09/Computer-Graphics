#include <gl/glut.h>
#include <gl/gl.h>
#include <stdio.h>
#include <math.h>


#define	PI	3.1415926
float radius = 10.0, theta = PI/4 , phi = PI/4; //theta : �浵 phi : ����
float cx, cy, cz;
float v = 1.0; //���⺤�� z��

GLfloat		vertices[][3] = {
		{ -1.0, -1.0,  1.0 },		// 0 
		{ -1.0,  1.0,  1.0 },		// 1
		{ 1.0,  1.0,  1.0 },		// 2
		{ 1.0, -1.0,  1.0 },		// 3
		{ -1.0, -1.0, -1.0 },		// 4
		{ -1.0,  1.0, -1.0 },		// 5
		{ 1.0,  1.0, -1.0 },		// 6
		{ 1.0, -1.0, -1.0 } };		// 7

GLfloat		colors[][3] = {
		{ 1.0, 0.0, 0.0 },			// red
		{ 0.0, 1.0, 0.0 },			// green 
		{ 1.0, 1.0, 0.0 },			// yellow
		{ 1.0, 1.0, 1.0 },			// white
		{ 0.0, 0.0, 1.0 },			// blue
		{ 1.0, 0.0, 1.0 } };		// magenta

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
	polygon(4, 5, 6, 7);
	polygon(1, 2, 6, 5);
	polygon(5, 4, 0, 1);
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 20.0);
}

void axis(void) {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // x�� 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); // y�� 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);

	glColor3f(0.0, 0.0, 1.0); // z�� 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();
}

void framebuffer_reset(void) {
	glClearColor(0.6, 0.6, 0.6, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

void camera(void) {
	cx = radius * cos(phi) * cos(theta);
	cy = radius * cos(phi) * sin(theta);
	cz = radius * sin(phi);	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cx, cy, cz, 0.0, 0.0, 0.0, 0.0, 0.0, v); 
	//cx, cy, cz : ī�޶� ��ǥ v : ī�޶� ���⺤�� +1 = up, -1 = down
	// 3, 4, 5��° ���� : ������
}

void display(void) {
	framebuffer_reset();

	camera();
	glColor3f(1.0, 1.0, 0.0);
	cube();

	axis();

	glFlush();
	glutSwapBuffers();
}

void myKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_LEFT: theta -= 0.1; break;
	case GLUT_KEY_RIGHT: theta += 0.1; break;
	case GLUT_KEY_UP: phi += 0.1; break;
	case GLUT_KEY_DOWN: phi -= 0.1; break;	
	default: break;
	}
	glutPostRedisplay();

	if (phi >= 2 * PI) phi -= 2 * PI; //phi ���� 360���� �Ѿ��� ���
	else if (phi < 0) phi += 2 * PI; //phi ���� ���̳ʽ� ������ ���

	if (phi >= 3 * PI / 2) v = 1;	//phi ���� 270�� �̻��� ��� ���⺤�� : 1

	else if (phi >= PI / 2) v = -1;	//phi ���� 90�� �̻��� ��� ���⺤�� : -1
	
	else v = 1; //pi ���� 90�� �̸��� ��� ���⺤�� : 1
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3D_cube");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(myKey);
	glutMainLoop();
}
