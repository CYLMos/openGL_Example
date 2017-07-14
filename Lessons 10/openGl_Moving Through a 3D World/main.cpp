#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <cmath>

#include <highgui.hpp>
#include <cv.h>

using namespace std;
using namespace cv;

GLuint texture;

typedef struct{
    GLfloat x, y, z;
}Vertex;

typedef struct{
    Vertex vertexs[4];
}Quads;

class Cube{
    public:
        Cube(GLfloat x, GLfloat y, GLfloat z){
            // First Face
            quads[0].vertexs[0].x = x;
            quads[0].vertexs[0].y = y;
            quads[0].vertexs[0].z = z;

            quads[0].vertexs[1].x = x;
            quads[0].vertexs[1].y = y - 2*abs(y);
            quads[0].vertexs[1].z = z;

            quads[0].vertexs[2].x = x + 2*abs(x);
            quads[0].vertexs[2].y = y - 2*abs(y);
            quads[0].vertexs[2].z = z;

            quads[0].vertexs[3].x = x + 2*abs(x);
            quads[0].vertexs[3].y = y;
            quads[0].vertexs[3].z = z;

            // Second Face
            quads[1].vertexs[0].x = x;
            quads[1].vertexs[0].y = y;
            quads[1].vertexs[0].z = z + 4.0f;

            quads[1].vertexs[1].x = x;
            quads[1].vertexs[1].y = y;
            quads[1].vertexs[1].z = z;

            quads[1].vertexs[2].x = x;
            quads[1].vertexs[2].y = y - 2*abs(y);
            quads[1].vertexs[2].z = z;

            quads[1].vertexs[3].x = x;
            quads[1].vertexs[3].y = y - 2*abs(y);
            quads[1].vertexs[3].z = z + 4.0f;

            // Third Face
            quads[2].vertexs[0].x = x;
            quads[2].vertexs[0].y = y - 2*abs(y);
            quads[2].vertexs[0].z = z + 4.0f;

            quads[2].vertexs[1].x = x;
            quads[2].vertexs[1].y = y - 2*abs(y);
            quads[2].vertexs[1].z = z;

            quads[2].vertexs[2].x = x + 2*abs(x);
            quads[2].vertexs[2].y = y - 2*abs(y);
            quads[2].vertexs[2].z = z;

            quads[2].vertexs[3].x = x + 2*abs(x);
            quads[2].vertexs[3].y = y - 2*abs(y);
            quads[2].vertexs[3].z = z + 4.0f;

            //Fourth Face
            quads[3].vertexs[0].x = x + 2*abs(x);
            quads[3].vertexs[0].y = y - 2*abs(y);
            quads[3].vertexs[0].z = z + 4.0f;

            quads[3].vertexs[1].x = x + 2*abs(x);
            quads[3].vertexs[1].y = y - 2*abs(y);
            quads[3].vertexs[1].z = z;

            quads[3].vertexs[2].x = x + 2*abs(x);
            quads[3].vertexs[2].y = y;
            quads[3].vertexs[2].z = z;

            quads[3].vertexs[3].x = x + 2*abs(x);
            quads[3].vertexs[3].y = y;
            quads[3].vertexs[3].z = z + 4.0f;

            //Fifth Face
            quads[4].vertexs[0].x = x + 2*abs(x);
            quads[4].vertexs[0].y = y;
            quads[4].vertexs[0].z = z + 4.0f;

            quads[4].vertexs[1].x = x + 2*abs(x);
            quads[4].vertexs[1].y = y;
            quads[4].vertexs[1].z = z;

            quads[4].vertexs[2].x = x;
            quads[4].vertexs[2].y = y;
            quads[4].vertexs[2].z = z;

            quads[4].vertexs[3].x = x;
            quads[4].vertexs[3].y = y;
            quads[4].vertexs[3].z = z + 4.0f;

            //Sixth Face
            quads[5].vertexs[0].x = x;
            quads[5].vertexs[0].y = y;
            quads[5].vertexs[0].z = z + 4.0f;

            quads[5].vertexs[1].x = x;
            quads[5].vertexs[1].y = y - 2*abs(y);
            quads[5].vertexs[1].z = z + 4.0f;

            quads[5].vertexs[2].x = x + 2*abs(x);
            quads[5].vertexs[2].y = y - 2*abs(y);
            quads[5].vertexs[2].z = z + 4.0f;

            quads[5].vertexs[3].x = x + 2*abs(x);
            quads[5].vertexs[3].y = y;
            quads[5].vertexs[3].z = z + 4.0f;
        }

        void draw(){
            for(int i = 0; i < 6; i++){
                if(i == 0)glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
                if(i == 1)glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
                if(i == 2)glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
                if(i == 3)glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
                if(i == 4)glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
                if(i == 5)glColor4f(0.0f, 1.0f, 1.0f, 1.0f);

                glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f);glVertex3f(this->quads[i].vertexs[0].x, this->quads[i].vertexs[0].y, this->quads[i].vertexs[0].z);
                    glTexCoord2f(0.0f, 1.0f);glVertex3f(this->quads[i].vertexs[1].x, this->quads[i].vertexs[1].y, this->quads[i].vertexs[1].z);
                    glTexCoord2f(1.0f, 1.0f);glVertex3f(this->quads[i].vertexs[2].x, this->quads[i].vertexs[2].y, this->quads[i].vertexs[2].z);
                    glTexCoord2f(1.0f, 0.0f);glVertex3f(this->quads[i].vertexs[3].x, this->quads[i].vertexs[3].y, this->quads[i].vertexs[3].z);
                glEnd();
            }
        }

    private:
        Quads quads[6];
};

