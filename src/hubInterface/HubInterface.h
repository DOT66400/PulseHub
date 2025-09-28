#pragma once

#include "glad.h"
#include <GLFW/glfw3.h>
#include "dllExport.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

class GenericComponent;

class PULSE_ENGINE_DLL_API HubInterface
{
public:
    HubInterface();
    ~HubInterface();

    // Main render loop
    void Render();

private:
    GLFWwindow* window = nullptr;

    std::vector<GenericComponent*> component;

    GenericComponent* selectedComponent;

};


std::vector<std::string> GetAllDlls(const std::string& directory);