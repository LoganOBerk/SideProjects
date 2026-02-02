#pragma once

#include "TaskListManager.h"
#include "UI.h"

class TaskManagerApp {
private:
    TaskListManager manager;

public:
    // Main application loop
    void init();
    void run();
    void exit();
};
