#include<bits/stdc++.h>
#include <GL/glut.h>

#define pb push_back
#define F first
#define S second
#define ii pair<double, double>
#define vii vector<ii>
#define REP(i, a, b) for(int i = a; i <= b; i++)
#define REPL(i, a, b) for(ll i = a; i <= b; i++)
#define ios ios_base::sync_with_stdio(false);cin.tie(NULL);
using namespace std;

float x_1,y_1,x_2,y_2,xmax,xmin,ymax,ymin;

void init() {
    glClearColor(0.0,0.0,0.0,0); 
    glColor3f(1.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0 ,500 ,0 ,500);
}

void display() {
    glColor3f(1.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(x_1,y_1);
    glVertex2f(x_2,y_2);
    glVertex2f(xmin,ymin);
    glVertex2f(xmin,ymax);
    glVertex2f(xmin,ymax);
    glVertex2f(xmax,ymax);
    glVertex2f(xmax,ymax);
    glVertex2f(xmax,ymin);
    glVertex2f(xmax,ymin);
    glVertex2f(xmin,ymin);
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
    glColor3f(0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINES);
        glVertex2f(xmin,ymin);
        glVertex2f(xmin,ymax);
        glVertex2f(xmin,ymax);
        glVertex2f(xmax,ymax);
        glVertex2f(xmax,ymax);
        glVertex2f(xmax,ymin);
        glVertex2f(xmax,ymin);
        glVertex2f(xmin,ymin);
        glVertex2f(x_1 + delta_x*u1,y_1 + delta_y*u1);
        glVertex2f(x_1 + delta_x*u2,y_1 + delta_y*u2);
    glEnd();
    glFlush();
}

void LiangBarsky() {
    double delta_x = x_2 - x_1;
    double delta_y = y_2 - y_1;
    vector<double> p;
    p.push_back(delta_x);
    p.push_back(-delta_x);
    p.push_back(delta_y);
    p.push_back(-delta_y);

    vector<double>q;
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

void CyrusBeck() {
    cout<<"Cyrus Beck\n";
    cout<<x_1<<" "<<y_1<<"\n";
    cout<<x_2<<" "<<y_2<<"\n";
    ii p1 = make_pair(x_1,y_1);
    ii p2 = make_pair(x_2,y_2);
    vii n;
    vii f;
    n.pb({1,0});
    n.pb({-1,0});
    n.pb({0,1});
    n.pb({0,-1});
    f.pb({xmin,ymin});
    f.pb({xmax,ymax});
    f.pb({xmin,ymin});
    f.pb({xmax,ymax});
    double tl = 0,tu = 1;
    ii D = make_pair(x_2 - x_1,y_2 - y_1);
    REP(i,0,3) {    
        ii w;
        w = {x_1 - f[i].F,y_1 -f[i].S};
        double Ddotn = D.F * n[i].F + D.S * n[i].S;
        double Wdotn = w.F * n[i].F + w.S * n[i].S;
        if(Ddotn != 0.0) {
            double t = -Wdotn / Ddotn;
            if(Ddotn > 0.0) {
                if(t>1) {
                    cout<<"Line outside the clipping window\n";
                    return;
                }
                tl = max(t,tl);
            }
            else
            {
                if(t<0) {
                    cout<<"Line outside the clipping window\n";
                    return;
                }
                tu = min(t,tu);
            }
        }
        else {
            if(Wdotn < 0.0) {
                cout<<"Line outside the clipping window\n";
                return;
            }
        }
    }
    if(tl > tu) {
        cout<<"Line outside the clipping window\n";
    }
    else {
        cout<<tl<<" "<<tu<<"\n";
        clippedLine(tl,tu);
    }

}


void myKey(unsigned char key,int x,int y) {
    if(key=='l') {
        glFlush();
        LiangBarsky();
    }
    else if(key=='c') {
        glFlush();
        CyrusBeck();
    }
}

int main(int argc, char **argv)
{
    cout<<"Enter the starting coordinate of a line   : ";
    cin>>x_1>>y_1;
    cout<<"Enter the ending coordinate of the line   : ";
    cin>>x_2>>y_2;
    cout<<"Enter the xmin and xmax of clipping window: ";
    cin>>xmin>>xmax;
    cout<<"Enter the ymin and ymax of clipping window: ";
    cin>>ymin>>ymax;
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (700,700);
    glutInitWindowPosition (7000,70);
    glutCreateWindow ("Cyrus-Beck");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(myKey);
    glutMainLoop();
    return 0;
}