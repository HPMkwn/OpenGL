//#include <windows.h>
#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
#define PI 3.142857
#define MAX_SCORE 5
GLfloat twicePI = 2.0f * PI;
int x,y;
/********************************Initialization Variables **********************************/
struct Ball{
    int xcenter,ycenter;
    bool ballboard;
    bool gone;
    bool xdir,ydir;
    Ball() : xcenter(0),ycenter(0),xdir(0),ydir(0),gone(false) {}
};


Ball ball;
int nextfree=0;
int boardblue = 0;
int boardred = 0;
int redScore=0;
int blueScore =0;
bool isThereBall = false;
int lastThrown = 1;



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
            boardblue =max(-519,boardblue-50);
            break;
        case GLUT_KEY_RIGHT:
            boardblue =min(520,boardblue+50);
            break;
        case GLUT_KEY_F1:
            boardred = max(-519,boardred-50);
            break;
        case GLUT_KEY_F3:
            boardred = min(520,boardred+50);
            break;
        case GLUT_KEY_UP:
            if(!isThereBall && lastThrown==1){
                isThereBall = true;
                ball.xcenter=boardblue;
                ball.ycenter=-280;
                ball.ballboard=0;
                ball.gone = true;
                ball.xdir= true;
                ball.ydir= true;
                lastThrown=0;
            }
            break;
        case GLUT_KEY_DOWN:
            if(!isThereBall && lastThrown==1){
                isThereBall = true;
                ball.xcenter=boardblue;
                ball.ycenter=-280;
                ball.ballboard=0;
                ball.gone = true;
                ball.xdir= false;
                ball.ydir= true;
                lastThrown=0;
            }
            break;
        case GLUT_KEY_F2:
            if(!isThereBall && lastThrown==0){
                isThereBall=true;
                ball.xcenter=boardred;
                ball.ycenter=280;
                ball.ballboard=1;
                ball.gone = true;
                ball.xdir= false;
                ball.ydir= false;
                lastThrown=1;
            }
            break;
        case GLUT_KEY_F4:
            if(!isThereBall && lastThrown==0){
                isThereBall=true;
                ball.xcenter=boardred;
                ball.ycenter=280;
                ball.ballboard=1;
                ball.gone = true;
                ball.xdir= true;
                ball.ydir= false;
                lastThrown=1;
            }
            break;

    }
}

void display (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    ball.ballboard==0 ? glColor3f(0.0,0.0,1.0) : glColor3f(1.0,0.0,0.0);
    if(ball.gone){
    glBegin(GL_POINTS);
    for (float j = 0; j < (2 * PI); j += 0.1)
    {
        x = ball.xcenter + 5 * cos(j); 
        y = ball.ycenter + 5 * sin(j); 
        if(x>=620)ball.xdir=false;
        else if(x<=-620)ball.xdir=true;
        else if(y>=340){isThereBall=false;}
        else if(y>=295 && (boardred+100 > ball.xcenter) && (boardred-100 < ball.xcenter)){ball.ydir=false; blueScore++;if(blueScore==MAX_SCORE){printf("player 1 wins");exit(0);}}
        else if(y<=-340){isThereBall=false; }
        else if(y<=-295 && (boardblue+100 > ball.xcenter) && (boardblue-100 < ball.xcenter)){ball.ydir=true; redScore++;if(redScore==MAX_SCORE){printf("player 2 wins");exit(0);}}
        glVertex2i(x, y); 
    }
    glEnd();
    }
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
			glVertex2i(boardblue + 100, -315);
			glVertex2i(boardblue + 100, -295);
			glVertex2i(boardblue - 100, -295);
			glVertex2i(boardblue - 100, -315);
	glEnd();
	glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
			glVertex2i(boardred + 100, +315);
			glVertex2i(boardred + 100, +295);
			glVertex2i(boardred - 100, +295);
			glVertex2i(boardred - 100, +315);
	glEnd();


    glutSwapBuffers();
}
void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);

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
