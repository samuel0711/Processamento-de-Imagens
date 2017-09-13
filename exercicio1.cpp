#include "pixelLab.h"
#ifdef WIN32
#include <windows.h>
#endif
#include "GL/glut.h"
#include <stdio.h>
#include <stdlib.h>

PixelLab *img = NULL, *copia = NULL;

int wimg = 0, wcurva = 0, tom = 128;
//GLfloat pnts[4][3] = {{ -4.0, -4.0, 0.0}, { -2.0, 4.0, 0.0}, {2.0, -4.0, 0.0}, {4.0, 4.0, 0.0}};

static void display1(void)
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    copia->ViewImage();
    glutSwapBuffers();
}

static void display2(void)
{
    int i;
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,256,0,256);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

        glBegin(GL_QUADS);
        glColor3f(0.0,0.0,0.0);
        glVertex2i(256, 256);
        glVertex2i(0,256);
        glColor3f(1.0,1.0,1.0);
        glVertex2i(0, 0);
        glVertex2i(256,0);
    glEnd();
    /*

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
      for (i = 0; i <= 30; i++)
         glEvalCoord1f((GLfloat) i/30.0);
    glEnd();
    glPointSize(5.0);
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
      for (i = 0; i < 4; i++)
         glVertex3fv(&pnts[i][0]);
    glEnd();
    glFlush();
    */
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
            copia->SetGrayValue(i,j, (uByte)valorPixel);
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
        }
    }
    modificarImg();
}

void motion(int x, int y)
{
    tom = y;
    modificarImg();
}

/*void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w,
               5.0*(GLfloat)h/(GLfloat)w, -5.0, 5.0);
   else
      glOrtho(-5.0*(GLfloat)w/(GLfloat)h,
               5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -5.0, 5.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}*/

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);

    img = new PixelLab();
    copia = new PixelLab();
    img->Read("../figs/woman.png");
    copia->Copy(img);

    wimg = glutCreateWindow("Image Window");
    wcurva = glutCreateWindow("Curve Window");

    glutSetWindow(wimg);        // Muda a janela atual para "wimg" (todas as callbacks serão utilizadas nessa janela)
    glutPositionWindow(10,50);
    glutDisplayFunc(display1);
    glutReshapeWindow(img->GetWidth(), img->GetHeight());

    glutSetWindow(wcurva);      // Muda a janela atual para "wcurva" (todas as callbacks serão utilizadas nessa janela)
    glutPositionWindow(600,50);
    glutReshapeWindow(256,256);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutDisplayFunc(display2);
    //glutReshapeFunc(reshape);

    glutMainLoop();

    return 1;
}
