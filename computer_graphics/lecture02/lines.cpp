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

void drawline_steps(int x1, int y1, int x2, int y2)
{
    int x = x1, y = y1;

    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    while (x <= x2 && y <= y2) {
        glVertex2i(x, y);
        ++x;
        ++y;
    }
    glEnd();
}

void drawline_dda(int x1, int y1, int x2, int y2)
{
    int x = x1;
    float y = y1 + 0.5, slope = (static_cast<float>(y2) - y1) / (x2 - x1);

    glBegin(GL_POINTS);
    glColor3f(0.0, 1.0, 0.0);
    while (x <= x2) {
        glVertex2i(x, static_cast<int>(y));
        y += slope;
        ++x;
    }
    glEnd();
}

void drawline_dda_fp(int x1, int y1, int x2, int y2)
{
    int x = x1, count = x2 - x1;
    long y = y1 << 16, slope = ((y2 - y1) << 16) / (x2 - x1);
    /*
    cout << ((y2 - y1) << 16) << endl;
    cout << slope << endl;
    */

    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2i(x1, y1);
    while (count > 0) {
        --count;
        y += slope;
        glVertex2i(++x, y >> 16);
    }
    glEnd();
}

void drawline_bresenham(int x1, int y1, int x2, int y2)
{
    int x = x1, y = y1, dx = x2 - x1, dy = y2 - y1;
    int count = dx;

    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 1.0);
    glVertex2i(x, y);
    while (count > 0) {
        --count;
        ++x;
        if (dy * x - dx * (y + 0.5) - x1 * dy + y1 * dx > 0)
            ++y;
        glVertex2i(x, y);
    }
    glEnd();
}

void drawline_bresenham_enh(int x1, int y1, int x2, int y2)
{
    const int dx = abs(x2 - x1), dy = abs(y2 - y1),
          incrdx = dx + dx, incrdy = dy + dy;
    int y = y1, e = dx;

    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 0.0);
    for (int x = x1; x <= x2; ++x) {
        glVertex2i(x, y);
        e -= incrdy;
        if (e < 0) {
            ++y;
            e += incrdx;
        }
    }
    glEnd();
}

void drawline_bresenham_mod(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    const bool steep = dy > dx;
    if (steep) {
        std::swap(x1, y1);
        std::swap(x2, y2);
        std::swap(dx, dy);
    }

    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    int e = dx;
    const int incrdy = dy + dy;
    const int incrdx = dx + dx;
    const int ystep = (y1 < y2) ? 1 : -1;
    int y = y1;

    glBegin(GL_POINTS);
    glColor3f(0.0, 0.0, 1.0);
    for (int x = x1; x <= x2; ++x) {
        if (steep)
            glVertex2i(y, x);
        else
            glVertex2i(x, y);

        e -= incrdy;
        if (e < 0) {
            y += ystep;
            e += incrdx;
        }
    }
}


void display(void)
{
    /* clear screen */
    glClear(GL_COLOR_BUFFER_BIT);

    /* set the pixel size */
    glPointSize(1.0f);

    // get window center coordinates
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);

    /* draw interval */
    glBegin(GL_LINES);
    glColor3d(0.75, 0.75, 1);
    glVertex2d(10, 30);
    glVertex2d(w - 10, h - 10);
    glEnd();

    drawline_dda(10, 40, w - 10, h + 10);
    drawline_dda(10, h - 100, 20, h - 10);

    drawline_bresenham(20, 20, w - 10, h - 20);
    drawline_bresenham(20, h - 100, 30, h - 10);

    drawline_bresenham_enh(20, 0, w - 10, h - 50);
    drawline_bresenham_enh(w - 200, 100, w - 30, 10);

    drawline_bresenham_mod(70, h - 100, 80, h - 10);
    drawline_bresenham_mod(w - 210, 100, w - 40, 10);

    drawline_dda_fp(10, 60, w - 10, h + 60);
    drawline_dda_fp(40, h - 100, 50, h - 10);

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
    glutCreateWindow("Lines");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
