#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <stdio.h>

using namespace std;
int h, k, a, b;

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
    glVertex2i(x, y);
    glEnd();
}

void ellipse(int h, int k, int a, int b)
{
    int x, y;
    float p;
    p = b * b - a * a * b + a * a / 4;
    x = 0;
    y = b;
    while (2.0 * b * b * x <= 2.0 * a * a * y)
    {
        if (p < 0)
        {
            x++;
            p = p + 2 * b * b * x + b * b;
        }
        else
        {
            x++;
            y--;
            p = p + 2 * b * b * x - 2 * a * a * y - b * b;
        }
        plot(h + x, k + y);
        plot(h + x, k - y);
        plot(h - x, k + y);
        plot(h - x, k - y);
    }

    p = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
    while (y > 0)
    {
        if (p <= 0)
        {
            x++;
            y--;
            p = p + 2 * b * b * x - 2 * a * a * y + a * a;
        }
        else
        {
            y--;
            p = p - 2 * a * a * y + a * a;
        }
        plot(h + x, k + y);
        plot(h + x, k - y);
        plot(h - x, k + y);
        plot(h - x, k - y);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(1.0);
    ellipse(h, k, a, b);
    glFlush();
}

int main(int argc, char **argv)
{
    cout << "Enter the centre : ";
    cin >> h >> k;
    cout << "Enter major and minor axes: ";
    cin >> a >> b;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Ellipse: Midpoint Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}