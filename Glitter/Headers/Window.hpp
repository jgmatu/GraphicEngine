#ifndef WINDOW_H
#define WINDOW_H


class Window : public System {

public:
    
     Window();
    ~Window();

    // All systems must update each game loop
    void Update (float dt) = 0;

    // It's good practice to separate the construction and initialization code.
    void Init (void) = 0;

    // This recieves any messages sent to the core engine in Engine.cpp
    void SendMessage (Message *msg) = 0;

private:

    GLFWwindow *_window;

};

#endif
