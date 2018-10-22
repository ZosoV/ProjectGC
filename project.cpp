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
int refreshMillis = 30;
int PosInicialAlfilX = 300, PosActualAlfilX = PosInicialAlfilX, IncrementoAlfilX = -5, LimiteAlfilX = -500;
float TamInicialRey = 1, TamActualRey  = TamInicialRey, TamIncrementoRey = 0.2, TamLimiteRey = 7;
int PosInicialTorreX = 300, PosActualTorreX = PosInicialTorreX, IncrementoTorreX = -5, LimiteTorreX = -300;
    int PosInicialTorreY = 200, PosActualTorreY = PosInicialTorreY, IncrementoTorreY = -5, LimiteTorreY = -200;
int PosInicialReinaX = 300, PosActualReinaX = PosInicialReinaX, IncrementoReinaX = -5, LimiteReinaX = -300;
    int PosInicialReinaY = 400, PosActualReinaY = PosInicialReinaY, IncrementoReinaY = -5, LimiteReinaY = -400;
    float TamInicialReina = 1, TamActualReina  = TamInicialReina, TamIncrementoReina = 0.03, TamLimiteReina = 7;
float TamInicialCaballo = 1, TamActualCaballo  = TamInicialCaballo, TamIncrementoCaballo = 0.03, TamLimiteCaballo = 7;
    int RotInicialCaballo = 0, RotActualCaballo  = TamInicialCaballo, RotIncrementoCaballo = 3;
float SizallaInicialPeon = 0, SizallaActualPeon  = SizallaInicialPeon, SizallaIncrementoPeon = 0.03, SizallaLimitePeon = 5;

GLfloat zValue=1000;
 GLfloat xRotated, yRotated, zRotated;
  GLfloat angleTheta[] = {0.0,0.0,0.0};
 GLint axis = 2;
GLfloat windowXMax, windowXMin, windowYMax, windowYMin; // window bounds
// ]Projection window/clipping/work area
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
    GLfloat Increment = lado;      // Espicficar el tamaño de los cuadrados
    GLfloat positionX = -windowWidth;
    GLfloat positionZ = -windowHeight;

    int numPiezasAncho = 2*windowWidth/lado;
    int numPiezasAlto = 2*windowHeight/lado;

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

   //REINA
   glNewList(objReina, GL_COMPILE);	
         reina();                       //    TODO: Draw object,  
   glEndList();

    //CABALLO
   glNewList(objCaballo, GL_COMPILE);	
         caballo();                       //    TODO: Draw object,  
   glEndList();

    //TORRE
   glNewList(objTorre, GL_COMPILE);
        DrawTorre();
    glEndList();

    //ALFIL
    glNewList(objAlfil, GL_COMPILE);
        DrawAlfil();
    glEndList();

    //REY
    glNewList(objRey, GL_COMPILE);
        DrawRey();
    glEndList();

    //PEON
    glNewList(objPeon, GL_COMPILE);
        DrawPeon();
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
   rotation(angleTheta[0], 1.0, 0.0, 0.0);
   rotation(angleTheta[1], 0.0, 1.0, 0.0);
    
    //Dibujo un tablero
    tabla(100);
   
   /* Draw object */
   glPolygonMode(GL_FRONT, GL_LINE);
   glPolygonMode(GL_BACK,GL_LINE);

    //Dibujo los ejes
    DrawAxis();

    
    //CABALLO
    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    rotation(RotActualCaballo ,0.0 ,1.0 ,0.0);
    scalation(TamActualCaballo, TamActualCaballo, TamActualCaballo);
    glCallList(objCaballo);
    glPopMatrix();
    

    //REINA    
    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    traslation(PosActualReinaX, 0.0f, PosActualReinaY);
    scalation(TamActualReina, TamActualReina, TamActualReina);
    glCallList(objReina);
    glPopMatrix();
    

    //TORRE
    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    traslation(PosActualTorreX,0.0f,PosActualTorreY);
    rotation(-90.0f,0.0f,0.0f,1.0f);
    glCallList(objTorre);
    glPopMatrix();

    //ALFIL
    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    traslation(PosActualAlfilX,0.0f,0.0f);
    rotation(-90.0f,0.0f,0.0f,1.0f);
    glCallList(objAlfil);
    glPopMatrix();

    //REY
    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    traslation(300.0f,0.0f,-200.0f);
    scalation(TamActualRey,TamActualRey,TamActualRey);
    rotation(-90.0f,0.0f,0.0f,1.0f);
    glCallList(objRey);
    glPopMatrix();

    //PEON
    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    traslation(300.0f,0.0f,-400.0f);
    shear(0.0, 0.0, SizallaActualPeon, 0.0, 0.0, 0.0);
    rotation(-90.0f,0.0f,0.0f,1.0f);
    glCallList(objPeon);
    glPopMatrix();


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

void keyboardFunc(unsigned char Key, int x, int y){
	if(Key=='q'){
		PosActualAlfilX = PosActualAlfilX + IncrementoAlfilX;
        if (PosActualAlfilX < LimiteAlfilX){
            PosActualAlfilX = PosInicialAlfilX;
        }
	}
    
	if(Key=='w'){
		TamActualRey = TamActualRey + TamIncrementoRey;
        if (TamActualRey > TamLimiteRey){
            TamActualRey = TamInicialRey;
        }
	}

    if(Key=='e'){
		PosActualTorreX = PosActualTorreX + IncrementoTorreX;
        PosActualTorreY = PosActualTorreY + IncrementoTorreY;
        if (PosActualTorreX < LimiteTorreX && PosActualTorreY < LimiteTorreY){
            PosActualTorreX  = PosInicialTorreX;
            PosActualTorreY  = PosInicialTorreY;
        }
	}

    if(Key=='r'){
		PosActualReinaX = PosActualReinaX + IncrementoReinaX;
        PosActualReinaY = PosActualReinaY + IncrementoReinaY;
        TamActualReina = TamActualReina + TamIncrementoReina;
        if (PosActualReinaX < LimiteReinaX && PosActualReinaY < LimiteReinaY){
            PosActualReinaX  = PosInicialReinaX;
            PosActualReinaY  = PosInicialReinaY;
            TamActualReina = TamInicialReina;
        }
	}
    
    if(Key=='t'){
        TamActualCaballo = TamActualCaballo + TamIncrementoCaballo;
        RotActualCaballo = RotActualCaballo + RotIncrementoCaballo;
        if (RotActualCaballo > 360){
            RotActualCaballo = 0;
        }
        if (TamActualCaballo > TamLimiteCaballo){
            TamActualCaballo = TamInicialCaballo;
        }
	}

    if(Key == 'y'){
        SizallaActualPeon = SizallaActualPeon + SizallaIncrementoPeon;
        if (SizallaActualPeon > SizallaLimitePeon){
            SizallaActualPeon = SizallaInicialPeon;
        }
    }
    
}


void Timer(int value) {
   glutPostRedisplay();    // Post a paint request to activate display()
   glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitWindowSize(windowWidth, windowHeight);  // Initial window width and height
   glutCreateWindow("Prac 5A");      // Create window with given title
   glutDisplayFunc(display);     // Register callback handler for window re-paint
   glutReshapeFunc(reshape); 
   glutMouseFunc(mouse);
   glutKeyboardFunc(keyboardFunc);
   glutTimerFunc(0, Timer, 0); 
   initGL();                     // Our own OpenGL initialization
   glutMainLoop();               // Enter event-processing loop
   return 1;
}
