#ifndef HUB_COMPONENT_H
#define HUB_COMPONENT_H

#include <string>

class GenericComponent
{
    public:
        GenericComponent(const std::string& name) : name(name) {}
        ~GenericComponent() {}

        virtual void RenderMainPage() const = 0;
        virtual bool RenderButton() const = 0;
    private:
        std::string name;
};


// extern "C" __declspec(dllexport) GenericComponent* CreateComponent() 
// {
//     return new GenericComponent();
// }

#endif