Cube cube(-2.0f, 2.0f, 0.0f);
Quads Floor;

GLfloat myPIOVER180 = 0.0174532925f;

GLfloat myPositionX = 0.0f;
GLfloat myPositionY = 0.5f;
GLfloat myPositionZ = 15.0f;

GLfloat myRotation = 0.0f;

GLfloat myLookUpDown = 0.0f;

GLfloat mouseLastX = 0.0f;
GLfloat mouseLastY = 0.0f;

int centerX;
int centerY;

bool resetMouseCenter = false;

void textureInit(){
    IplImage* image = cvLoadImage("nagato.jpg");

    cvCvtColor(image, image, CV_BGR2RGB);

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

    gluPerspective (45.0f, (GLfloat)w / (GLfloat)h, 0.1, 100);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //gluLookAt(8.0f, 8.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    GLfloat transX = -myPositionX;
    GLfloat transY = -myPositionY;
    GLfloat transZ = -myPositionZ;
    GLfloat rotation = 360.0f - myRotation;

    glRotatef(myLookUpDown, 1.0f, 0.0f, 0.0f);
    glRotatef(rotation, 0.0f, 1.0f, 0.0f);
    glTranslatef(transX, transY, transZ);

    glBindTexture(GL_TEXTURE_2D, texture);
    cube.draw();

    //Floor
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);glVertex3f(Floor.vertexs[0].x, Floor.vertexs[0].y, Floor.vertexs[0].z);
        glTexCoord2f(0.0f, 1.0f);glVertex3f(Floor.vertexs[1].x, Floor.vertexs[1].y, Floor.vertexs[1].z);
        glTexCoord2f(1.0f, 1.0f);glVertex3f(Floor.vertexs[2].x, Floor.vertexs[2].y, Floor.vertexs[2].z);
        glTexCoord2f(1.0f, 0.0f);glVertex3f(Floor.vertexs[3].x, Floor.vertexs[3].y, Floor.vertexs[3].z);
    glEnd();

    glutSwapBuffers();
}

void keyBoardFunc(unsigned char key, int x, int y){
    switch(key){
        case 'w':
            myPositionX -= float(sin(myRotation * myPIOVER180));
            myPositionZ -= float(cos(myRotation * myPIOVER180));
            glutPostRedisplay();
            break;

        case 's':
            myPositionX += float(sin(myRotation * myPIOVER180));
            myPositionZ += float(cos(myRotation * myPIOVER180));
            glutPostRedisplay();
            break;

        case 'd':
            myPositionX += float(cos(myRotation * myPIOVER180));
            myPositionZ -= float(sin(myRotation * myPIOVER180));
            glutPostRedisplay();
            break;

        case 'a':
            myPositionX -= float(cos(myRotation * myPIOVER180));
            myPositionZ += float(sin(myRotation * myPIOVER180));
            glutPostRedisplay();
            break;

        case 'e':
            myLookUpDown += 0.05f;
            glutPostRedisplay();
            break;
        case 'q':
            myLookUpDown -= 0.05f;
            glutPostRedisplay();
            break;
        }
}

void mouseMovementFunc(int x, int y){
    if(resetMouseCenter == false){
        int mouseDiffX = x - mouseLastX;
        int mouseDiffY = y - mouseLastY;

        mouseLastX = x;
        mouseLastY = y;

        myRotation -= (GLfloat)mouseDiffX * 0.5f;
        if(myRotation > 360.0f){
            myRotation -= 360.0f;
        }
        if(myRotation < 0.0f){
            myRotation = 360.0f;
        }
        myLookUpDown += (GLfloat)mouseDiffY * 0.5f;

        if((int)mouseLastX != centerX && (int)mouseLastY != centerY){
            resetMouseCenter = true;
        }
    }

    else if(resetMouseCenter == true){
        glutWarpPointer(centerX, centerY);
        mouseLastX = centerX;
        mouseLastY = centerY;

        resetMouseCenter = false;
    }
    //glutPostRedisplay();
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(400, 80);
    glutCreateWindow("Moving Through a 3D World");

    glMatrixMode(GL_PROJECTION);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    textureInit();

    Floor.vertexs[0].x = 0.0f;
    Floor.vertexs[0].y = -2.0f;
    Floor.vertexs[0].z = 1000.0f;
    Floor.vertexs[1].x = -1000.0f;
    Floor.vertexs[1].y = -2.0f;
    Floor.vertexs[1].z = 0.0f;
    Floor.vertexs[2].x = 0.0f;
    Floor.vertexs[2].y = -2.0f;
    Floor.vertexs[2].z = -1000.0f;
    Floor.vertexs[3].x = 1000.0f;
    Floor.vertexs[3].y = -2.0f;
    Floor.vertexs[3].z = 0.0f;

    mouseLastX = centerX = 800/2;
    mouseLastY = centerY = 800/2;

    glutSetCursor(GLUT_CURSOR_NONE);

    glutWarpPointer(mouseLastX, mouseLastY);

    glutReshapeFunc(windowsFunc);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyBoardFunc);
    glutPassiveMotionFunc(mouseMovementFunc);

    glutMainLoop();

    return 0;
}
