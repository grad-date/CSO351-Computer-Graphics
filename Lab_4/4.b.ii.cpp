#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;

#define SIN(x) sin(x * 3.141592653589 / 180)
#define COS(x) cos(x * 3.141592653589 / 180)

int x[3], y[3], sx, sy, h, k, angle;

void draw(int xp[3], int yp[3])
{
    glBegin(GL_LINE_LOOP);
    glVertex2i(xp[0], yp[0]);
    glVertex2i(xp[1], yp[1]);
    glVertex2i(xp[2], yp[2]);
    glEnd();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, 100, -50, 100);
}

void findNewCoordinate(int s[][2], int p[][1])
{
    int temp[2][1] = {0};

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 1; j++)
            for (int k = 0; k < 2; k++)
                temp[i][j] += (s[i][k] * p[k][j]);

    p[0][0] = temp[0][0];
    p[1][0] = temp[1][0];
}

void scaling(void)
{
    int scx[3], scy[3];
    scx[0] = x[0] - h, scx[1] = x[1] - h, scx[2] = x[2] - h;
    scy[0] = y[0] - k, scy[1] = y[1] - k, scy[2] = y[2] - k;
    int s[2][2] = {sx, 0, 0, sy};
    int p[2][1];
    for (int i = 0; i < 3; i++)
    {
        p[0][0] = scx[i];
        p[1][0] = scy[i];

        findNewCoordinate(s, p);

        scx[i] = p[0][0];
        scy[i] = p[1][0];
    }

    for (int i = 0; i < 3; i++)
    {
        scx[i] += h;
        scy[i] += k;
    }
    draw(scx, scy);
}

void rotation(void)
{
    int ax[3], ay[3];
    ax[0] = x[0] - h, ax[1] = x[1] - h, ax[2] = x[2] - h;
    ay[0] = y[0] - k, ay[1] = y[1] - k, ay[2] = y[2] - k;
    int i = 0;
    while (i < 3)
    {

        int x_r = ax[i] - h;
        int y_r = ay[i] - k;

        ax[i] = h + (x_r * COS(angle) - y_r * SIN(angle));
        ay[i] = k + (x_r * SIN(angle) + y_r * COS(angle));
        i++;
    }

    draw(ax, ay);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(1.0);
    draw(x, y);
    glColor3f(0.0, 0.0, 1.0);
    rotation();
    glColor3f(1.0, 1.0, 1.0);
    scaling();
    glFlush();
}

int main(int argc, char **argv)
{
    cout << "Enter vertices (make sure vertices are not collinear):\n";
    for (int i = 0; i < 3; i++)
    {
        cout << "(x" << i + 1 << ", y" << i + 1 << "): ";
        cin >> x[i] >> y[i];
    }
    cout << endl << "Enter reference point (h, k): ";
    cin >> h >> k;
    cout << "Enter scaling factors sx, sy: ";
    cin >> sx >> sy;
    cout << endl << "Enter rotation angle: ";
    cin >> angle;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Red: Original; White: Scaled; Blue: Rotated");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}