#include <gl/glut.h>  
#include <math.h>

#define		PI	3.1415926
#define		N	36
#define		M	18 

static int	sphere_drawing_type = 0;

float	sphere_radius = 2.0;
float	camera_radius = 5.0;
float	camera_theta = 0.0;
float	camera_phi = 0.0;

float	ver[N][M + 1][3];


/* 광원의 데이터 값 */
float	light_position[] = { -7.0, 5.0, 5.0, 1.0 };		// 좌표계	
float	light_ambient[] = { 0.0, 0.3, 0.0, 1.0 };		// 주변광(가장 어두운 부분) -> (R, G, B)
float	light_diffuse[] = { 3.0, 2.0, 0.0, 1.0 };		// 분산광(전체적인 부분) -> (R, G, B)
float	light_specular[] = { 1.0, 0.0, 0.0, 1.0 };		// 반사광(밝게 빛나는 부분) -> (R, G, B)

void Vertex_Generation(void) {
	float	theta, phi;
	float	delta_theta, delta_phi;
	float	start_theta, start_phi;

	start_theta = 0.0;
	delta_theta = 2.0 * PI / N;

	start_phi = -1.0 * PI / 2.0;
	delta_phi = PI / M;

	for (int j = 0; j <= M; j++) {
		for (int i = 0; i < N; i++) {
			theta = start_theta + i * delta_theta;
			phi = start_phi + j * delta_phi;


			/* Scale */
			ver[i][j][0] = sphere_radius * cos(phi) * cos(theta);
			ver[i][j][1] = sphere_radius * cos(phi) * sin(theta);
			ver[i][j][2] = sphere_radius * sin(phi);
				
			/*
				Q1. 반지름을 키웠는데, 빛이 이상하다. 왜일까..?
				A1. 반지름을 키웠으므로 법선벡터가 2배가 되었다. 우리는 원래 법선벡터로 단위벡터를 사용함.
			*/

			/* Position
			ver[i][j][0] = sphere_radius + cos(phi) * cos(theta);
			ver[i][j][1] = sphere_radius + cos(phi) * sin(theta);
			ver[i][j][2] = sphere_radius + sin(phi);
	
				Q1. position만 옮겼는데, 빛이 이상하다. 왜일까..?
				A1. 위치를 바꾸면 법선벡터가 제대로 계산되지 않는다. 원래 원점에서 시작했던 법선벡터가 옮겨진 지점으로 벡터 방향이 달라짐(glNormal 안에 vertex 위치 정보를 그대로 사용함)
				Q2. 그럼 위치를 바꿔도 제대로 된 결과를 얻는 방법은?
				A2.	법선벡터를 제대로 계산하자. -> How? : 실제로 짜보기..?
				
				- 법선 벡터를 제대로 계산하는 방법

			*/
		}
	}
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


void Draw_Wire_Sphere(void) {
	glColor3f(1.0, 0.0, 0.0);
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(1.01 * ver[i][j][0], 1.01 * ver[i][j][1], 1.01 * ver[i][j][2]);
			glVertex3f(1.01 * ver[i + 1][j][0], 1.01 * ver[i + 1][j][1], 1.01 * ver[i + 1][j][2]);
			glVertex3f(1.01 * ver[i + 1][j + 1][0], 1.01 * ver[i + 1][j + 1][1], 1.01 * ver[i + 1][j + 1][2]);
			glVertex3f(1.01 * ver[i][j + 1][0], 1.01 * ver[i][j + 1][1], 1.01 * ver[i][j + 1][2]);
			glEnd();
		}
	}
}

