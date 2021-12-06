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

void draw(int h, int k, int xi, int yi)
{
	plot(h + xi, k + yi);
	plot(h + xi, k - yi);
	plot(h - xi, k + yi);
	plot(h - xi, k - yi);
	plot(h + yi, k + xi);
	plot(h + yi, k - xi);
	plot(h - yi, k + xi);
	plot(h - yi, k - xi);
}

void circle(int h, int k, int r)
{
	int xi = 0, yi = r, d = 3 - 2 * r;
	while (xi <= yi)
	{
		draw(h, k, xi, yi);
		if (d < 0)
			d += 4 * xi + 6;
		else
		{
			d += 4 * (xi - yi) + 10;
			yi--;
		}
		xi++;
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
    glutCreateWindow("Circle: Breshenham's Algorithm");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}