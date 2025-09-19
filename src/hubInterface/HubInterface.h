#pragma once

#include "glad.h"
#include <GLFW/glfw3.h>
#include "dllExport.h"

class PULSE_ENGINE_DLL_API HubInterface
{
public:
    HubInterface();
    ~HubInterface();

    // Main render loop
    void Render();

private:
    GLFWwindow* window = nullptr;

};
