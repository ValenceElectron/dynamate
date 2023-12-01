#ifndef USERINTERFACEMANAGER_H
#define USERINTERFACEMANAGER_H

#include "ResourceManager.hpp"
#include "objects/UserInterfaceElement.hpp"

class UserInterfaceManager : public ResourceManager {
public:
    UserInterfaceManager();

    void addToBuffer(UserInterfaceElement *element);
    UserInterfaceElement* getNext();
    int getBufferSize();
    void handleMouseClick(double x, double y);

private:
    std::vector<UserInterfaceElement*> resourceBuffer;
};

#endif
