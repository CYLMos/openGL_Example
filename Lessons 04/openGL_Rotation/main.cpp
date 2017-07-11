#include <iostream>
#include <windows.h>
#include <glut.h>
#include <GL/glu.h>
#include <cstdio>

using namespace std;

float rv = 0.0;

void windowsFunc(int w, int h){
    printf("The window size is %d X %d\n", w, h);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -10, 10);
}

void display(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
         glRotatef(rv, 1, 0, 1);
         glBegin(GL_QUADS);
            glVertex3f(-5.0f, 5.0f, 0.0f); // Top Left Of The Quad
            glColor3f(1, 1, 0);
            glVertex3f(5.0f, 5.0f, 0.0f); // Top Right Of The Quad
            glColor3f(1, 0, 0);
            glVertex3f(5.0f, -5.0f, 0.0f); // Bottom Right Of The Quad
            glColor3f(0, 1, 0);
            glVertex3f(-5.0f, -5.0f, 0.0f); // Bottom Left Of The Quad
            glColor3f(1, 0, 0);
        glEnd();
    glPopMatrix();

    glutSwapBuffers();

}

void timer(int value){
    glutTimerFunc(50, timer, 2);

    rv -= value;
    glutPostRedisplay();
}

int main(int argv, char* argc[])
{
    glutInit(&argv, argc);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(400, 80);
    glutCreateWindow("Rotation");

    glutReshapeFunc(windowsFunc);
    glutDisplayFunc(display);
    glutTimerFunc(50, timer, 2);

    glutMainLoop();

    return 0;
}
