#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;
#define N 4   // number of control points
#define D 2   // number of dimensions
#define T 100 // number of u subintervals

static GLfloat ctrlPoints[N][3];
GLUnurbsObj *theNurb;

int ww = 700;
int wh = 700;
int MOVENAME = -1;
int pickRadius = 50;

void inputControlPoints()
{
    printf("Enter Control Points:\n");
    int x, y;
    for (int i = 0; i < N; i++)
    {
        cout << "Point " << i + 1 << ": ";
        cin >> x >> y;
        ctrlPoints[i][0] = x;
        ctrlPoints[i][1] = y;
        ctrlPoints[i][2] = 0;
    }
}

void display2DControlPolyline()
{
    glLineWidth(2.0);
    glColor3f(0.0f, 0.0f, 1.0f);

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < N; i++)
    {
        glVertex2i(ctrlPoints[i][0], ctrlPoints[i][1]);
    }
    glEnd();
    glFlush();
}

void display2DControlPoints()
{
    glPointSize(3.0);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POINTS);
    for (int i = 0; i < N; i++)
    {
        glVertex2i(ctrlPoints[i][0], ctrlPoints[i][1]);
    }
    glEnd();
    glFlush();
}

void interpolate()
{
    printf("\nCalculating Interpolating Form...\n");

    glLineWidth(4.0);
    glColor3f(1.0f, 0.0f, 0.0f);

    GLfloat bu[N];

    glBegin(GL_LINE_STRIP);

    for (int uInt = 0; uInt <= T; uInt++)
    {
        GLfloat u = uInt / (GLfloat)T;
        bu[0] = (-9.0 / 2.0) * (u - (1.0 / 3.0)) * (u - (2.0 / 3.0)) * (u - 1.0);
        bu[1] = (27.0 / 2.0) * u * (u - (2.0 / 3.0)) * (u - 1.0);
        bu[2] = (-27.0 / 2.0) * u * (u - (1.0 / 3.0)) * (u - 1.0);
        bu[3] = (9.0 / 2.0) * u * (u - (1.0 / 3.0)) * (u - (2.0 / 3.0));

        GLfloat x = 0.0;
        GLfloat y = 0.0;

        for (int i = 0; i < N; i++)
        {
            x += bu[i] * ctrlPoints[i][0];
            y += bu[i] * ctrlPoints[i][1];
        }
        printf("x=%g  y=%g\n", x, y);
        glVertex2i(x, y);
    }

    glEnd();
    glFlush();
}

void hermite()
{
    printf("\nCalculating Hermite Form with specific endpoint tangents...\n");

    glLineWidth(4.0);
    glColor3f(1.0f, 0.0f, 0.0f);

    GLfloat fu[N];

    glBegin(GL_LINE_STRIP);

    for (int uInt = 0; uInt <= T; uInt++)
    {
        GLfloat u = uInt / (GLfloat)T;
        GLfloat u2 = u * u;
        GLfloat u3 = u2 * u;
        fu[0] = 2.0 * u3 - 3.0 * u2 + 1.0;
        fu[1] = -2.0 * u3 + 3.0 * u2;
        fu[2] = u3 - 2.0 * u2 + u;
        fu[3] = u3 - u2;

        GLfloat x = 0.0;
        GLfloat y = 0.0;

        // p0 = ctrlPoints[0]
        x += fu[0] * ctrlPoints[0][0];
        y += fu[0] * ctrlPoints[0][1];

        // p1 = ctrlPoints[3]
        x += fu[1] * ctrlPoints[3][0];
        y += fu[1] * ctrlPoints[3][1];

        //  tangent at p0 = ctrlPoints[1]-ctrlPoints[0]
        x += fu[2] * (3.0 * (ctrlPoints[1][0] - ctrlPoints[0][0]));
        y += fu[2] * (3.0 * (ctrlPoints[1][1] - ctrlPoints[0][1]));

        //  tangent at p1 = ctrlPoints[3]-ctrlPoints[2]
        x += fu[3] * (6.0 * (ctrlPoints[3][0] - ctrlPoints[2][0]));
        y += fu[3] * (6.0 * (ctrlPoints[3][1] - ctrlPoints[2][1]));

        printf("x=%g  y=%g\n", x, y);
        glVertex2i(x, y);
    }

    glEnd();
    glFlush();
}

void drawCurve()
{
    hermite();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    display2DControlPolyline();
    display2DControlPoints();
    drawCurve();
    glFlush();
}

void mainMenu(int id)
{
    glutPostRedisplay();
}

void createMenu()
{
    glutCreateMenu(mainMenu);
    glutAddMenuEntry("Control Polygon", 1);
    glutAddMenuEntry("Exit", 8);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, ww, 0.0, wh);
}

// mouse function
void myPick(int button, int state, int xPosition, int yPosition)
{
    // left mouse button down
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        GLuint newX = xPosition;
        GLuint newY = wh - yPosition;
        printf("Pick location: x = %d   y = %d\n", newX, newY);

        // determine which control point is picked

        int choiceFound = 0;

        for (int i = 0; i < N && !choiceFound; i++)
        {
            // Use globally defined pickRadius
            if ((abs(ctrlPoints[i][0] - newX) <= pickRadius) &&
                (abs(ctrlPoints[i][1] - newY) <= pickRadius))
            {
                MOVENAME = i;
                choiceFound = 1;
                printf("Control point %d was picked.\n", MOVENAME);
            }
        }
    }

    // left mouse button up
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        MOVENAME = -1;
    }
    glutPostRedisplay();
}

// mouse motion function
void myMouseMove(int xPosition, int yPosition)
{
    if (MOVENAME > -1)
    {
        GLuint newX = xPosition;
        GLuint newY = wh - yPosition;
        printf("New control point %d location: x = %d   y = %d\n", MOVENAME, newX, newY);

        ctrlPoints[MOVENAME][0] = newX;
        ctrlPoints[MOVENAME][1] = newY;

        glutPostRedisplay();
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    ww = w;
    wh = h;
}

int main(int argc, char **argv)
{
    inputControlPoints();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(ww, wh);
    glutInitWindowPosition(7000, 70);
    glutCreateWindow("Hermite Curve");
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myPick);
    glutMotionFunc(myMouseMove);
    glutReshapeFunc(reshape);
    init();
    createMenu();
    glutMainLoop();
    return 0;
}