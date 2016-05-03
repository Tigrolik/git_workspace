//#include <GL/freeglut.h>
#include <iostream>
#include <GL/glut.h>

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(void)
{
    /* clear screen */
    glClear(GL_COLOR_BUFFER_BIT);

    /* set the pixel size */
    glPointSize(1.0f);

    // get window center coordinates
    int w = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int h = glutGet(GLUT_WINDOW_HEIGHT) / 2;

    /* draw two dots next to each other */
    glBegin(GL_POINTS);
    // green dot in the center
    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(w, h);
    // red dot next to the green dot
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(w + 1, h);
    glEnd();

    /* draw interval */
    glBegin(GL_LINES);
    glColor3d(0.75, 0.75, 1);
    glVertex2d(200, 100);
    glVertex2d(100, 200);
    glEnd();

    /* end */
    glutSwapBuffers();
    // glFinish();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Example");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    std::cout << glutGet(GLUT_WINDOW_WIDTH) << std::endl;
    glutMainLoop();

    return 0;
}
