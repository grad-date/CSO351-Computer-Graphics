#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;
int h, k, a, b;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, 100, -50, 100);
}

void plotpixels(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x+h, y+k);
    glEnd();
}

void ellipse1()
{
    int x = 0;
    double y = b;
    plotpixels(x,y);
    plotpixels(x,-y);
    x++;
    while (x <= a)
    {
        y = b * sqrt(((a*a)-(x*x*1.0))/(a*a));
        round(y);
        plotpixels(x,y);
        plotpixels(-x,y);
        plotpixels(-x,-y);
        plotpixels(x,-y);
        x++;
    }
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 0.0, 0.0);
    glPointSize(1.0);
    ellipse1();
    glFlush ();
}

int main(int argc, char** argv)
{
    cout << "Enter the center: ";
    cin >> h >> k;
    cout << "Enter major and minor axes: ";
    cin >> a >> b;
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("Ellipse : Polynomial Algorithm");
    glutDisplayFunc(display);
    init ();
    glutMainLoop();
    return 0;
}