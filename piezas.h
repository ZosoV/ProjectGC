

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
void caballo(void){
    base(50,20,10);
    cuerpo();
    esfera(15.0,0.0,80.0,-2.0);
    cubo(25,10,30);
    oreja(6.0,8.0);
    glPushMatrix();
    traslation(-15.0,0.0,0.0);
    oreja(6.0,8.0);
    glPopMatrix();
}
void reina(void){
    base(50,40,20); //25 de altura siempre empieza la base
    glPushMatrix();
    traslation(0.0,25.0,0.0);
    cilindroHueco(25,20,5);
    traslation(0.0,5.0,0.0);
    casiCono(20,10,45);
    traslation(0.0,45.0,0.0);
    cilindroHueco(20,10,5);
    traslation(0.0,5.0,0.0);
    cilindroHueco(17.5,10,3);
    traslation(0.0,3.0,0.0);
    casiCono(10,17,15);
    traslation(0.0,15.0,0.0);
    corona(20.0,17.0);
    traslation(0.0,4.0,0.0);
    mediaEsfera(17);
    esfera(5,0.0,17.0,0.0);
    glPopMatrix();
}

float peon[12][3]={
    {0.0, 0.0, 0.0},
    {0.0, 50.0, 0.0},
    {10.0, 50.0, 0.0},
    {15.0, 20.0, 0.0},
    {25.0, 10.0, 0.0},
    {50.0, 10.0, 0.0},
    {60.0, 20.0, 0.0},
    {70.0, 10.0, 0.0},
    {80.0, 20.0, 0.0},
    {90.0, 20.0, 0.0},
    {100.0, 10.0, 0.0},
    {100.0, 0.0, 0.0},
};

float newpeon[12][3]={
    {0.0, 0.0, 0.0},
    {0.0, 50.0, 0.0},
    {10.0, 50.0, 0.0},
    {15.0, 20.0, 0.0},
    {25.0, 10.0, 0.0},
    {50.0, 10.0, 0.0},
    {60.0, 20.0, 0.0},
    {70.0, 10.0, 0.0},
    {80.0, 20.0, 0.0},
    {90.0, 20.0, 0.0},
    {100.0, 10.0, 0.0},
    {100.0, 0.0, 0.0},
};

float alfil[15][3]={
    {0.0, 0.0, 0.0},
    {0.0, 50.0, 0.0},
    {10.0, 50.0, 0.0},
    {15.0, 20.0, 0.0},
    {25.0, 10.0, 0.0},
    {50.0, 10.0, 0.0},
    {60.0, 20.0, 0.0},
    {70.0, 10.0, 0.0},
    {80.0, 20.0, 0.0},
    {90.0, 20.0, 0.0},
    {100.0, 13.0, 0.0},
    {110.0, 6.0, 0.0},
    {120.0, 4.0, 0.0},
    {130.0, 2.0, 0.0},
    {140.0, 0.0, 0.0},
};

float newalfil[15][3]={
    {0.0, 0.0, 0.0},
    {0.0, 50.0, 0.0},
    {10.0, 50.0, 0.0},
    {15.0, 20.0, 0.0},
    {25.0, 10.0, 0.0},
    {50.0, 10.0, 0.0},
    {60.0, 20.0, 0.0},
    {70.0, 10.0, 0.0},
    {80.0, 20.0, 0.0},
    {90.0, 20.0, 0.0},
    {100.0, 13.0, 0.0},
    {110.0, 6.0, 0.0},
    {120.0, 4.0, 0.0},
    {130.0, 2.0, 0.0},
    {140.0, 0.0, 0.0},
};

float rey[8][3]{
    {0.0, 0.0, 0.0},
    {0.0, 50.0, 0.0},
    {10.0, 50.0, 0.0},
    {15.0, 20.0, 0.0},
    {25.0, 10.0, 0.0},
    {70.0, 10.0, 0.0},
    {80.0, 20.0, 0.0},
    {90.0, 10.0, 0.0},
};

float newrey[8][3]{
    {0.0, 0.0, 0.0},
    {0.0, 50.0, 0.0},
    {10.0, 50.0, 0.0},
    {15.0, 20.0, 0.0},
    {25.0, 10.0, 0.0},
    {70.0, 10.0, 0.0},
    {80.0, 20.0, 0.0},
    {90.0, 10.0, 0.0},
};

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



