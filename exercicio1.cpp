#include "pixelLab.h"
#ifdef WIN32
#include <windows.h>
#endif
#include "GL/glut.h"
#include <stdio.h>
#include <stdlib.h>

PixelLab *img = NULL, *curva = NULL;

int wimg = 0, wcurva = 0, tom = 128;

static void display1(void)
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
/*
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0,100,0,100);

    glBegin(GL_QUADS);
        glColor3f(1.0,0.0,0.0);
        glVertex2i(0, 0);
        glVertex2i(0,100);
        glColor3f(0.0,0.0,1.0);
        glVertex2i(100, 0);
        glVertex2i(100,100);
    glEnd();


*/
    img->ViewImage();
    glutSwapBuffers();
}

static void display2(void)
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0,100,0,100);

    glBegin(GL_LINE_STRIP);
        glColor3f(0.0,0.0,0.0);
        glVertex2i(0, 0);
        glVertex2i(20,40);
        glVertex2i(60, 30);
        glVertex2i(100,100);
    glEnd();
    glutSwapBuffers();

}

void modificarImg()
{
    int valor = tom-128, valorPixel;

    for(int i = 0; i < img->GetWidth(); i++)
    {
        for(int j = 0; j < img->GetHeight(); j++)
        {
            valorPixel = img->GetGrayValue(i,j);
            valorPixel += valor;
            if(valorPixel >= 255)
            {
                valorPixel = 255;
            }
            else if(valorPixel <= 0)        //PLEONASMO COM uBYTE??
            {
                valorPixel = 0;
            }
            img->SetGrayValue(i,j, (uByte)valorPixel);
        }
    }
    glutPostWindowRedisplay(wimg);
    glutPostWindowRedisplay(wcurva);
}

void mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            tom = y;
            modificarImg();
        }
    }
}

void motion(int x, int y)
{
    tom = y;
    modificarImg();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);

    img = new PixelLab();
    curva = new PixelLab();
    img->Read("../figs/woman.png");

    wimg = glutCreateWindow("Image Window");
    wcurva = glutCreateWindow("Curve Window");

    glutSetWindow(wimg);        // Muda a janela atual para "wimg" (todas as callbacks serão utilizadas nessa janela)
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutDisplayFunc(display1);

    glutSetWindow(wcurva);      // Muda a janela atual para "wcurva" (todas as callbacks serão utilizadas nessa janela)
    glutInitWindowSize(600,600);
    glutInitWindowPosition(650,0);
    glutReshapeWindow(256,256);
    //glutSolidCube(1.0);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutDisplayFunc(display2);

    glutMainLoop();

    return 1;
}
