#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#define PI 3.142857

GLfloat twicePI = 2.0f * PI;

float x, y, i;
int xcenter = 0,ycenter = 0; 
bool xdir,ydir;
void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glColor3f(1.0f, 0.0f, 0.0f);

    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-620.0, 620.0, -340.0, 340.0);
}

void display (void)  
{ 
    glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_POINTS); 

    for ( i = 0; i < (2 * PI); i += 0.01) 
    { 
        x = xcenter + 5 * cos(i); 
        y = ycenter + 5 * sin(i); 
        if(x>=620)xdir=false;
        if(x<=-620)xdir=true;
        if(y>=340)ydir=false;
        if(y<=-340)ydir=true;
        glVertex2i(x, y); 
    } 
    glEnd();
    glutSwapBuffers();
} 
void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);
    xdir ? xcenter+=3 : xcenter-=3;
    ydir ? ycenter+=3 : ycenter-=3;
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1500, 800);

    glutInitWindowPosition(0, 0);

    glutCreateWindow("Game");

    myInit();
    glutDisplayFunc(display);
    glutTimerFunc(10,timer,0);
    // glutKeyboardFunc(keyboard);
    glutMainLoop();
}