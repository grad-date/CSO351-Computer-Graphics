#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

typedef double Matrix3x3[3][3];
int n = 3;
vector<pair<double, double>> vertex(3);
double m, c;
Matrix3x3 matComposite;
int choice;

void setIdentity(Matrix3x3 matIdentity)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            matIdentity[i][j] = (i == j);
}

void matrixPreMultiply(Matrix3x3 m1, Matrix3x3 m2)
{
    Matrix3x3 temp;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            temp[i][j] = m1[i][0] * m2[0][j] + m1[i][1] * m2[1][j] + m1[i][2] * m2[2][j];
        }
    }
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m2[i][j] = temp[i][j];
}

void translate2D(double tx, double ty)
{
    Matrix3x3 matTranslation;
    setIdentity(matTranslation);
    matTranslation[0][2] = tx;
    matTranslation[1][2] = ty;
    matrixPreMultiply(matTranslation, matComposite);
}

void rotate2D(double x, double y, double theta)
{
    Matrix3x3 matRot;
    matRot[0][0] = cos(theta);
    matRot[0][1] = -sin(theta);
    matRot[0][2] = x * (1 - cos(theta)) + y * sin(theta);
    matRot[1][0] = sin(theta);
    matRot[1][1] = cos(theta);
    matRot[1][2] = y * (1 - cos(theta)) - x * sin(theta);
    matrixPreMultiply(matRot, matComposite);
}

void reflectx2D()
{
    Matrix3x3 matShear;
    setIdentity(matShear);
    matShear[0][1] = 0;
    matShear[0][2] = 0;
    matShear[1][0] = 0;
    matShear[1][1] = -1;
    matShear[1][2] = 0;
    matrixPreMultiply(matShear, matComposite);
}

void transformVertex(int nVertices, vector<pair<double, double>> &vertex)
{
    double temp;
    for (int i = 0; i < nVertices; ++i)
    {
        temp = matComposite[0][0] * vertex[i].first + matComposite[0][1] * vertex[i].second + matComposite[0][2];
        vertex[i].second = matComposite[1][0] * vertex[i].first + matComposite[1][1] * vertex[i].second + matComposite[1][2];
        vertex[i].first = temp;
    }
}

void triangle(vector<pair<double, double>> &vertex)
{
    for (int k = 0; k < 3; k++)
        glVertex2f(vertex[k].first, vertex[k].second);
}

void display()
{
    double tx = 0, ty = c;
    double theta = atan(m);

    glBegin(GL_TRIANGLES);

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    triangle(vertex);

    setIdentity(matComposite);
    translate2D(tx, -ty);
    rotate2D(0, 0, -theta);
    reflectx2D();
    rotate2D(0, 0, theta);
    translate2D(tx, ty);
    transformVertex(n, vertex);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    triangle(vertex);

    glEnd();
    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-50, 100, -50, 100);
}

void winReshape(GLint newwidth, GLint newheight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, 100, -50, 100);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
    cout << "Enter vertices (make sure vertices are not collinear):\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "(x" << i + 1 << ", y" << i + 1 << "): ";
        cin >> vertex[i].first >> vertex[i].second;
    }

    cout << "\nEnter Line parameters m and c: ";
    cin >> m >> c;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Red: Original; Blue: Reflected");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(winReshape);
    glutMainLoop();
    return 0;
}