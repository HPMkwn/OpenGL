/**
 * Computer Graphics project 
 * 
 * Subject : Save the ball going to wards your head
 * 
 * 
 * Herat Makwana(U17CO015)
 * Jiten Vagadiya(U17CO030)
*/

#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

float xcenter = 0.0, ycenter = 0.0, zcenter = 0.0;
bool gone = false;
bool xdir = true, ydir = true, zdir = true;

// float ballAt[3] = {1.5, 0.0, -5.8};
float plateAt[3] = {0.0, 0.0, -3.0};
int score = 5;
int speed = 0.02;
int hits = 0;

void RenderString(float x, float y, void *font, int player)
{

    glColor3f(0.0, 0.0, 1.0);
    glRasterPos2f(x, y);
    stringstream ss;
    string str = ss.str();
    string showstring = "Score " + score;
    for (unsigned int i = 0; i < showstring.length(); i++)
        glutBitmapCharacter(font, showstring[i]);
}

void display()
{
    if(score){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-2.0, -1.5, 0.0);
    glBegin(GL_QUADS);
    glColor3f(0.4, 0.4, 0.4);
    glVertex3f(0.0, 0.0, -3.0);
    glVertex3f(4.0, 0.0, -3.0);
    glVertex3f(4.0, 0.0, -6.0);
    glVertex3f(0.0, 0.0, -6.0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(0.0, 0.0, -6.0);
    glVertex3f(4.0, 0.0, -6.0);
    glVertex3f(4.0, 3.0, -6.0);
    glVertex3f(0.0, 3.0, -6.0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.3, 0.3);
    glVertex3f(0.0, 0.0, -3.0);
    glVertex3f(0.0, 0.0, -6.0);
    glVertex3f(0.0, 3.0, -6.0);
    glVertex3f(0.0, 3.0, -3.0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.3, 0.3);
    glVertex3f(4.0, 0.0, -3.0);
    glVertex3f(4.0, 0.0, -6.0);
    glVertex3f(4.0, 3.0, -6.0);
    glVertex3f(4.0, 3.0, -3.0);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    glLoadIdentity();
    if (gone)
    {
        glTranslatef(xcenter, ycenter, zcenter);
        glutWireSphere(0.2, 10, 12);
    }
    glLoadIdentity();
    glTranslatef(plateAt[0], plateAt[1], plateAt[2]);
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.7, 0.7);
    glVertex3f(-0.3, -0.3, 0.0);
    glVertex3f(-0.3, 0.3, 0.0);
    glVertex3f(0.3, 0.3, 0.0);
    glVertex3f(0.3, -0.3, 0.0);
    glEnd();

    RenderString(500.0f, -300.0f, GLUT_BITMAP_TIMES_ROMAN_24, 1);

    glutSwapBuffers();
    }else{
        gone = false;
    }
}
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)w / (float)h, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}
void initialize()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}
void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);

    if (xcenter <= -1.8 || xcenter >= 1.8)
    {
        xdir = xdir ? false : true;
    }
    if (ycenter <= -1.3 || ycenter >= 1.3)
    {
        ydir = ydir ? false : true;
    }
    if (zcenter <= -5.8)
    {
        zdir = zdir ? false : true;
    }
    if (zcenter >= -3.2 && xcenter < plateAt[0] + 0.3 && xcenter > plateAt[0] - 0.3 && ycenter < plateAt[1] + 0.3 && ycenter > plateAt[1] - 0.3)
    {
        zdir = zdir ? false : true;
    }
    else if (zcenter > -3.2)
    {
        if (gone && score!=0)
        {
            score--;
            if(score ==0){cout<<"game over";exit(0);}
            printf("Life left %d\n", score);
            gone = false;
        }
    }

    xdir ? xcenter += 0.02 : xcenter -= 0.02;
    ydir ? ycenter += 0.02 : ycenter -= 0.02;
    zdir ? zcenter += 0.02 : zcenter -= 0.02;
}
void processNormalKeys(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ' ':
        if (!gone && score!=0)
        {
            gone = true;
            xcenter = 0.0;
            ycenter = 0.0;
            zcenter = -5.8;
            xdir = true;
            ydir = true;
            zdir = false;
        }
        break;
    case 'a':
        plateAt[0] = max(-1.7, plateAt[0] - 0.2);
        break;
    case 'd':
        plateAt[0] = min(1.7, plateAt[0] + 0.2);
        break;
    case 'w':
        plateAt[1] = min(1.2, plateAt[1] + 0.2);
        break;
    case 's':
        plateAt[1] = max(-1.2, plateAt[1] - 0.2);
        break;
    }
}

void processSpecialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        plateAt[0] = max(-1.7, plateAt[0] - 0.2);
        break;
    case GLUT_KEY_RIGHT:
        plateAt[0] = min(1.7, plateAt[0] + 0.2);
        break;
    case GLUT_KEY_UP:
        plateAt[1] = min(1.2, plateAt[1] + 0.2);
        break;
    case GLUT_KEY_DOWN:
        plateAt[1] = max(-1.2, plateAt[1] - 0.2);
        break;
    case GLUT_KEY_PAGE_UP:
        plateAt[1] = min(1.2, plateAt[1] + 0.2);
        plateAt[0] = min(1.7, plateAt[0] + 0.2);
        break;
    case GLUT_KEY_PAGE_DOWN:
        plateAt[1] = max(-1.2, plateAt[1] - 0.2);
        plateAt[0] = min(1.7, plateAt[0] + 0.2);
        break;
    case GLUT_KEY_HOME:
        plateAt[1] = min(1.2, plateAt[1] + 0.2);
        plateAt[0] = max(-1.7, plateAt[0] - 0.2);
        break;
    case GLUT_KEY_END:
        plateAt[1] = max(-1.2, plateAt[1] - 0.2);
        plateAt[0] = max(-1.7, plateAt[0] - 0.2);
        break;
    }
}

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("3D Ball");

    initialize();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(10, timer, 0);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    glutMainLoop();

    return 0;
}
