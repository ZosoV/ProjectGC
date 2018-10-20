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
#define PI 3.14159265f

#define ObjElipsoide 1
#define ObjMediaEsfera 2
#define ObjToro 3
#define ObjKlein 4
#define ObjMobius 5
// Global variables
int windowWidth  = 500;     // Initial Screen and viewport width 
int windowHeight = 500;     // Initil Screen and viewport height

GLfloat zValue=400;
 GLfloat xRotated, yRotated, zRotated;
  GLfloat angleTheta[] = {0.0,0.0,0.0};
 GLint axis = 2;
int slices = 10;
GLfloat windowXMax, windowXMin, windowYMax, windowYMin; // window bounds

// Projection window/clipping/work area
GLdouble windowAreaXLeft, windowAreaXRight, windowAreaYBottom, windowAreaYTop;

//sqrt(X² + Y²) = r
#define X 50 //TODO: Set the value of X
#define Z 80 //TODO: Set the value of Z
#define radio sqrt(pow(X,2)+pow(Z,2))

const GLfloat vVertex[12][3] =
    {
    {-X,0.0,Z}, {X,0.0,Z}, {-X,0.0,-Z}, {X,0.0,-Z},
    {0.0,Z,X}, {0.0,Z,-X}, {0.0,-Z,X}, {0.0,-Z,-X},
    {Z,X,0.0}, {-Z,X,0.0}, {Z,-X,0.0}, {-Z,-X,0.0},
    };

