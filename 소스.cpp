#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)
#include <iostream>
using namespace std;

#define		Window_Width	800
#define		Window_Height	800

int	point[100][2];
int	num = 0;
int pp = 100;

float factorial(int n) {
	float res;
	if (n > 1) res = n * factorial(n - 1);
	else res = 1.0;
	return res;
}

float combination(int n, int i) {
	float res;
	res = factorial(n) / (factorial(n - i) * factorial(i));
	return res;
}

float bernstein(int n, int i, float t) {
	float res;
	res = combination(n, i) * pow(1 - t, n - i) * pow(t, i);
	return res;
}

void Draw_Bezier_Curve(void) {
	float dt = 1.0 / pp;
	float sumx, sumy;
	float p0x = point[0][0];
	float p0y = point[0][1];

	glBegin(GL_LINE_STRIP);
	for (float time = 0; time <= 1.0; time += dt) {
		sumx = sumy = 0.0;
		for (int i = 0; i < num; i++) {
			sumx += bernstein(num, i, time) * point[i][0];
			sumy += bernstein(num, i, time) * point[i][1];
			p0x = sumx;
			p0y = sumy;
		}
		glVertex2f(p0x, p0y);
		glVertex2f(sumx, sumy);
	}
	sumx = point[num - 1][0];
	sumy = point[num - 1][1];
	glVertex2f(p0x, p0y);
	glVertex2f(sumx, sumy);
	glEnd();
}

void Draw_Control_Points(void) {
	glPointSize(3.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (int k = 0; k < num; k++) {
		glVertex2f(point[k][0], point[k][1]);
	}
	glEnd();
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glColor3f(1.0, 0.0, 0.0);

	if (num >= 1)
		Draw_Control_Points();
	if (num >= 2)
		Draw_Bezier_Curve();

	glFlush();
	glutSwapBuffers();
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	glLoadIdentity();
	gluOrtho2D(0, Window_Width, 0, Window_Height);
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		point[num][0] = x;
		point[num][1] = Window_Height - y;
		num++;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		num = 0;
	}
	glutPostRedisplay();
	RenderScene();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Window_Width, Window_Height);
	glutCreateWindow("Bezier Curve");
	init();
	glutDisplayFunc(RenderScene);
	glutMouseFunc(mouse);
	glutMainLoop();
}