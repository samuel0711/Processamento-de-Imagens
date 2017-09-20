#include "pixelLab.h"
#ifdef WIN32
#include <windows.h>
#endif
#include "GL/glut.h"
#include <stdio.h>
#include <stdlib.h>

PixelLab *img1 = NULL, *img2 = NULL, *copia = NULL;

int wimg1 = 0, wimg2 = 0, resultado = 0;

void display1()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    img1->ViewImage();
    glutSwapBuffers();
}

void display2()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    img2->ViewImage();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
//            translacao(x,y);
        }
    }
    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
  //          escala(x,y);
        }
    }
    else if(button == 3)
    {
        if(state == GLUT_UP)
        {
    //        rotacao();
        }
    }
    else if(button == 4)
    {
        if(state == GLUT_DOWN)
        {
      //      rotacao();
        }
    }
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB| GLUT_DOUBLE| GLUT_DEPTH);

    img1 = new PixelLab();
    img2 = new PixelLab();

    img1->Read("../figs/lenaGray.png");
    img2->Read("../figs/gearsGray.png");

    wimg1 = glutCreateWindow("Lena Gray Window");
    wimg2 = glutCreateWindow("Gears Gray Window");
    resultado = glutCreateWindow("Result Window");

    glutSetWindow(wimg1);
    glutDisplayFunc(display1);
    glutReshapeWindow(img1->GetWidth(),img1->GetHeight());
    glutMouseFunc(mouse);

    glutSetWindow(wimg2);
    glutDisplayFunc(display2);
    glutReshapeWindow(img2->GetWidth(),img2->GetHeight());
    glutMouseFunc(mouse);

    glutSetWindow(resultado);
    glutReshapeWindow(600,600);

    glutMainLoop();
}
