#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <glut.h>


using namespace std;

void WindowSize(int w, int h)
{
    cout << "目前視窗大小為"; cout << w; cout << "X"; cout << h; cout << "\n";
    glViewport(0, 0, w, h); //當視窗長寬改變時，畫面也跟著變
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10,10,-10,10,-10,10); //正交投影
}

void drawMyPolygon(void){

    glClearColor(0.0, 0.0, 0.0, 0.0);   //用白色塗背景
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_TRIANGLES);
       glColor3ub( 255, 0, 255);glVertex3f( 8.6603, -5, 0);
       glColor3ub( 255, 255, 0);glVertex3f(      0, 10, 0);
       glColor3ub( 0, 255, 255);glVertex3f(-8.6603, -5, 0);
    glEnd();
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400,400);
    glutInitWindowPosition(600,80);
    glutCreateWindow("測試");

    glutReshapeFunc(WindowSize);
    glutDisplayFunc(drawMyPolygon);
    glutMainLoop();

    return 0;
}
