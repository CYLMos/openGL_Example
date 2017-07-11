#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdio>
#include <cstdlib>
#include <time.h>

#include <highgui.hpp>
#include <cv.h>

using namespace std;
using namespace cv;

GLuint texture;
IplImage* image;
GLfloat zoom = 0.0f;

bool stopFlag = true;
bool twinkle = false;

typedef struct{
    int r, g, b; //顏色
    GLfloat distance; //距離中心距離
    GLfloat angle; //當前角度
}
starStruct;

int randomSeed[10] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
int num = 10;

class Star{
    public:
        Star(int seed){
            srand(seed);

            this->star.r = rand() % 256;
            this->star.g = rand() % 256;
            this->star.b = rand() % 256;

            this->star.angle = 0.0;
            this->star.distance = rand() % 5;
        }

        void draw(){
            glBindTexture(GL_TEXTURE_2D, texture);

            glColor4ub(this->star.r, this->star.g, this->star.b, 255);  //Full Color, 50% Alpha
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0);glVertex3f(-1.0f, -1.0f, 0.0f);
                glTexCoord2f(0.0, 1.0);glVertex3f(1.0f, -1.0f, 0.0f);
                glTexCoord2f(1.0, 1.0);glVertex3f(1.0f, 1.0f, 0.0f);
                glTexCoord2f(1.0, 0.0);glVertex3f(-1.0f, 1.0f, 0.0f);
            glEnd();
        }

        void drawLighter(int r, int g, int b){
            glBindTexture(GL_TEXTURE_2D, texture);

            glColor4ub(r, g, b, 255);  //Full Color, 50% Alpha
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0);glVertex3f(-1.0f, -1.0f, 0.0f);
                glTexCoord2f(0.0, 1.0);glVertex3f(1.0f, -1.0f, 0.0f);
                glTexCoord2f(1.0, 1.0);glVertex3f(1.0f, 1.0f, 0.0f);
                glTexCoord2f(1.0, 0.0);glVertex3f(-1.0f, 1.0f, 0.0f);
            glEnd();
        }

        GLfloat getSpin(){
            return this->spin;
        }
        void setSpin(GLfloat value){
            this->spin = value;
        }

        starStruct getStarStruct(){
            return this->star;
        }
        void setStarStruct(starStruct value){
            this->star = value;
        }

    private:
        starStruct star;
        GLfloat spin = 0.0f;
};

Star* stars[10];

void windowsFunc(int w, int h){
    printf("The window size is %d X %d\n", w, h);

    glViewport(0, 0, w, h);
    glOrtho(-10, 10, -10, 10, -1000, 1000);
}

void textureInit(){
    char* path = "nagato.jpg";

    image = cvLoadImage(path, CV_LOAD_IMAGE_UNCHANGED);;

    cvCvtColor(image, image, CV_BGR2RGB);

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->imageData);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    for(int i = 0; i < num; i++){
        glRotatef(stars[i]->getSpin(), 0.0f, 0.0f, 1.0f);
        glTranslatef(stars[i]->getStarStruct().distance, 0.0f, 0.0f);

        glPushMatrix();

        glRotatef(stars[i]->getStarStruct().angle, 0.0f, 0.0f, 1.0f);
        if(twinkle){
            stars[i]->drawLighter(stars[9 - i]->getStarStruct().r, stars[9 - i]->getStarStruct().g, stars[9 - i]->getStarStruct().b);
        }
        stars[i]->draw();

        glPopMatrix();
    }

    glPopMatrix();

    glutSwapBuffers();
}

void timer(int value){
    if(stopFlag == true){
        glutTimerFunc(20, timer, 2.0);

        for(int i = 0; i < num; i++){
            starStruct temp = stars[i]->getStarStruct();
            temp.angle += 6.0f;
            stars[i]->setStarStruct(temp);

            stars[i]->setSpin(stars[i]->getSpin() + 1.0f);
        }
        glutPostRedisplay();
    }
}

void keyBoardFunc(unsigned char key, int x, int y){
    switch(key){
        case 'S':
            stopFlag = !stopFlag;
            glutTimerFunc(20, timer, 2);
            break;
        case 's':
            stopFlag = !stopFlag;
            glutTimerFunc(20, timer, 2);
            break;
        case 32:  //Space
            twinkle = !twinkle;
            break;
    }
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(400, 80);
    glutCreateWindow("Moving Bitmap in 3D Shape");

    glMatrixMode(GL_PROJECTION);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    textureInit();

    glBlendFunc(GL_SRC_ALPHA,GL_ONE);  //設定混合參數

    for(int i = 0; i < num; i++){
        stars[i] = new Star(randomSeed[i]);
    }

    glutReshapeFunc(windowsFunc);
    glutDisplayFunc(display);
    glutTimerFunc(20, timer, 2);
    glutKeyboardFunc(keyBoardFunc);
    glutMainLoop();


    return 0;
}
