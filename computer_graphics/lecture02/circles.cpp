#include <GL/glut.h>
#include <iostream>

using namespace std;

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

inline int square(int x) { return x * x; }

void draw8points(int x1, int y1, int x, int y)
{
    // draw 8 points to reperesent the entire circle (except the 'corners')
    glVertex2i(x1 + x, y1 + y);
    glVertex2i(x1 - x, y1 + y);
    glVertex2i(x1 + x, y1 - y);
    glVertex2i(x1 - x, y1 - y);
    glVertex2i(x1 + y, y1 + x);
    glVertex2i(x1 - y, y1 + x);
    glVertex2i(x1 + y, y1 - x);
    glVertex2i(x1 - y, y1 - x);
}

void draw4points(int x1, int y1, int r)
{
    // draw 4 'corner' points of a circle
    glVertex2i(x1, y1 + r);
    glVertex2i(x1, y1 - r);
    glVertex2i(x1 + r, y1);
    glVertex2i(x1 - r, y1);
}

void drawcircle_bresenham(int x1, int y1, int r)
{
    int x = 0, y = r, r2 = square(r);
    glBegin(GL_POINTS);
    glColor3f(0.0, 1.0, 0.0);
    draw4points(x1, y1, r);
    while (x <= y) {
        if (square(++x) + square(y - 0.5) - r2 > 0)
            --y;
        draw8points(x1, y1, x, y);
    }
    glEnd();
}

void drawcircle_bresenham_enh(int x1, int y1, int r)
{
    int x = 0, y = r, f = 1 - r, incrE = 3, incrSE = 5 - r - r;

    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 0.0);
    draw4points(x1, y1, r);

    while (x <= y) {
        if (f > 0) {
            --y;
            f += incrSE;
            incrSE += 4;
        } else {
            f += incrE;
            incrSE += 2;
        }
        incrE += 2;
        draw8points(x1, y1, ++x, y);
    }

    glEnd();
}

void display(void)
{
    /* clear screen */
    glClear(GL_COLOR_BUFFER_BIT);

    /* set the pixel size */
    glPointSize(1.0f);

    // get window center coordinates
    int w = glutGet(GLUT_WINDOW_WIDTH), cx = w / 2;
    int h = glutGet(GLUT_WINDOW_HEIGHT), cy = h / 2;

    drawcircle_bresenham(cx, cy, 50);
    drawcircle_bresenham_enh(cx, cy, 80);

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Circles");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
