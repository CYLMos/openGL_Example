#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <cstdio>

using namespace std;

float rv = 0.0;

void windowsFunc(int w, int h){
    printf("The window size is %d X %d\n", w, h);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_LIGHT3);
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();
    glOrtho(-6, 6, -6, 6, -6, 6);
}

void display(){
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float p1[3] = {0.0, 0.0, 6.0};
    float p2[3] = {-6.0, 0.0, 0.0};
    float p3[3] = {0.0, -6.0, 0.0};
    float p4[3] = {0.0, 6.0, 0.0};
    float p5[3] = {6.0, 0.0, 0.0};

    glPushMatrix();
        glRotatef(rv, 1, 1, 0);
        glBegin(GL_TRIANGLES);
            glColor3f(0 , 0 , 0);
            glVertex3f(0.0, 0.0, 6.0);
            glColor3f(1, 1, 0);
            glVertex3f(-6.0, 0.0, 0.0);
            glColor3f(0, 1, 0);
            glVertex3f(0.0, 6.0, 0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glColor3f(0 , 0 , 0);
            glVertex3f(0.0, 0.0, 6.0);
            glColor3f(0, 1, 0);
            glVertex3f(0.0, 6.0, 0.0);
            glColor3f(0 , 0 , 1);
            glVertex3f(6.0, 0.0, 0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glColor3f(0 , 0 , 0);
            glVertex3f(0.0, 0.0, 6.0);
            glColor3f(1, 0, 0);
            glVertex3f(0.0, -6.0, 0.0);
            glColor3f(0 , 0 , 1);
            glVertex3f(6.0, 0.0, 0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glColor3f(0 , 0 , 0);
            glVertex3f(0.0, 0.0, 6.0);
            glColor3f(1, 1, 0);
            glVertex3f(-6.0, 0.0, 0.0);
            glColor3f(1, 0, 0);
            glVertex3f(0.0, -6.0, 0.0);
        glEnd();

        glBegin(GL_QUADS);
            glColor3f(0 , 0 , 1);
            glVertex3f(6.0, 0.0, 0.0);
            glColor3f(0, 1, 0);
            glVertex3f(0.0, 6.0, 0.0);
            glColor3f(1, 1, 0);
            glVertex3f(-6.0, 0.0, 0.0);
            glColor3f(1, 0, 0);
            glVertex3f(0.0, -6.0, 0.0);
        glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

void timer(int value){
    glutTimerFunc(50, timer, 10);

    rv -= value;
    glutPostRedisplay();
}


int main(int argv, char* argc[])
{
    glutInit(&argv, argc);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(400, 80);
    glutCreateWindow("3D Shapes");

    glutReshapeFunc(windowsFunc);
    glutDisplayFunc(display);
    glutTimerFunc(50, timer, 10);

    glutMainLoop();

    return 0;
}
