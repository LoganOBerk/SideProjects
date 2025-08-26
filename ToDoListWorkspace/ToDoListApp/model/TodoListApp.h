#pragma once

#include "TodoListManager.h"
#include "UI.h"

class TodoListApp {
private:
    TodoListManager manager;

public:
    // Main application loop
    void init();
    void run();
    void exit();
};
