/****************************************************************************/
/* Prac. 5A Polygonal mesh with triangles                                        */
/****************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
// OSX systems need their own headers
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif
// Use of degrees is deprecated. Use radians for GLM functions
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <time.h>
#include <math.h>
#include "transformation.h"
#include "extras.h"
#include "piezas.h"
#define PI 3.14159265f

#define objReina 1
#define objCaballo 2
#define objPeon 3
#define objAlfil 4
#define objTorre 5
#define objRey 6
// Global variables
int windowWidth  = 500;     // Initial Screen and viewport width 
int windowHeight = 500;     // Initil Screen and viewport height

GLfloat zValue=1000;
 GLfloat xRotated, yRotated, zRotated;
  GLfloat angleTheta[] = {0.0,0.0,0.0};
 GLint axis = 2;
GLfloat windowXMax, windowXMin, windowYMax, windowYMin; // window bounds
// Projection window/clipping/work area
GLdouble windowAreaXLeft, windowAreaXRight, windowAreaYBottom, windowAreaYTop;

void DrawAxis(void){
    glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(250.0, 0.0, 0.0); 
        glColor3f(0.3f, 0.0f, 0.0f);
        glVertex3f(-250.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);


        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0, 250.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glColor3f(0.0f, 0.3f, 0.0f);
        glVertex3f(0.0, -250.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);


        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0, 0.0, 250.0);
        glVertex3f(0.0, 0.0, 0.0);
        glColor3f(0.0f, 0.0f, 0.3f);
        glVertex3f(0.0, 0.0, -250.0);
        glVertex3f(0.0, 0.0, 0.0);
    glEnd();
}

void tabla(int lado){
    GLfloat Increment = 2*lado;      // translation unit in x directions
    GLfloat positionX = -windowWidth;
    GLfloat positionZ = -windowHeight;

    int numPiezasAncho = 2*windowWidth/(lado*2);
    int numPiezasAlto = 2*windowHeight/(lado*2);

    for(int i = 0;i<numPiezasAlto;i++){
        for(int j=0;j<numPiezasAncho;j++){
            glPushMatrix();                               // TODO: Save State Matrix

            glTranslatef(positionX,0.0f,positionZ);
            if( (i+j)%2==0){
                glColor3f(0.65f,0.65f,0.65f);
            }else{
                glColor3f(0.09f,0.89f,0.86f);
            }
            cuadrado(lado);
            positionZ +=Increment;
            glPopMatrix();
        }
        positionX +=Increment;
        positionZ = -windowHeight;
    }


    
}
/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0, 0.0, 0.0, 1.0); //   Set background (clear) color to black
   glNewList(objReina, GL_COMPILE);	
         reina();                       //    TODO: Draw object,  
   glEndList();

   glNewList(objCaballo, GL_COMPILE);	
         caballo();                       //    TODO: Draw object,  
   glEndList();

   glNewList(objTorre, GL_COMPILE);
        DrawTorre();
    glEndList();
         //efecto de iluminacion
    //glEnable(GL_LIGHTING); //habilita luz natural
    //glEnable(GL_LIGHT0); //habilita luz blanca
}

/* Callback handler for window re-paint event */
void display() {
   
   glClear (GL_COLOR_BUFFER_BIT); /*   clear screen */
   glMatrixMode(GL_MODELVIEW);    //   To operate on the model-view matrix
   glLoadIdentity();              //   Reset model-view matrix
   
   
   gluLookAt(0.0,75.0,zValue,  0.0,0.0,0.0,   0.0,1.0,0.0);      //  Define camera settings
   
    //Dibujo los ejes
   //DrawAxis();
   //Dibujo un tablero
   //tabla(25);
    glPushMatrix();                               // TODO: Save State Matrix
   glRotatef(angleTheta[0], 1.0, 0.0, 0.0);
   glRotatef(angleTheta[1], 0.0, 1.0, 0.0);
    
    //Dibujo un tablero
    tabla(50);
   
   /* Draw object */
   glPolygonMode(GL_FRONT, GL_LINE);
   glPolygonMode(GL_BACK,GL_LINE);

    //Dibujo los ejes
    DrawAxis();


    //CABALLO
    glColor3f(1.0,1.0,1.0);
    rotation(180,0.0,1.0,0.0);
    glCallList(objCaballo);

    //REINA    
    glColor3f(1.0,1.0,1.0);
    traslation(100.0,0.0,0.0);
    glCallList(objReina);  

    //TORRE
    glColor3f(1.0,1.0,1.0);
    glCallList(objTorre);


	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
    glPopMatrix();                              // TODO: Recover previous state matrix
    

   glFlush ();                   //  Render Object
}
 
/* Call back when the windows is re-sized */
void reshape(GLsizei width, GLsizei height) {
   // Compute aspectRatio ratio of the new window
   GLfloat aspectRatio = (GLfloat)width / (GLfloat)height; //Compute aspect ratio
 
   
   glViewport(0, 0, width, height);  // Set the viewport to cover the new screen size
 
   // Set the aspectRatio ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  //   To operate on the Projection matrix
   glLoadIdentity();             //   Reset the projection matrix
   if (width >= height) {
      windowAreaXLeft   = -windowWidth * aspectRatio;
      windowAreaXRight  = windowWidth * aspectRatio;
      windowAreaYBottom = -windowHeight;
      windowAreaYTop    = windowHeight;
   } else {
      windowAreaXLeft   = -windowWidth;
      windowAreaXRight  = windowWidth;
      windowAreaYBottom = -windowHeight / aspectRatio;
      windowAreaYTop    = windowHeight / aspectRatio;
   }
   
   //Adjust vision cone
    
   
   gluPerspective(60.0, GLfloat(width) / GLfloat(height), 0.5, 2000.0); //   Define the shape of your viewing volume using glFrustum function
 
  
   //Save new windowXMin, windowXMax, windowYMin, windowYMax (or called left, right, bottom, top respectively)
   windowXMin = windowAreaXLeft;
   windowXMax = windowAreaXRight;
   windowYMin = windowAreaYBottom;
   windowYMax = windowAreaYTop;


}

 void mouse(int btn, int state, int x, int y){
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
        if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 1;
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 2;	
	angleTheta[axis] += 2.0;
	if( angleTheta[axis] > 360.0 ) angleTheta[axis] -= 360.0;
	display();
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitWindowSize(windowWidth, windowHeight);  // Initial window width and height
   glutCreateWindow("Prac 5A");      // Create window with given title
   glutDisplayFunc(display);     // Register callback handler for window re-paint
   glutReshapeFunc(reshape); 
   glutMouseFunc(mouse);
   initGL();                     // Our own OpenGL initialization
   glutMainLoop();               // Enter event-processing loop
   return 1;
}
