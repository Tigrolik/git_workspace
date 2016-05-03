#include "GameWindow.h"

typedef struct {
    GLfloat posCoords[3];
} VertexData;

#define sq_size 100

VertexData vertices[] = {
    {0.0f, 0.0f, 0.0f},
    {sq_size, 0.0f, 0.0f},
    {sq_size, sq_size, 0.0f},
    {0.0f, sq_size, 0.0f},
};

GameWindow::GameWindow(bool running): _running(running), _width(800 / 9 * 16),
_height(800), _vertexBufferID(0)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glViewport(0.0f, 0.0f, _width, _height);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, _width, 0, _height);
    glMatrixMode(GL_MODELVIEW);

    glGenBuffers(1, &_vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(VertexData), (GLvoid *)
            offsetof(VertexData, posCoords));
}

void GameWindow::setRunning(bool newRunning) {
    _running = newRunning;
}

bool GameWindow::getRunning() {
    return _running;
}

void GameWindow::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);
    /*
    glBegin(GL_QUADS);
    glVertex2f(0.0f,   0.0f); // bottom-left
    glVertex2f(100.0f, 0.0f); // bottom-right
    glVertex2f(100.0f, 100.0f); // top-right
    glVertex2f(0.0f,   100.0f); // top-left
    glEnd();
    */
    // glDrawArrays(GL_QUADS, 0, 4);

    glfwSwapBuffers();
}

void GameWindow::update() {
}
