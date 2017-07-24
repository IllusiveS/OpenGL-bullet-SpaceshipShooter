//
// Created by wysocki on 22/07/2017.
//

#ifndef STATEK_WINDOW_H
#define STATEK_WINDOW_H


#include <glfw3.h>

class Window {
public:
    Window();
    ~Window();

public:
    GLFWwindow* window;

private:
    int SetupWindow();
};


#endif //STATEK_WINDOW_H
