#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;
int pntX1, pntY1, a, b;

void plot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x + pntX1, y + pntY1);
    glEnd();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, 100, -50, 100);
}

void midPointCircleAlgo()
{
    double x = a;
    double y = 0;
    int theta = 0;
    while (theta <= 90)
    {
        plot(x, y);
        plot(-x, y);
        plot(x, -y);
        plot(-x, -y);
        x = a * cos(theta * 3.14 / 180.0);
        y = b * sin(theta * 3.14 / 180.0);
        theta++;
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(1.0);
    midPointCircleAlgo();
    glFlush();
}

int main(int argc, char **argv)
{
    cout << "Enter the center: ";
    cin >> pntX1 >> pntY1;
    cout << "Enter major and minor axes: ";
    cin >> a >> b;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (0, 0);
    glutCreateWindow("Ellipse: Parametric Equation");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
	return 0;
}