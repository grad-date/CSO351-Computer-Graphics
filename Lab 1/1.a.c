#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>

float x1, x2, y1, y2;

void display(void)
{
    float dy, dx, step, x, y, k, Xin, Yin;
    dx = x2 - x1;
    dy = y2 - y1;

    if (abs(dx) > abs(dy))
        step = abs(dx);
    else
        step = abs(dy);

    Xin = dx / step;
    Yin = dy / step;
    x = x1;
    y = y1;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    for (k = 1 ; k <= step; k++)
    {
        x = x + Xin;
        y = y + Yin;
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
    }
    glFlush();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, 100, -50, 100);
}

int main(int argc, char** argv) 
{
    printf("Enter x1 and y1 : ");
    scanf("%f %f", &x1, &y1);
    printf("Enter x2 and y2 : ");
    scanf("%f %f", &x2, &y2);
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (400, 400);
    glutInitWindowPosition (10, 10);
    glutCreateWindow ("Line Generation using DDA");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}