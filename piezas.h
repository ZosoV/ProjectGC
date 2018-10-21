

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
    glTranslatef(-15.0,0.0,0.0);
    oreja(6.0,8.0);
    glPopMatrix();
}
void reina(void){
    base(50,40,20); //25 de altura siempre empieza la base
    glPushMatrix();
    glTranslatef(0.0,25.0,0.0);
    cilindroHueco(25,20,5);
    glTranslatef(0.0,5.0,0.0);
    casiCono(20,10,45);
    glTranslatef(0.0,45.0,0.0);
    cilindroHueco(20,10,5);
    glTranslatef(0.0,5.0,0.0);
    cilindroHueco(17.5,10,3);
    glTranslatef(0.0,3.0,0.0);
    casiCono(10,17,15);
    glTranslatef(0.0,15.0,0.0);
    corona(20.0,17.0);
    glTranslatef(0.0,4.0,0.0);
    mediaEsfera(17);
    esfera(5,0.0,17.0,0.0);
    glPopMatrix();
}