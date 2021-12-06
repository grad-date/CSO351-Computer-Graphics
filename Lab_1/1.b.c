#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

int x1, x2, y1, y2;

void display (void)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int p0 = 2*dy - dx;
    float x = x1, y = y1;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2i (x, y);
    int p = p0;
    int k;

    for(k = 0 ; k < dx ; k++)
    {
        if(p < 0)
        {
            x = x + 1;
            glVertex2i(x, y);
        }
        else
        {
            x = x + 1; 
            y = y + 1;
            glVertex2i(x, y);
        }
    }
    glEnd();
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
    scanf("%d %d", &x1, &y1);
    printf("Enter x2 and y2 : ");
    scanf("%d %d", &x2, &y2);
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (400, 400);
    glutInitWindowPosition (10, 10);
    glutCreateWindow ("Line Generation using Breshenham's Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}