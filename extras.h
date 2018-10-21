
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

void base(GLfloat rMayor, GLfloat rMedio,GLfloat rMenor){

  int numVertices = 5;
  GLfloat vertices[numVertices][3] = {
  {0.0, 0.0, 0.0},
    {rMayor, 0.0, 0.0},
    {rMayor, 10.0, 0.0},
    {rMedio, 15.0, 0.0},
    {rMenor, 25.0, 0.0}
  };



  GLfloat newVertices[numVertices][3];
  int slices = 40;
  GLfloat angulo = (2*PI)/slices;
  for (int j = 0; j < slices; j++) {
      glBegin(GL_LINE_STRIP);
    // glBegin(GL_TRIANGLE_STRIP);
      for(int i=0;i<numVertices;i++){
        glVertex3f( vertices[i][0],
                    vertices[i][1],
                    vertices[i][2]);
        newVertices[i][0] = (cos(angulo)*vertices[i][0])+(sin(angulo)*vertices[i][2]);
        newVertices[i][1] = vertices[i][1];
        newVertices[i][2] = -(sin(angulo)*vertices[i][0])+(cos(angulo)*vertices[i][2]);
      }
      glEnd();
      for(int i=0;i<numVertices;i++){

        glBegin(GL_LINES);
        //glBegin(GL_TRIANGLE_STRIP);
          glVertex3f(vertices[i][0],vertices[i][1],vertices[i][2]);
          glVertex3f(newVertices[i][0],newVertices[i][1],newVertices[i][2]);
        glEnd();
        vertices[i][0] = newVertices[i][0];
        vertices[i][1] = newVertices[i][1];
        vertices[i][2] = newVertices[i][2];
      }

  }
}
void cuerpo(void){
      int numVertices = 4;
  GLfloat derecho[numVertices][3] = {
    {10.0, 25.0, 0.0},
    {20.0,50.0,0.0},
    {15.0,70.0,0.0},
    {10.0,80.0,0.0},
  };
  
  GLfloat auxiliar[numVertices][3] = {
    {10.0, 25.0, 0.0},
    {20.0,50.0,0.0},
    {15.0,70.0,0.0},
    {10.0,80.0,0.0},
  };
  GLfloat izquierdo[numVertices][3] = {
    {-10.0,25.0,0.0},
    {-14.0,50.0,0.0},
    {-16.5,70.0,0.0},
    {-13.0,80.0,0.0}
  };


  GLfloat newVertices[numVertices][3];
  int slices = 10;
  GLfloat angulo = (PI)/slices;
  for (int j = 0; j < slices; j++) {
      glBegin(GL_LINE_STRIP);
    // glBegin(GL_TRIANGLE_STRIP);
      for(int i=0;i<numVertices;i++){
        glVertex3f( derecho[i][0],
                    derecho[i][1],
                    derecho[i][2]);
        newVertices[i][0] = (cos(angulo)*derecho[i][0])+(sin(angulo)*derecho[i][2]);
        newVertices[i][1] = derecho[i][1];
        newVertices[i][2] = -(sin(angulo)*derecho[i][0])+(cos(angulo)*derecho[i][2]);
      }
      glEnd();
      for(int i=0;i<numVertices;i++){
        glBegin(GL_LINES);
        //glBegin(GL_TRIANGLE_STRIP);
          glVertex3f(derecho[i][0],derecho[i][1],derecho[i][2]);
          glVertex3f(newVertices[i][0],newVertices[i][1],newVertices[i][2]);
        glEnd();
        derecho[i][0] = newVertices[i][0];
        derecho[i][1] = newVertices[i][1];
        derecho[i][2] = newVertices[i][2];
        if(j==slices-1){
          glBegin(GL_LINES);
        //glBegin(GL_TRIANGLE_STRIP);
          glVertex3f(derecho[i][0],derecho[i][1],derecho[i][2]);
          glVertex3f(izquierdo[i][0],izquierdo[i][1],izquierdo[i][2]);
        glEnd();
        }
      }

  }

  for (int j = 0; j < slices; j++) {
      glBegin(GL_LINE_STRIP);
    // glBegin(GL_TRIANGLE_STRIP);
      for(int i=0;i<numVertices;i++){
        glVertex3f( izquierdo[i][0],
                    izquierdo[i][1],
                    izquierdo[i][2]);
        newVertices[i][0] = (cos(angulo)*izquierdo[i][0])+(sin(angulo)*izquierdo[i][2]);
        newVertices[i][1] = izquierdo[i][1];
        newVertices[i][2] = -(sin(angulo)*izquierdo[i][0])+(cos(angulo)*izquierdo[i][2]);
      }
      glEnd();
      for(int i=0;i<numVertices;i++){

        glBegin(GL_LINES);
        //glBegin(GL_TRIANGLE_STRIP);
          glVertex3f(izquierdo[i][0],izquierdo[i][1],izquierdo[i][2]);
          glVertex3f(newVertices[i][0],newVertices[i][1],newVertices[i][2]);
        glEnd();
        izquierdo[i][0] = newVertices[i][0];
        izquierdo[i][1] = newVertices[i][1];
        izquierdo[i][2] = newVertices[i][2];
        if(j==slices-1){
          glBegin(GL_LINES);
        //glBegin(GL_TRIANGLE_STRIP);
          glVertex3f(izquierdo[i][0],izquierdo[i][1],izquierdo[i][2]);
          glVertex3f(auxiliar[i][0],auxiliar[i][1],auxiliar[i][2]);
        glEnd();
        }
      }

  }
}

