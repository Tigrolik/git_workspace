#ifndef _GAMEWINDOW_H_
#define _GAMEWINDOW_H_

#include <iostream>
#include <GL/glew.h>
#include <GL/glfw.h>

class GameWindow {

    private:

        bool _running;
        GLfloat _width;
        GLfloat _height;
        GLuint _vertexBufferID;

    public:

        GameWindow(bool running);

        void setRunning(bool newRunning);
        bool getRunning();

        void render();
        void update();
};

#endif
