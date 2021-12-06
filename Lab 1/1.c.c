#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

GLint xbeg, ybeg, xend, yend, dlen, slen;

void init(void) 
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(-50, 100, -50, 100);
}

void display (int xa, int ya, int xb, int yb) 
{
	GLint dx = abs (xb - xa), 
            dy = abs (yb - ya),
	        param = 2 * dy - dx,
	        x, y, xMax;
	GLfloat p[2];

	if (xa > xb) {
		x = xb;
		y = yb;
		xMax = xa;
	} 
	else {
		x = xa;
		y = ya;
		xMax = xb;
	}

	p[0] = x;
	p[1] = y;
	glVertex2fv (p);
	while (x < xMax) {
		x++;
		if (param < 0) {
			param += 2 * dy;
		} else {
			y++;
			param += 2 * (dy - dx);
		}
		p[0] = x;
		p[1] = y;
		glVertex2fv (p);
	}
}


void showGraphic (void) 
{
	glClear (GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
	glBegin (GL_POINTS);
	GLdouble x1, y1, x2, y2,
	        theta = atan2 (yend - ybeg, xend - xbeg),
	        s = sin (theta),
	        c = cos (theta);
	x1 = xbeg;
	y1 = ybeg;

	while (x1 < xend && y1 < yend) {
		x2 = x1 + dlen * c;
		y2 = y1 + dlen * s;
		display (x1, y1, x2, y2);
		x1 = x2 + slen * c;
        y1 = y2 + slen * s; 		
	}	
	glEnd ();
	glFlush ();
}

int main(int argc, char **argv) {
	GLfloat slope;
	do {
		printf("Enter x1 and y1 : ");
		scanf("%d %d", &xbeg, &ybeg);
		printf("Enter x2 and y2 : ");
		scanf("%d %d", &xend, &yend);
		slope = (yend - ybeg) / (xend - xbeg);
	} while (slope < 0 || slope > 1);
	printf("Enter lengths of dash and space: ");
	scanf("%d %d", &dlen, &slen);
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (400, 400);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("Dased Line using Breshenham's Algorithm");
	init();
	glutDisplayFunc(showGraphic);
	glutMainLoop();
	return 0;
}