const GLuint tindices[20][3] =
    {
    {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},
    {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},
    {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
    {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11}
    };

 


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
 
/*normalize a vector*/
void normalize(float v[3]) {    
   GLfloat d = sqrt(v[0]*v[0] + v[1]*v[1]+v[2]*v[2]);            //TODO: compute the magnitude of the vector
   if (d == 0.0) {
      printf("\nErrot: zero length vector");    
      return;
   }
   //GLfloat factor = radio/d;
   v[0] =  v[0]/d ; v[1] = v[1]/d ; v[2]= v[2]/d ;    //TODO: normalize the vector
}

//v1[], v2[] are two vectors
//out[] holds the crossproduct v1 x v2 
void normcrossprod(float v1[3], float v2[3], float out[3]) 
{ 
   GLint i, j; 
   GLfloat length;

    out[0] =  v1[1]*v2[2] - v1[2]*v2[1];                                    //TODO: Compute the crossproduct between V1 and V2
    out[1] =  v1[2]*v2[0] - v1[0]*v2[2];   
    out[2] =  v1[0]*v2[1] - v1[1]*v2[0];   	
    
   normalize(out); 
}

void DrawTriangle(GLfloat v0[3], GLfloat v1[3], GLfloat v2[3]){
    glBegin(GL_TRIANGLES);
        glColor3ub( (char) rand()%256, (char) rand()%256, (char) rand()%256);
        //glColor3f(1.0f,1.0f,1.0f);
        GLfloat vecA[3], vecB[3], norm[3];    
        for (int j = 0; j < 3; j++) 
        {    
            vecA[j] =  v0[j] - v1[j];                                                         //TODO: Compute vecA[j]   
            vecB[j] =  v2[j] - v1[j];                                                       //TODO: Compute vecB[j]   
        }
        normcrossprod(vecA, vecB, norm); 
            

        //vertex information
        glNormal3fv(norm);                     
        glVertex3f(v0[0],v0[1],v0[2]);
        glNormal3fv(norm); 
        glVertex3f(v1[0],v1[1],v1[2]);
        glNormal3fv(norm);
        glVertex3f(v2[0],v2[1],v2[2]);
    glEnd();

}

void recursiveTriangles(int numDiv, GLfloat v0[3], GLfloat v1[3], GLfloat v2[3]){
    if(numDiv!=0){
        GLfloat v01[3],v12[3],v02[3];
        for(int i=0;i<3;i++){
            v01[i] = (v0[i]+v1[i])/2;
            v12[i] = (v1[i]+v2[i])/2;
            v02[i] = (v0[i]+v2[i])/2;
        }
        normalize(v01);
        normalize(v12);
        normalize(v02);

        for(int i=0;i<3;i++){
            v01[i] = radio*v01[i];
            v12[i] = radio*v12[i];
            v02[i] = radio*v02[i];
        }

        //DrawTriangle(v0,v1,v2);
        //DrawTriangle(v01,v12,v02);
        DrawTriangle(v0,v01,v02);
        DrawTriangle(v01,v12,v02);
        DrawTriangle(v02,v12,v02);
        DrawTriangle(v01,v1,v12);


        recursiveTriangles(numDiv-1,v0,v01,v02);
        recursiveTriangles(numDiv-1,v01,v12,v02);
        recursiveTriangles(numDiv-1,v02,v12,v2);
        recursiveTriangles(numDiv-1,v01,v1,v12);
    }
}

void elipsoide(void)
{   
    GLfloat rx=100,ry=50,rz=200;
    int nlatitude = 10, nlongitude = 10;
    GLfloat varSlicesLat = PI /nlatitude; //Respecto a Z
    GLfloat varSlicesLon = 2*PI/nlongitude; //Respecto a X

    GLfloat vertex[3];

    glColor3f(1.0f,1.0f,1.0f);
    for(int i = 0;i<=nlatitude;i++){  //Respecto a Z
        glBegin(GL_TRIANGLE_STRIP);
        for(int j=0;j<=nlongitude;j++){ //Respecto a X
            vertex[0] = rx*cos((i+1)*varSlicesLat)*cos(j*varSlicesLon-0.5*PI);
            vertex[1] = ry*sin((i+1)*varSlicesLat)*cos(j*varSlicesLon-0.5*PI);
            vertex[2] = rz*sin(j*varSlicesLon-0.5*PI);
            glVertex3fv(vertex);
            vertex[0] = rx*cos(i*varSlicesLat)*cos(j*varSlicesLon-0.5*PI);
            vertex[1] = ry*sin(i*varSlicesLat)*cos(j*varSlicesLon-0.5*PI);
            vertex[2] = rz*sin(j*varSlicesLon-0.5*PI);
            glVertex3fv(vertex);
        }
        glEnd();
        
    }
              
}
/* Initialize OpenGL Graphics */
void initGL() 
{
   glClearColor(0.0, 0.0, 0.0, 1.0); //   Set background (clear) color to black
   glNewList(ObjElipsoide, GL_COMPILE);	
         elipsoide();                       //    TODO: Draw object,  
   glEndList();
         //efecto de iluminacion
    //glEnable(GL_LIGHTING); //habilita luz natural
    //glEnable(GL_LIGHT0); //habilita luz blanca
}

/* Callback handler for window re-paint event */
void display() 
{
   
   glClear (GL_COLOR_BUFFER_BIT); /*   clear screen */
   glMatrixMode(GL_MODELVIEW);    //   To operate on the model-view matrix
   glLoadIdentity();              //   Reset model-view matrix
   
   
   gluLookAt(.0,0.0,zValue,  0.0,0.0,0.0,   0.0,1.0,0.0);      //  Define camera settings
    glPushMatrix();                               // TODO: Save State Matrix
   glRotatef(angleTheta[0], 1.0, 0.0, 0.0);
   glRotatef(angleTheta[1], 0.0, 1.0, 0.0);
   
   
   /* Draw object */
      glPolygonMode(GL_FRONT, GL_LINE);
   glPolygonMode(GL_BACK,GL_LINE);

    //Banda de Mobius usar este escalamiento para apreciar el objeto mejor
    //glScaled(100.0f,100.0f,100.0f);
    //glCallList(ObjMobius);

    //Botella de Klein usar este escalamiento para apreciar el objeto mejor
    //glScaled(10.0f,10.0f,10.0f);
    //glCallList(ObjKlein);
    
    
    
    glCallList(ObjElipsoide);                              // TODO: Call Instance  ObjIcosahedron  
    //glCallList(ObjMediaEsfera);                              // TODO: Call Instance  ObjIcosahedron  
    //glCallList(ObjToro);                              // TODO: Call Instance  ObjIcosahedron  

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
    glPopMatrix();                              // TODO: Recover previous state matrix

   DrawAxis();
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
    
   
   gluPerspective(60.0, GLfloat(width) / GLfloat(height), 0.5, 500.0); //   Define the shape of your viewing volume using glFrustum function
 
   
  
   //Save new windowXMin, windowXMax, windowYMin, windowYMax (or called left, right, bottom, top respectively)
   windowXMin = windowAreaXLeft;
   windowXMax = windowAreaXRight;
   windowYMin = windowAreaYBottom;
   windowYMax = windowAreaYTop;


}

 void mouse(int btn, int state, int x, int y)
{
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
