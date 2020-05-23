#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
#define PI 3.142857

GLfloat twicePI = 2.0f * PI;

/********************************Initialization Variables **********************************/
float x, y, i;

struct balls{
    int xcenter,ycenter; 
    bool xdir,ydir;
    bool gone;
    balls() : xcenter((rand() % 1240)- 620),ycenter((rand() % 680)- 340),xdir((rand()%2)==0),ydir((rand()%2)==0),gone(false){}
};

balls ball;
int board = 0;
int score=1;
void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glColor3f(1.0f, 0.0f, 0.0f);

    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-620.0, 620.0, -340.0, 340.0);
}

void keyboard(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_LEFT:
            board =max(-519,board-50);
            break;
        case GLUT_KEY_RIGHT:
            board =min(520,board+50);
            break;
    }
}

void display (void)  
{ 
    glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_POINTS); 

    for ( i = 0; i < (2 * PI); i += 0.1) 
    { 
        x = ball.xcenter + 5 * cos(i); 
        y = ball.ycenter + 5 * sin(i); 
        if(x>=620)ball.xdir=false;
        if(x<=-620)ball.xdir=true;
        if(y>=340)ball.ydir=false;
        if(y<=-340){}
        if(y<=-295 && (board+100 > ball.xcenter) && (board-100 < ball.xcenter)){ball.ydir=true; score++;}
        glVertex2i(x, y); 
    } 
    glEnd();



    glBegin(GL_LINE_LOOP); 
			glVertex2i(board + 100, -315); 
			glVertex2i(board + 100, -295); 
			glVertex2i(board - 100, -295); 
			glVertex2i(board - 100, -315); 
	glEnd(); 

    glutSwapBuffers();
} 
void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);
    // for(int n=0;n<=min(100,score%5)&& !ball.gone ; n++){
    ball.xdir ? ball.xcenter+=3 : ball.xcenter-=3;
    ball.ydir ? ball.ycenter+=3 : ball.ycenter-=3;
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
    glutSpecialFunc(keyboard);
    // glutKeyboardFunc(keyboard);
    glutMainLoop();
}