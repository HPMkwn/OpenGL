#include <GL/glut.h>
#include <bits/stdc++.h>

struct Ball
{
    int xcenter, ycenter, zcenter;
    bool gone;
    bool xdir, ydir, zdir;
    Ball() : xcenter(0), ycenter(0), zcenter(0), xdir(0), ydir(0), zdir(0), gone(false) {}
};

Ball ball;



float ballAt[3] = {1.5, 0.0, -5.8};
float plateAt[3] = {0.0, 0.0, -3.0};
void display()
{
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
    glTranslatef(ballAt[0], ballAt[1], ballAt[2]);
    glutWireSphere(0.2, 10, 12);
    glLoadIdentity();
    glTranslatef(plateAt[0], plateAt[1], plateAt[2]);
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.7, 0.7);
    glVertex3f(-0.3, -0.3, 0.0);
    glVertex3f(-0.3, 0.3, 0.0);
    glVertex3f(0.3, 0.3, 0.0);
    glVertex3f(0.3, -0.3, 0.0);
    glEnd();
    glutSwapBuffers();
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
    ballAt[2] += 0.02;
    if (ballAt[2] > -3.2)
    {
        ballAt[2] = -5.8;
    }
}
void keyboard(int key, int x, int y)
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
    glutSpecialFunc(keyboard);
    glutMainLoop();

    return 0;
}
