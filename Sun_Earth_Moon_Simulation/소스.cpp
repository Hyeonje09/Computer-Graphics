#include <Windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)

#define		PI	3.1415926

int			Width = 800;
int			Height = 800;

float		sun_radius = 50.0, earth_radius = 10.0, moon_radius = 5.0;

float		earthRotation = 0.0, moonRotation = 0.0;

float		earth_rotation_speed = 0.005;
float		moon_rotation_speed = 0.03;
/* 기존에 설정된 earth_rotation_speed = 0.2, moon_rotation_speed = 2로 설정했을 경우 컴퓨터에서
공전이 너무 빨리 돼서 0.005, 0.03으로 고침.*/

void init(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0 * Width / 2.0, Width / 2.0, -1.0 * Height / 2.0, Height / 2.0);
}

void Draw_Circle(float c_radius) {
	float	delta;
	int		num = 36;

	delta = 2 * PI / num;
	glBegin(GL_POLYGON);
	for (int i = 0; i < num; i++)
		glVertex2f(c_radius * cos(delta * i), c_radius * sin(delta * i));
	glEnd();
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0); // Set display-window color to black.

	earthRotation += earth_rotation_speed;
	moonRotation += moon_rotation_speed;

	/***********코드 작성하기 ***************/

	// 태양 : 빨간색의 구 
	glColor3f(1.0, 0.0, 0.0);	
	Draw_Circle(sun_radius);

	// 지구 : 초록색의 구 
	glPushMatrix();
	
	glRotatef(earthRotation, 0.0, 0.0, 1.0);
	glTranslatef(150.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	Draw_Circle(earth_radius);

	// 달   : 노랑색의 구 
	glRotatef(moonRotation, 0.0, 0.0, 1.0);
	glTranslatef(40.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	Draw_Circle(moon_radius);
	
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Solar System");
	init();
	glutDisplayFunc(RenderScene);
	glutIdleFunc(RenderScene);
	glutMainLoop();
}

