/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

int num_puntos = 10; //numero de puntos a ingresar

int x[100];
int y[100];

int q=0;
int k=0;
double old_X, old_Y;
double sig_X, sig_Y;

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void init(void){
	glClearColor(0.0,1.0,1.0,0.0);
	glColor3f(1.0, 0.0, 1.0);
	glPointSize(8.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
 	gluOrtho2D(0,500,0,500);
}

void drawLine(float l,float m, float j, float i){
	glBegin(GL_LINES);
	glVertex2f(l,m);
	glVertex2f(j,i);
	glEnd();
	glFlush();
}

void drawDot(int l, int m){
	glBegin(GL_POINTS);
	glVertex2i(l,m);
	glEnd();
	glFlush();
}

int fact(int x){
	if(x == 0)
		return 1;
	int facto=1;
	for(; x > 0; x = x-1){
		facto=facto*(x);
	}
	return facto;
}

void bern(){
	double t;
	int i;
	for(t=0; t<=1.0; t=t+0.0001){
		sig_X=0;
		sig_Y=0;
		for(i=0; i<=num_puntos; i++){
			sig_X=sig_X+double((double)fact(num_puntos)/(double)(fact(num_puntos-i)*fact(i)))*(pow((1-t),num_puntos-i))*pow(t,i)*x[i];
			sig_Y=sig_Y+double((double)fact(num_puntos)/(double)(fact(num_puntos-i)*fact(i)))*(pow((1-t),num_puntos-i))*pow(t,i)*y[i];
		}
		drawLine(old_X,500-old_Y,sig_X,500-sig_Y);
		old_X=sig_X;
		old_Y=sig_Y;
	}
}

void placeDots(int button, int state, int i, int j){
	if(state==GLUT_DOWN){
		if(button==GLUT_LEFT_BUTTON){
			if(q <= num_puntos){
				x[q]=(int)i;
				y[k]=(int)j;
				drawDot(x[q],500-y[k]);
				if(q==0)
					old_X=x[q];
				if(q==0)
					old_Y=y[q];
				q++;
				k++;
			}
			else if(q == num_puntos+1){
				bern();
				q++;
			}
		}
	}
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("CURVAS DE BEZIER");
	glutMouseFunc(placeDots);
 	glutDisplayFunc(display);
 	init();
	glutMainLoop();
	return 0;
}
