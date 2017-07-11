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
GLfloat myPositionZ = 15.0f;

GLfloat myRotation = 0.0f;

GLfloat myLookUpDown = 0.0f;

//GLuint texture;

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

    GLfloat x, y, z;
    GLfloat transX = -myPositionX;
    GLfloat transY = -0.5f;
    GLfloat transZ = -myPositionZ;
    GLfloat rotation = 360.0f - myRotation;

    glRotatef(rotation, 0.0f, 1.0f, 0.0f);
    glRotatef(myLookUpDown, 1.0f, 0.0f, 0.0f);
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
    float xrotrad, yrotrad;
    switch(key){
        case 'w':
            myPositionX -= float(sin(myRotation * myPIOVER180)) ;
            myPositionZ -= float(cos(myRotation * myPIOVER180)) ;
            glutPostRedisplay();
            break;

        case 's':
            myPositionX += float(sin(myRotation * myPIOVER180)) ;
            myPositionZ += float(cos(myRotation * myPIOVER180)) ;
            glutPostRedisplay();
            break;

        case 'd':
            myRotation -= 1.5f;
            if(myRotation < 0.0f){
                myRotation = 360.0f;
            }
            glutPostRedisplay();
            break;

        case 'a':
            myRotation += 1.5f;
            if(myRotation > 360.0f){
                myRotation -= 360.0f;
            }
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

void timer(int value){
    glutTimerFunc(20, timer, 2);

    glutPostRedisplay();
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
    //glShadeModel (GL_SMOOTH);
    //glEnable(GL_BLEND);

    //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    //gluPerspective( 0, 800/800, 1.0, 500.0);

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

    glutReshapeFunc(windowsFunc);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyBoardFunc);
    //glutTimerFunc(20, timer, 2);

    glutMainLoop();

    return 0;
}

/*#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
//angle of rotation
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle=0.0;

float lastx, lasty;

//positions of the cubes
float positionz[10];
float positionx[10];

void cubepositions (void) { //set the positions of the cubes

    for (int i=0;i<10;i++)
    {
    positionz[i] = rand()%5 + 5;
    positionx[i] = rand()%5 + 5;
    }
}

//draw the cube
void cube (void) {
    for (int i=0;i<10;i++)
    {
    glPushMatrix();
    glTranslated(-positionx[i + 1] * 10, 0, -positionz[i + 1] *
10); //translate the cube
    glutSolidCube(2); //draw the cube
    glPopMatrix();
    }
}

void init (void) {
cubepositions();
}

void enable (void) {
    glEnable (GL_DEPTH_TEST); //enable the depth testing
    glEnable (GL_LIGHTING); //enable the lighting
    glEnable (GL_LIGHT0); //enable LIGHT0, our Diffuse Light
    glShadeModel (GL_SMOOTH); //set the shader to smooth shader

}

void camera (void) {
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on teh
//x-axis (left and right)
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the
//y-axis (up and down)
    glTranslated(-xpos,-ypos,-zpos); //translate the screento the position of our camera
}

void display (void) {
    glClearColor (0.0,0.0,0.0,1.0); //clear the screen to black
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glLoadIdentity();
    camera();
    enable();
    cube(); //call the cube drawing function
    glutSwapBuffers(); //swap the buffers
    angle++; //increase the angle
}



void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection

    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0
); //set the perspective (angle of sight, width, height, ,depth)
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model

}

void keyboard (unsigned char key, int x, int y) {
    if (key=='q')
    {
    xrot += 1;
    if (xrot >360) xrot -= 360;
    }

    if (key=='z')
    {
    xrot -= 1;
    if (xrot < -360) xrot += 360;
    }

    if (key=='w')
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f);
    xpos += float(sin(yrotrad)) ;
    zpos -= float(cos(yrotrad)) ;
    ypos -= float(sin(xrotrad)) ;
    }

    if (key=='s')
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f);
    xpos -= float(sin(yrotrad));
    zpos += float(cos(yrotrad)) ;
    ypos += float(sin(xrotrad));
    }

    if (key=='d')
    {
    float yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xpos += float(cos(yrotrad)) * 0.2;
    zpos += float(sin(yrotrad)) * 0.2;
    }

    if (key=='a')
    {
    float yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xpos -= float(cos(yrotrad)) * 0.2;
    zpos -= float(sin(yrotrad)) * 0.2;
    }

    if (key==27)
    {
    exit(0);
    }
}

void mouseMovement(int x, int y) {
    int diffx=x-lastx; //check the difference between the current x and the last x position
    int diffy=y-lasty; //check the difference between the current y and the last y position
    lastx=x; //set lastx to the current x position
    lasty=y; //set lasty to the current y position
    xrot += (float) diffy; //set the xrot to xrot with the addition of the difference in the y position
    yrot += (float) diffx;    //set the xrot to yrot with the addition of the difference in the x position
}

int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("A basic OpenGL Window");
    init ();
    glutDisplayFunc (display);
    glutIdleFunc (display);
    glutReshapeFunc (reshape);

    glutPassiveMotionFunc(mouseMovement); //check for mouse movement

    glutKeyboardFunc (keyboard);
    glutMainLoop ();
    return 0;
}*/
