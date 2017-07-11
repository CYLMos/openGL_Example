#include <iostream>
#include <cstdio>

#include <windows.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <highgui.hpp>
#include <cv.hpp>

using namespace std;

//GLUQuadric* quadric;
float angle = 0.0;
GLuint texture[2];
IplImage** image;

void textureInit(){
    char** path = new char*[2];
    path[0] = "lena.jpg";
    path[1] = "nagato.jpg";

    image = new IplImage*[2];
    image[0] = cvLoadImage(path[0]);
    image[1] = cvLoadImage(path[1]);

    cvCvtColor(image[0], image[0], CV_BGR2RGB);
    cvCvtColor(image[1], image[1], CV_BGR2RGB);

    glGenTextures(2, texture);

    for(int i = 0; i < 2; i++){
        glBindTexture(GL_TEXTURE_2D, texture[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[i]->width, image[i]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image[i]->imageData);
    }
}

void windowsFunc(int w, int h){
    printf("The window size is %d X %d\n", w, h);

    glViewport(0, 0, w, h);
    glOrtho(-10, 10, -10, 10, -20, 20);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float point1[3] = {0.0, 6.0, 0.0};
    float point2[3] = {-6.0, 0.0, 0.0};
    float point3[3] = {0.0, -6.0, 0.0};
    float point4[3] = {6.0, 0.0, 0.0};
    float point5[3] = {0.0, 6.0, 6.0};
    float point6[3] = {-6.0, 0.0, 6.0};
    float point7[3] = {0.0, -6.0, 6.0};
    float point8[3] = {6.0, 0.0, 6.0};

    gluLookAt(6, 6, 3, 0, 0, 0, 0, 0, 1);

    glPushMatrix();

    glRotated(angle, 0, 0, 1);
    // Bottom Face
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);glVertex3f(point1[0],point1[1], point1[2]);
        glTexCoord2f(0.0, 1.0);glVertex3f(point2[0],point2[1], point2[2]);
        glTexCoord2f(1.0, 1.0);glVertex3f(point3[0],point3[1], point3[2]);
        glTexCoord2f(1.0, 0.0);glVertex3f(point4[0],point4[1], point4[2]);
    glEnd();

    // Top Face
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);glVertex3f(point5[0],point5[1], point5[2]);
        glTexCoord2f(0.0, 1.0);glVertex3f(point6[0],point6[1], point6[2]);
        glTexCoord2f(1.0, 1.0);glVertex3f(point7[0],point7[1], point7[2]);
        glTexCoord2f(1.0, 0.0);glVertex3f(point8[0],point8[1], point8[2]);
    glEnd();

    //Other
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);glVertex3f(point5[0],point5[1], point5[2]);
        glTexCoord2f(0.0, 1.0);glVertex3f(point1[0],point1[1], point1[2]);
        glTexCoord2f(1.0, 1.0);glVertex3f(point2[0],point2[1], point2[2]);
        glTexCoord2f(1.0, 0.0);glVertex3f(point6[0],point6[1], point6[2]);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);glVertex3f(point6[0],point6[1], point6[2]);
        glTexCoord2f(0.0, 1.0);glVertex3f(point2[0],point2[1], point2[2]);
        glTexCoord2f(1.0, 1.0);glVertex3f(point3[0],point3[1], point3[2]);
        glTexCoord2f(1.0, 0.0);glVertex3f(point7[0],point7[1], point7[2]);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);glVertex3f(point7[0],point7[1], point7[2]);
        glTexCoord2f(0.0, 1.0);glVertex3f(point3[0],point3[1], point3[2]);
        glTexCoord2f(1.0, 1.0);glVertex3f(point4[0],point4[1], point4[2]);
        glTexCoord2f(1.0, 0.0);glVertex3f(point8[0],point8[1], point8[2]);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);glVertex3f(point8[0],point8[1], point8[2]);
        glTexCoord2f(0.0, 1.0);glVertex3f(point4[0],point4[1], point4[2]);
        glTexCoord2f(1.0, 1.0);glVertex3f(point1[0],point1[1], point1[2]);
        glTexCoord2f(1.0, 0.0);glVertex3f(point5[0],point5[1], point5[2]);
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

void timer(int value){
    glutTimerFunc(20, timer, 2);

    angle -= 2;
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(400, 80);
    glutCreateWindow("TextureMappingPlural");

    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    textureInit();

    glutReshapeFunc(windowsFunc);
    glutDisplayFunc(display);
    glutTimerFunc(20, timer, 2);

    glutMainLoop();

    return 0;
}
