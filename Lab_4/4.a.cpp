#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;
typedef double Matrix3x3[3][3];

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

void scale2D(double sx, double sy, double x, double y)
{
    Matrix3x3 matScale;
    setIdentity(matScale);
    matScale[0][0] = sx;
    matScale[0][2] = (1 - sx) * x;
    matScale[1][1] = sy;
    matScale[1][2] = (1 - sy) * y;
    matrixPreMultiply(matScale, matComposite);
}

void shear2D(double shx, double shy)
{
    Matrix3x3 matShear;
    setIdentity(matShear);
    matShear[0][1] = shx;
    matShear[0][2] = 0;
    matShear[1][0] = shy;
    matShear[1][2] = 0;
    matrixPreMultiply(matShear, matComposite);
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
    int n = 3;
    cout << "\nEnter the vertices of the triangle:\n";
    vector<pair<double, double>> vertex(3);
    for (int i = 0; i < n; ++i)
        cin >> vertex[i].first >> vertex[i].second;
    pair<int, int> centroid;
    double xSum = 0, ySum = 0;
    for (int i = 0; i < n; i++)
        xSum += vertex[i].first;
    for (int i = 0; i < n; ++i)
        ySum += vertex[i].second;
    centroid.first = xSum / n;
    centroid.second = ySum / n;
    cout << "\nChoice Menu:\n";
    cout << "1. Translate\n";
    cout << "2. Shear\n";
    cout << "3. Scale\n";
    cout << "4. Rotate\n";
    cout << "5. Line refection\n";
    cout << "\nYour choice: ";
    cin >> choice;
    if (choice == 1)
    {
        glBegin(GL_TRIANGLES);
        double tx, ty;
        cout << "Enter translation point: ";
        cin >> tx >> ty;
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 0.0, 0.0);
        triangle(vertex);
        setIdentity(matComposite);
        translate2D(tx, ty);
        transformVertex(n, vertex);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.0, 0.0, 1.0);
        triangle(vertex);
        glEnd();
        glFlush();
    }
    else if (choice == 2)
    {
        double shx, shy;
        cout << "Enter shx, shy values: "; // between 0 and 1
        cin >> shx >> shy;
        glBegin(GL_TRIANGLES);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 0.0, 0.0);
        triangle(vertex);
        setIdentity(matComposite);
        shear2D(shx, shy);
        transformVertex(n, vertex);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.0, 0.0, 1.0);
        triangle(vertex);
        glEnd();
        glFlush();
    }
    else if (choice == 3)
    {
        double sx, sy;
        cout << "Enter sx, sy values: ";
        cin >> sx >> sy;
        glBegin(GL_TRIANGLES);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 0.0, 0.0);
        triangle(vertex);
        setIdentity(matComposite);
        scale2D(sx, sy, 0, -20);
        transformVertex(n, vertex);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.0, 0.0, 1.0);
        triangle(vertex);
        glEnd();
        glFlush();
    }
    else if (choice == 4)
    {
        double theta;
        cout << "Enter theta value: ";
        cin >> theta;
        glBegin(GL_TRIANGLES);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 0.0, 0.0);
        triangle(vertex);
        setIdentity(matComposite);
        rotate2D(100.0, 100.0, theta);
        transformVertex(n, vertex);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.0, 0.0, 1.0);
        triangle(vertex);
        glEnd();
        glFlush();
    }
    else if (choice == 5)
    {
        double m, c;
        cout << "Enter m and c: ";
        cin >> m >> c;
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
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0);
    glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void winReshape(GLint newwidth, GLint newheight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 225, 0, 225);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Red: Original; Blue: 2D Transformed");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(winReshape);
    glutMainLoop();
    return 0;
}