void Draw_Wire_Sphere1(void) {
	glColor3f(1.0, 0.0, 0.0);
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(1.01 * ver[i][j][0], 1.01 * ver[i][j][1], 1.01 * ver[i][j][2]);
			glVertex3f(1.01 * ver[(i + 1) % N][j][0], 1.01 * ver[(i + 1) % N][j][1], 1.01 * ver[(i + 1) % N][j][2]);
			glVertex3f(1.01 * ver[(i + 1) % N][j + 1][0], 1.01 * ver[(i + 1) % N][j + 1][1], 1.01 * ver[(i + 1) % N][j + 1][2]);
			glVertex3f(1.01 * ver[i][j + 1][0], 1.01 * ver[i][j + 1][1], 1.01 * ver[i][j + 1][2]);
			glEnd();
		}
	}
}


void Sphere(void) {
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glBegin(GL_POLYGON);
			glNormal3fv(ver[i][j]);
			glVertex3fv(ver[i][j]);
			glNormal3fv(ver[(i + 1) % N][j]);
			glVertex3fv(ver[(i + 1) % N][j]);
			glNormal3fv(ver[(i + 1) % N][j + 1]);
			glVertex3fv(ver[(i + 1) % N][j + 1]);
			glNormal3fv(ver[i][j + 1]);
			glVertex3fv(ver[i][j + 1]);
			glEnd();

		}
	}
}

void Sphere1(void) {
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_POLYGON);
			glVertex3fv(ver[i][j]);
			glVertex3fv(ver[i + 1][j]);
			glVertex3fv(ver[i + 1][j + 1]);
			glVertex3fv(ver[i][j + 1]);
			glEnd();
		}
	}
	Draw_Wire_Sphere();
}

void Sphere2(void) {
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_POLYGON);
			glVertex3fv(ver[i][j]);
			glVertex3fv(ver[(i + 1) % N][j]);
			glVertex3fv(ver[(i + 1) % N][j + 1]);
			glVertex3fv(ver[i][j + 1]);
			glEnd();
		}
	}
	Draw_Wire_Sphere1();
}

void Sphere3(void) {
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glColor3f(cos(exp(i + j) * sin(i + j)), sin(j * sin(i * j)), sin(i * j));
			glBegin(GL_POLYGON);
			glVertex3fv(ver[i][j]);
			glVertex3fv(ver[(i + 1) % N][j]);
			glVertex3fv(ver[(i + 1) % N][j + 1]);
			glVertex3fv(ver[i][j + 1]);
			glEnd();
		}
	}
}


void init(void)
{
	glShadeModel(GL_SMOOTH);      //GL_FLAT 

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glMaterialfv(GL_FRONT, GL_SPECULAR, light_specular);
	glMateriali(GL_FRONT, GL_SHININESS, 50);

	glEnable(GL_DEPTH_TEST);
	Vertex_Generation();
}


void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 1.0, 1000);
}


void camera_setting(void)
{
	float	x, y, z;

	x = camera_radius * cos(camera_theta) * cos(camera_phi);
	y = camera_radius * sin(camera_theta) * cos(camera_phi);
	z = camera_radius * sin(camera_phi);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}
void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera_setting();
	axis();

	switch (sphere_drawing_type) {
	case 0: Sphere(); break;
	case 1: Sphere1(); break;
	case 2: Sphere2(); break;
	case 3: Sphere3(); break;
	default:break;
	}

	glFlush();

}


void special_key(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:		camera_theta -= 0.01; 	break;
	case GLUT_KEY_RIGHT:	camera_theta += 0.01;	break;
	case GLUT_KEY_UP:		camera_phi += 0.01;		break;
	case GLUT_KEY_DOWN:		camera_phi -= 0.01;		break;
	default: break;
	}
	glutPostRedisplay();
}

void mykey(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':	camera_radius += 0.1; break;
	case 's':	camera_radius -= 0.1; break;
	case '0':   sphere_drawing_type = 0;	break;
	case '1':   sphere_drawing_type = 1;	break;
	case '2':   sphere_drawing_type = 2;	break;
	case '3':   sphere_drawing_type = 3;	break;
	default: break;
	}
	glutPostRedisplay();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("2D_Sphere");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(mykey);
	glutSpecialFunc(special_key);
	glutMainLoop();
}