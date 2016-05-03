#include "GameWindow.h"

GameWindow *gameWindow;

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
    // initialize GLFW
    glfwInit();

    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    glfwOpenWindow(WIDTH, HEIGHT, 8, 8, 8, 8, 0, 0, GLFW_WINDOW);
    glfwSetWindowTitle("OpenGL Game");

    gameWindow = new GameWindow(true);

    while (gameWindow->getRunning()) {
        gameWindow->render();
        gameWindow->update();
        gameWindow->setRunning(glfwGetWindowParam(GLFW_OPENED));
    }

    delete gameWindow;

    glfwTerminate();
    return 0;
}
