#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int h, k, r;

void plot(GLint x, GLint y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void draw(int h, int k, int x, int y)
{
	plot(h + x, k + y);
	plot(h + x, k - y);
	plot(h - x, k + y);
	plot(h - x, k - y);
	plot(h + y, k + x);
	plot(h + y, k - x);
	plot(h - y, k + x);
	plot(h - y, k - x);
}

void circle(int h, int k, int r)
{
	for (int i = 0; i <= 45 * r; i++)
	{
		float theta = (i / (180.0 * r)) * acos(-1);
		int x = r * cos(theta), y = r * sin(theta);
		draw(h, k, x, y);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
	circle(h, k, r);
	glFlush();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, 100, -50, 100);
}

int main(int argc, char **argv)
{
	printf ("Enter the center: ");
	scanf("%d %d", &h, &k);
	printf ("Enter the radius: ");
	scanf("%d", &r);
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Circle: Parametric Equation");
    glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
