#include <iostream>
#include <windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdio>

#include <highgui.hpp>
#include <cv.h>

using namespace std;
using namespace cv;

GLUquadric* quadric;
float angle = 0.0;

void textureInit(char* path){
    IplImage* image = cvLoadImage("lena.jpg");

    cvCvtColor(image, image, CV_BGR2RGB);

    quadric = gluNewQuadric();
    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->imageData);
}

void windowsFunc(int w, int h){
    printf("The window size is %d X %d\n", w, h);
    glViewport(0, 0, w, h);

    glOrtho(-10, 10, -10, 10, -10, 10);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
        glRotated(90, 1, 0, 0);
        glRotated(angle, 0, 0, 1);
        gluQuadricTexture(quadric, 1);
        gluSphere(quadric, 5, 30, 30);
    glPopMatrix();

    //angle -= 1;

    glutSwapBuffers();
}

void timer(int value){
    glutTimerFunc(20, timer, 1);

    angle -= 1;
    glutPostRedisplay();
}

int main(int argv, char* argc[])
{
    glutInit(&argv, argc);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(400, 80);
    glutCreateWindow("Texture Mapping");

    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    textureInit("lena.jpg");

    glutReshapeFunc(windowsFunc);
    glutDisplayFunc(display);
    //glutIdleFunc(display);
    glutTimerFunc(20, timer, 1);

    glutMainLoop();

    return 0;
}
