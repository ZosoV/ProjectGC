
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

//Tomar en cuenta que las matrices empleadas aqui deben ser las transpuestas 
//a las que comunmente vemos en clases
void traslation(GLfloat tx, GLfloat ty, GLfloat tz){
    GLfloat m[16] = {
     1.0,   0.0,   0.0, 0.0,
     0.0,   1.0,   0.0, 0.0,
     0.0,   0.0,   1.0, 0.0,
     tx,    ty,    tz,  1.0};
 glMultMatrixf(m);
}

void rotation(GLfloat  angulo, GLfloat x, GLfloat y, GLfloat z){
    angulo = angulo*PI/180;
    if(x == 1){
        GLfloat mx[16] = {
            1.0,   0.0,    0.0,     0.0,
            0.0,   cos(angulo),   -sin(angulo),     0.0,
            0.0,   sin(angulo),    cos(angulo),     0.0,
            0.0,   0.0,    0.0,     1.0};
            glMultMatrixf(mx);
    }
    if(y == 1){
        GLfloat my[16] = {
            cos(angulo),    0.0,    -sin(angulo),       0.0,
            0.0,            1.0 ,   0.0 ,               0.0,
            sin(angulo),    0.0,    cos(angulo),        0.0,
            0.0,            0.0,    0.0,                1.0
            };
            glMultMatrixf(my);
    }

    if(z == 1){
        GLfloat mz[16] = {
            cos(angulo),    -sin(angulo),   0.0,            0.0,
            sin(angulo),    cos(angulo),    0.0,            0.0,
            0.0,            0.0,            1.0,            0.0,
            0.0,            0.0,            0.0,            1.0};
            glMultMatrixf(mz);
    }

}

void scalation(GLfloat sx, GLfloat sy, GLfloat sz){
    GLfloat m[16] = {
     sx,   0.0,   0.0, 0.0,
     0.0,   sy,   0.0, 0.0,
     0.0,   0.0,   sz, 0.0,
     0.0,   0.0,   0.0,  1.0};
 glMultMatrixf(m);
}

void shear(GLfloat  sx_y, GLfloat sx_z, GLfloat sy_x, GLfloat sy_z, GLfloat sz_x, GLfloat sz_y){
    GLfloat m[16] = {
     1.0,   sy_x,   sz_x,  0.0,
     sx_y,   1.0,   sz_y,  0.0,
     sx_z,   sy_z,   1.0,  0.0,
     0.0,   0.0,   0.0,  1.0};
 glMultMatrixf(m);
}