void esfera(GLfloat r, GLfloat posx, GLfloat posy, GLfloat posz){
    int nlatitude = 10, nlongitude = 10;
    GLfloat varSlicesLat = 2*PI /nlatitude; //Respecto a Z
    GLfloat varSlicesLon = PI/nlongitude; //Respecto a X

    GLfloat vertex[3];

    glColor3f(1.0f,1.0f,1.0f);
    for(int i = 0;i<=nlatitude;i++){  //Respecto a Z
        glBegin(GL_TRIANGLE_STRIP);
        for(int j=0;j<=nlongitude;j++){ //Respecto a X
            vertex[0] = posx + r*cos((i+1)*varSlicesLat)*sin(j*varSlicesLon);
            vertex[1] = posy + r*sin((i+1)*varSlicesLat)*sin(j*varSlicesLon);
            vertex[2] = posz + r*cos(j*varSlicesLon);
            glVertex3fv(vertex);
            vertex[0] = posx + r*cos(i*varSlicesLat)*sin(j*varSlicesLon);
            vertex[1] = posy + r*sin(i*varSlicesLat)*sin(j*varSlicesLon);
            vertex[2] = posz + r*cos(j*varSlicesLon);
            glVertex3fv(vertex);
        }
        glEnd();
        
    }
}
void cubo(GLfloat lMayor, GLfloat lmenor,GLfloat profundidad){
    
    glPushMatrix();
    glTranslatef(0.0,75,-5.0);
    int numVertices = 10;
    GLfloat vertexs[numVertices][3] = {
        {lMayor/2,0.0,0.0},{-lMayor/2,0.0,0.0},
        {-lMayor/2,lMayor/2,0.0},{lMayor/2,lMayor/2,0.0},
        {lMayor/2,0.0,0.0},{lmenor/2,0.0,-profundidad},
        {-lmenor/2,0.0,-profundidad},{-lmenor/2,lmenor/2,-profundidad},
        {lmenor/2,lmenor/2,-profundidad},{lmenor/2,0.0,-profundidad}
   };
   glBegin(GL_LINE_STRIP);
    for(int i=0;i<numVertices;i++){
        glVertex3f(
            vertexs[i][0],
            vertexs[i][1],
            vertexs[i][2]
        );
    }
   glEnd();

    int numV = 6;
   GLfloat vertexsExtra[numV][3]={
       {lMayor/2,lMayor/2,0.0},{lmenor/2,lmenor/2,-profundidad},
       {-lMayor/2,lMayor/2,0.0},{-lmenor/2,lmenor/2,-profundidad},
        {-lMayor/2,0.0,0.0},{-lmenor/2,0.0,-profundidad}
   };
      glBegin(GL_LINES);
    for(int i=0;i<numV;i++){
        glVertex3f(
            vertexsExtra[i][0],
            vertexsExtra[i][1],
            vertexsExtra[i][2]
        );
    }
   glEnd();
   glPopMatrix();
}

