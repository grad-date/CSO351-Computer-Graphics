#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;
int h, k, r;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, 100, -50, 100);
}

void plot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x + h, y + k);
    glEnd();
}

void circle()
{
    int x = 0;
    double y = r;
    double x2 = r / sqrt(2);
    while (x <= x2)
    {
        y = sqrt(r * r - x * x);
        plot(x, floor(y));
        plot(x, -floor(y));
        plot(-x, floor(y));
        plot(-x, -floor(y));
        plot(floor(y), x);
        plot(-floor(y), x);
        plot(floor(y), -x);
        plot(-floor(y), -x);
        x += 1;
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    circle();
    glFlush();
}

int main(int argc, char **argv)
{
	cout << "Enter the center: ";
    cin >> h >> k;
	cout << "Enter the radius: ";
    cin >> r;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Circle: Polynomial Equation");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}