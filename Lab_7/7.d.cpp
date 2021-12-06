#include<bits/stdc++.h>
#include <GL/glut.h>

#define pb push_back
#define F first
#define S second
#define ii pair<double, double>
#define vii vector<ii>
using namespace std;

float x_1,y_1,x_2,y_2,xmax,xmin,ymax,ymin;
vii vertices;

void init() {
    glClearColor(0.0,0.0,0.0,0);
    glColor3f(1.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex2f(xmin,ymin);
        glVertex2f(xmin,ymax);
        glVertex2f(xmin,ymax);
        glVertex2f(xmax,ymax);
        glVertex2f(xmax,ymax);
        glVertex2f(xmax,ymin);
        glVertex2f(xmax,ymin);
        glVertex2f(xmin,ymin);
        for(int i=0;i<4;i++)
        {
            glVertex2f(vertices[i].F,vertices[i].S);
            glVertex2f(vertices[(i+1)%4].F,vertices[(i+1)%4].S);
        }
    glEnd();
    glFlush();
}

void clippedLine(double u1,double u2) {
    double delta_x = x_2 - x_1;
    double delta_y = y_2 - y_1;
    double cl1_x = x_1 + delta_x*u1;
    double cl2_x = x_1 + delta_x*u2;
    double cl1_y = y_1 + delta_y*u1;
    double cl2_y = y_1 + delta_y*u2;
    cout<<cl1_x<<" "<<cl1_y<<" "<<cl2_x<<" "<<cl2_y<<"\n";
    glFlush();
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINES);
        glVertex2f(x_1 + delta_x*u1,y_1 + delta_y*u1);
        glVertex2f(x_1 + delta_x*u2,y_1 + delta_y*u2);
    glEnd();
}

void PolygonClipping() {
    double delta_x = x_2 - x_1;
    double delta_y = y_2 - y_1;
    vector<double> p ;
    p.push_back(delta_x);
    p.push_back(-delta_x);
    p.push_back(delta_y);
    p.push_back(-delta_y);
    vector<double>q ;
    q.push_back(xmax - x_1);
    q.push_back(x_1 - xmin);
    q.push_back(ymax - y_1);
    q.push_back(y_1 - ymin);
    double u1 = 0,u2 = 1;
    for (int i = 0; i < 4; ++i) {
        if(p[i] < 0)
            u1 = max(u1,q[i]/p[i]);
        else if(p[i] >0)
            u2 = min(u2,q[i]/p[i]);
        else
            if(q[i] < 0) {
                cout<<"Line outside the clipping window\n";
                return;
            }
    }
    if(u1 > u2) {
        cout<<"Line outside the clipping window\n";
        return;
    }
    else {
        clippedLine(u1,u2);
    }
}

void myKey(unsigned char key,int x,int y) {
    if(key=='l') {
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_LINES);
        glVertex2f(xmin,ymin);
        glVertex2f(xmin,ymax);
        glVertex2f(xmin,ymax);
        glVertex2f(xmax,ymax);
        glVertex2f(xmax,ymax);
        glVertex2f(xmax,ymin);
        glVertex2f(xmax,ymin);
        glVertex2f(xmin,ymin);
        glEnd();
        for(int i=0;i<4;i++) {
            x_1 = vertices[i].F; y_1 = vertices[i].S;
            x_2 = vertices[(i+1)%4].F; y_2 = vertices[(i+1)%4].S;
            PolygonClipping();
        }
        glFlush();
    }
}

int main(int argc, char **argv) {
    int n = 4;
    cout<<"Enter the four vertices:\n";
    for (int i = 0; i < 4; ++i) {
        ii c;
        cin>>c.F>>c.S;
        vertices.pb(c);
    }
    cout<<"Enter the xmin and xmax of clipping window: ";
    cin>>xmin>>xmax;
    cout<<"Enter the ymin and ymax of clipping window: ";
    cin>>ymin>>ymax;
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (700,700);
    glutInitWindowPosition (7000,70);
    glutCreateWindow ("Polygon Clipping");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(myKey);
    glutMainLoop();
    return 0;
}