void oreja(GLfloat lado, GLfloat altura){
    glPushMatrix();
    glTranslatef(5.0,90.0,-1.0);
    int numVertices = 7;
    GLfloat vertexs[numVertices][3] ={
        {lado/2,altura,0.0},{0.0,0.0,0.0},
        {lado,0.0,0.0},{lado/2,altura,0.0},
        {0.0,0.0,-lado},{lado,0.0,-lado},
        {lado/2,altura,0.0}
    };
    glBegin(GL_LINE_STRIP);
    for(int i=0;i<numVertices;i++){
        glVertex3f(
            vertexs[i][0],
            vertexs[i][1],
            vertexs[i][2]
        );
    }
   glEnd();

   int numV = 4;
   GLfloat vertexExtra[numV][3]={
       {0.0,0.0,0.0},{0.0,0.0,-lado},
       {lado,0.0,0.0},{lado,0.0,-lado}
   };
    glBegin(GL_LINES);
    for(int i=0;i<numV;i++){
        glVertex3f(
            vertexExtra[i][0],
            vertexExtra[i][1],
            vertexExtra[i][2]
        );
    }
   glEnd();
   glPopMatrix();
}
void cuadrado(GLfloat lado){
    GLfloat vertex[4][3] = {
        {-lado/2,0.0f,-lado/2},{lado/2,0.0f,-lado/2},
        {lado/2,0.0f,lado/2},{-lado/2,0.0f,lado/2}
                            };
    glBegin(GL_POLYGON);
        for(int i = 0;i<4;i++){
            glVertex3f(
                vertex[i][0],
                vertex[i][1],
                vertex[i][2]
            );
        }

    glEnd();
}

void cilindroHueco(GLfloat rExterno, GLfloat rInterno,GLfloat altura){
    int numVertices = 4 ;
    GLfloat vertices[numVertices][3] = {
        {rInterno,0.0,0.0},{rExterno,0.0,0.0},
        {rExterno,altura,0.0},{rInterno,altura,0.0}       
    };
    GLfloat newVertices[numVertices][3];
  int slices = 40;
  GLfloat angulo = (2*PI)/slices;
  for (int j = 0; j < slices; j++) {
      glBegin(GL_LINE_STRIP);
    // glBegin(GL_TRIANGLE_STRIP);
      for(int i=0;i<numVertices;i++){
        glVertex3f( vertices[i][0],
                    vertices[i][1],
                    vertices[i][2]);
        newVertices[i][0] = (cos(angulo)*vertices[i][0])+(sin(angulo)*vertices[i][2]);
        newVertices[i][1] = vertices[i][1];
        newVertices[i][2] = -(sin(angulo)*vertices[i][0])+(cos(angulo)*vertices[i][2]);
      }
      glEnd();
      for(int i=0;i<numVertices;i++){

        glBegin(GL_LINES);
        //glBegin(GL_TRIANGLE_STRIP);
          glVertex3f(vertices[i][0],vertices[i][1],vertices[i][2]);
          glVertex3f(newVertices[i][0],newVertices[i][1],newVertices[i][2]);
        glEnd();
        vertices[i][0] = newVertices[i][0];
        vertices[i][1] = newVertices[i][1];
        vertices[i][2] = newVertices[i][2];
      }

  }
}

void casiCono(GLfloat rInferior, GLfloat rSuperior,GLfloat altura){
    int numVertices = 2;
    GLfloat vertices[numVertices][3]={
        {rInferior,0.0,0.0},{rSuperior,altura,0.0}
    };
     GLfloat newVertices[numVertices][3];
  int slices = 40;
  GLfloat angulo = (2*PI)/slices;
  for (int j = 0; j < slices; j++) {
      glBegin(GL_LINE_STRIP);
    // glBegin(GL_TRIANGLE_STRIP);
      for(int i=0;i<numVertices;i++){
        glVertex3f( vertices[i][0],
                    vertices[i][1],
                    vertices[i][2]);
        newVertices[i][0] = (cos(angulo)*vertices[i][0])+(sin(angulo)*vertices[i][2]);
        newVertices[i][1] = vertices[i][1];
        newVertices[i][2] = -(sin(angulo)*vertices[i][0])+(cos(angulo)*vertices[i][2]);
      }
      glEnd();
      for(int i=0;i<numVertices;i++){

        glBegin(GL_LINES);
        //glBegin(GL_TRIANGLE_STRIP);
          glVertex3f(vertices[i][0],vertices[i][1],vertices[i][2]);
          glVertex3f(newVertices[i][0],newVertices[i][1],newVertices[i][2]);
        glEnd();
        vertices[i][0] = newVertices[i][0];
        vertices[i][1] = newVertices[i][1];
        vertices[i][2] = newVertices[i][2];
      }

  }
}