void DrawAlfil()
{ 
    int slices = 10;
    GLfloat theta = (2*PI) /slices;
    glColor3f(0.38f, 0.0f, 0.64f);
    for (int r=0; r<slices; r++){
        glBegin(GL_LINE_STRIP); 
        for (int i=0; i<sizeof(alfil)/sizeof(alfil[0]); i++){
            glVertex3f(alfil[i][0], alfil[i][1], alfil[i][2]);
            newalfil[i][0]= alfil[i][0];
            newalfil[i][1]= (cos(theta)*alfil[i][1])-(sin(theta)*alfil[i][2]);
            newalfil[i][2]= (sin(theta)*alfil[i][1])+(cos(theta)*alfil[i][2]);
        }glEnd();
        for (int i=0; i<sizeof(alfil)/sizeof(alfil[0]); i++){
            glBegin(GL_LINE_STRIP); 
                glVertex3f(alfil[i][0], alfil[i][1], alfil[i][2]);
                glVertex3f(newalfil[i][0], newalfil[i][1], newalfil[i][2]);
            glEnd();
            alfil[i][0]= newalfil[i][0];
            alfil[i][1]= newalfil[i][1];
            alfil[i][2]= newalfil[i][2];
        }      
    }    
              // End Drawing The Cube
glFlush();
}

void DrawPeon()
{ 
    int slices = 10;
    GLfloat theta = (2*PI) /slices;
    glColor3f(0.38f, 0.0f, 0.64f);
    for (int r=0; r<slices; r++){
        glBegin(GL_LINE_STRIP); 
        for (int i=0; i<sizeof(peon)/sizeof(peon[0]); i++){
            glVertex3f(peon[i][0], peon[i][1], peon[i][2]);
            newpeon[i][0]= peon[i][0];
            newpeon[i][1]= (cos(theta)*peon[i][1])-(sin(theta)*peon[i][2]);
            newpeon[i][2]= (sin(theta)*peon[i][1])+(cos(theta)*peon[i][2]);
        }glEnd();
        for (int i=0; i<sizeof(peon)/sizeof(peon[0]); i++){
            glBegin(GL_LINE_STRIP); 
                glVertex3f(peon[i][0], peon[i][1], peon[i][2]);
                glVertex3f(newpeon[i][0], newpeon[i][1], newpeon[i][2]);
            glEnd();
            peon[i][0]= newpeon[i][0];
            peon[i][1]= newpeon[i][1];
            peon[i][2]= newpeon[i][2];
        }      
    }    
              // End Drawing The Cube
glFlush();
}

void DrawTubo(){
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
        for (int i=0; i<sizeof(rey)/sizeof(rey[0]); i++){
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

void DrawRey(){
    int slices = 10;

    GLfloat theta = (2*PI) /slices;
    glColor3f(0.38f, 0.0f, 0.64f);
    for (int r=0; r<slices; r++){
        glBegin(GL_LINE_STRIP); 
        for (int i=0; i<sizeof(rey)/sizeof(rey[0]); i++){
            glVertex3f(rey[i][0], rey[i][1], rey[i][2]);
            newrey[i][0]= rey[i][0];
            newrey[i][1]= (cos(theta)*rey[i][1])-(sin(theta)*rey[i][2]);
            newrey[i][2]= (sin(theta)*rey[i][1])+(cos(theta)*rey[i][2]);
        }glEnd();
        for (int i=0; i<sizeof(rey)/sizeof(rey[0]); i++){
            glBegin(GL_LINE_STRIP); 
                glVertex3f(rey[i][0], rey[i][1], rey[i][2]);
                glVertex3f(newrey[i][0], newrey[i][1], newrey[i][2]);
            glEnd();
            rey[i][0]= newrey[i][0];
            rey[i][1]= newrey[i][1];
            rey[i][2]= newrey[i][2];
        }      
    }    // End Drawing The Cube
    glPushMatrix();
     glTranslatef(90.0,0.0,0.0);
     glPushMatrix();
     glTranslatef(30.0,0.0,0.0);
     glRotatef(90.0f,0.0f,1.0f,0.0f);
     glTranslatef(-30.0,0.0,0.0);
     DrawTubo();
     glPopMatrix();
     DrawTubo();
     glPopMatrix();
    glFlush();
}

void DrawTorre1(){
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

void DrawTorre2(){
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

void DrawTorre(){
    glPushMatrix();
    for (int i=1;i<=4;i++){
        DrawTorre1();
        glRotatef(45.0f,1.0f,0.0f,0.0f);
        DrawTorre2();
    }
    glPopMatrix();
}