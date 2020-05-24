// #include <windows.h>
#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;
#define PI 3.142857

GLfloat twicePI = 2.0f * PI;
int x,y;
/********************************Initialization Variables **********************************/
struct ball{
    int xcenter,ycenter;
    bool ballboard;
    bool gone;
};
ball* balls = new ball[101];
int nextfree=0;
int boardblue = 0;
int boardred = 0;
void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glColor3f(1.0f, 0.0f, 0.0f);

    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-620.0, 620.0, -340.0, 340.0);
}
void RenderString(float x, float y, void *font,int player)
{

    player ==1 ? glColor3f(0.0, 0.0, 1.0) : glColor3f(1.0, 0.0, 0.0);
    glRasterPos2f(x, y);
    stringstream ss;
    ss << (player==1 ? "blue " : "red ");
    ss << (player==1 ? blueScore : redScore);
    string str = ss.str();
    string showstring = "Player "+ str;
    for(unsigned int i=0;i<showstring.length();i++)
        glutBitmapCharacter(font, showstring[i]);
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
            if(nextfree>99){break;}
            balls[nextfree].xcenter=boardblue;
            balls[nextfree].ycenter=-285;
            balls[nextfree].ballboard=0;
            balls[nextfree].gone=0;
            nextfree++;
            break;
        case GLUT_KEY_F2:
            if(nextfree>99){break;}
            balls[nextfree].xcenter=boardred;
            balls[nextfree].ycenter=+285;
            balls[nextfree].ballboard=1;
            balls[nextfree].gone=0;
            nextfree++;
            break;

    }
}

void display (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i=0;i<min(nextfree,99);i++){
        if(balls[i].gone==1){continue;}
        balls[i].ballboard==0 ? glColor3f(0.0,0.0,1.0) : glColor3f(1.0,0.0,0.0);
        glBegin(GL_TRIANGLES);
        for (float j = 0; j < (2 * PI); j += 0.1)
        {
            glVertex2d(balls[i].xcenter,balls[i].ycenter);
            x = 10 * cos(j);
            y = 10 * sin(j);
            glVertex2d(balls[i].xcenter+x,balls[i].ycenter+y);
            x = 10 * cos(j+0.1);
            y = 10 * sin(j+0.1);
            glVertex2d(balls[i].xcenter+x,balls[i].ycenter+y);
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
	RenderString(-600.0f, 300.0f, GLUT_BITMAP_TIMES_ROMAN_24);


    glutSwapBuffers();
}
void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);
    for( int i = 0; i < min(nextfree,99) ; i++ ){
        if(balls[i].gone){continue;}
        balls[i].ballboard==1 ? balls[i].ycenter-=3 : balls[i].ycenter+=3;
        if(balls[i].ycenter>285 || balls[i].ycenter<-285){
            balls[i].gone=1;
        }
    }
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