void corona(GLfloat rMayor, GLfloat rMenor){
    int numVertices = 5;
    GLfloat vertices[numVertices][3]={
        {rMenor,0.0,0.0},{rMenor+5,5,0.0},
        {rMenor+8,8,0.0},{rMenor+3,6.5,0.0},
        {rMenor,6.5,0.0}
    };
       GLfloat newVertices[numVertices][3];
  int slices = 40;
  GLfloat angulo = (2*PI)/slices;
  for (int j = 0; j < slices; j++) {
      glBegin(GL_LINE_STRIP);
    // glBegin(GL_TRIANGLE_STRIP);
      for(int i=0;i<numVertices;i++){
        glVertex3f( vertices[i][0],
                    vertices[i][1],
                    vertices[i][2]);
        newVertices[i][0] = (cos(angulo)*vertices[i][0])+(sin(angulo)*vertices[i][2]);
        newVertices[i][1] = vertices[i][1];
        newVertices[i][2] = -(sin(angulo)*vertices[i][0])+(cos(angulo)*vertices[i][2]);
      }
      glEnd();
      for(int i=0;i<numVertices;i++){

        glBegin(GL_LINES);
        //glBegin(GL_TRIANGLE_STRIP);
          glVertex3f(vertices[i][0],vertices[i][1],vertices[i][2]);
          glVertex3f(newVertices[i][0],newVertices[i][1],newVertices[i][2]);
        glEnd();
        vertices[i][0] = newVertices[i][0];
        vertices[i][1] = newVertices[i][1];
        vertices[i][2] = newVertices[i][2];
      }

  }
}
void mediaEsfera(GLfloat r){   
    int nlatitude = 20, nlongitude = 20;
    GLfloat varSlicesLat = (PI/2)/nlatitude; //Respecto a Z fi =>Latitud
    GLfloat varSlicesLon = 2*PI/nlongitude; //Respecto a X thetha =>Longitud

    GLfloat vertex[3];

    glColor3f(1.0f,1.0f,1.0f);
    for(int i = 0;i<=nlatitude;i++){  //Respecto a Z
        glBegin(GL_TRIANGLE_STRIP);
        for(int j=0;j<=nlongitude;j++){ //Respecto a X
            vertex[0] = r*cos((i+1)*varSlicesLat)*cos(j*varSlicesLon);
            vertex[1] = r*sin((i+1)*varSlicesLat);
            vertex[2] = r*cos((i+1)*varSlicesLat)*sin(j*varSlicesLon);;
            glVertex3fv(vertex);
            vertex[0] = r*cos(i*varSlicesLat)*cos(j*varSlicesLon);
            vertex[1] = r*sin(i*varSlicesLat);
            vertex[2] = r*cos(i*varSlicesLat)*sin(j*varSlicesLon);;
            glVertex3fv(vertex);
        }
        glEnd();
        
    }
              
}

void DrawTubo(void){

    float tubo[6][3]{
    {0.0, 0.0, 0.0},
    {0.0, 10.0, 0.0},
    {20.0, 10.0, 0.0},
    {40.0, 10.0, 0.0},
    {60.0, 10.0, 0.0},
    {60.0, 0.0, 0.0},
    };

    float newtubo[6][3]{
    {0.0, 0.0, 0.0},
    {0.0, 10.0, 0.0},
    {20.0, 10.0, 0.0},
    {40.0, 10.0, 0.0},
    {60.0, 10.0, 0.0},
    {60.0, 0.0, 0.0},
    };

    int slices = 10;

    GLfloat theta = (2*PI) /slices;
    glColor3f(0.38f, 0.0f, 0.64f);
    for (int r=0; r<slices; r++){
        glBegin(GL_LINE_STRIP); 
        for (int i=0; i<sizeof(tubo)/sizeof(tubo[0]); i++){
            glVertex3f(tubo[i][0], tubo[i][1], tubo[i][2]);
            newtubo[i][0]= tubo[i][0];
            newtubo[i][1]= (cos(theta)*tubo[i][1])-(sin(theta)*tubo[i][2]);
            newtubo[i][2]= (sin(theta)*tubo[i][1])+(cos(theta)*tubo[i][2]);
        }glEnd();
        for (int i=0; i<sizeof(tubo)/sizeof(tubo[0]); i++){
            glBegin(GL_LINE_STRIP); 
                glVertex3f(tubo[i][0], tubo[i][1], tubo[i][2]);
                glVertex3f(newtubo[i][0], newtubo[i][1], newtubo[i][2]);
            glEnd();
            tubo[i][0]= newtubo[i][0];
            tubo[i][1]= newtubo[i][1];
            tubo[i][2]= newtubo[i][2];
        }      
    }    // End Drawing The Cube
    glFlush();
}

void DrawTorre1(void){

    float torre1[12][3]{
    {20.0, 0.0, 0.0},
    {20.0, 20.0, 0.0},
    {0.0, 20.0, 0.0},
    {0.0, 30.0, 0.0},
    {35.0, 30.0, 0.0},
    {35.0, 15.0, 0.0},
    {65.0, 15.0, 0.0},
    {65.0, 30.0, 0.0},
    {100.0, 30.0, 0.0},
    {100.0, 20.0, 0.0},
    {80.0, 20.0, 0.0},
    {80.0, 0.0, 0.0},
    };

    float newtorre1[12][3]{
    {20.0, 0.0, 0.0},
    {20.0, 20.0, 0.0},
    {0.0, 20.0, 0.0},
    {0.0, 30.0, 0.0},
    {35.0, 30.0, 0.0},
    {35.0, 15.0, 0.0},
    {65.0, 15.0, 0.0},
    {65.0, 30.0, 0.0},
    {100.0, 30.0, 0.0},
    {100.0, 20.0, 0.0},
    {80.0, 20.0, 0.0},
    {80.0, 0.0, 0.0},
    };

    int tslices = 3;
    GLfloat theta = (2*PI) /(8*tslices);
    glColor3f(0.38f, 0.0f, 0.64f);
    for (int r=0; r<tslices; r++){
        glBegin(GL_LINE_STRIP); 
        for (int i=0; i<sizeof(torre1)/sizeof(torre1[0]); i++){
            glVertex3f(torre1[i][0], torre1[i][1], torre1[i][2]);
            newtorre1[i][0]= torre1[i][0];
            newtorre1[i][1]= (cos(theta)*torre1[i][1])-(sin(theta)*torre1[i][2]);
            newtorre1[i][2]= (sin(theta)*torre1[i][1])+(cos(theta)*torre1[i][2]);
        }glEnd();
        for (int i=0; i<sizeof(torre1)/sizeof(newtorre1[0]); i++){
            glBegin(GL_LINE_STRIP); 
                glVertex3f(torre1[i][0], torre1[i][1], torre1[i][2]);
                glVertex3f(newtorre1[i][0], newtorre1[i][1], newtorre1[i][2]);
            glEnd();
            torre1[i][0]= newtorre1[i][0];
            torre1[i][1]= newtorre1[i][1];
            torre1[i][2]= newtorre1[i][2];
        }      
    }    // End Drawing The Cube
    glFlush();
}

void DrawTorre2(void){

    float torre2[12][3]{
    {20.0, 0.0, 0.0},
    {20.0, 20.0, 0.0},
    {10.0, 20.0, 0.0},
    {10.0, 30.0, 0.0},
    {35.0, 30.0, 0.0},
    {35.0, 15.0, 0.0},
    {65.0, 15.0, 0.0},
    {65.0, 30.0, 0.0},
    {90.0, 30.0, 0.0},
    {90.0, 20.0, 0.0},
    {80.0, 20.0, 0.0},
    {80.0, 0.0, 0.0},
    };

    float newtorre2[12][3]{
    {20.0, 0.0, 0.0},
    {20.0, 20.0, 0.0},
    {10.0, 20.0, 0.0},
    {10.0, 30.0, 0.0},
    {35.0, 30.0, 0.0},
    {35.0, 15.0, 0.0},
    {65.0, 15.0, 0.0},
    {65.0, 30.0, 0.0},
    {90.0, 30.0, 0.0},
    {90.0, 20.0, 0.0},
    {80.0, 20.0, 0.0},
    {80.0, 0.0, 0.0},
    };

    int tslices = 3;
    GLfloat theta = (2*PI) /(8*tslices);
    glColor3f(0.38f, 0.0f, 0.64f);
    for (int r=0; r<tslices; r++){
        glBegin(GL_LINE_STRIP); 
        for (int i=0; i<sizeof(torre2)/sizeof(torre2[0]); i++){
            glVertex3f(torre2[i][0], torre2[i][1], torre2[i][2]);
            newtorre2[i][0]= torre2[i][0];
            newtorre2[i][1]= (cos(theta)*torre2[i][1])-(sin(theta)*torre2[i][2]);
            newtorre2[i][2]= (sin(theta)*torre2[i][1])+(cos(theta)*torre2[i][2]);
        }glEnd();
        for (int i=0; i<sizeof(torre2)/sizeof(newtorre2[0]); i++){
            glBegin(GL_LINE_STRIP); 
                glVertex3f(torre2[i][0], torre2[i][1], torre2[i][2]);
                glVertex3f(newtorre2[i][0], newtorre2[i][1], newtorre2[i][2]);
            glEnd();
            torre2[i][0]= newtorre2[i][0];
            torre2[i][1]= newtorre2[i][1];
            torre2[i][2]= newtorre2[i][2];
        }      
    }    // End Drawing The Cube
    glFlush();
}