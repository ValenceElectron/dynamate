#include "UserInterfaceManager.hpp"

UserInterfaceManager::UserInterfaceManager()
: ResourceManager() { }

void UserInterfaceManager::addToBuffer(UserInterfaceElement *element) {
    std::cout << "Pushing object into vector...\n";
    resourceBuffer.push_back(element);
}

UserInterfaceElement* UserInterfaceManager::getNext() {
    UserInterfaceElement* element = resourceBuffer.at(currentIndex);
    if (!element->isVisible()) { element->setVisibility(true); }

    if ((currentIndex + 1) >= resourceBuffer.size()) { currentIndex = 0; }
    else { currentIndex++; }

    return element;
}

int UserInterfaceManager::getBufferSize() { return resourceBuffer.size(); }

void UserInterfaceManager::handleMouseClick(double x, double y) {
    for (UserInterfaceElement* element : resourceBuffer) {
        if (element->getObjectType() == "uibutton") { element->isClicked(x, y); }
    }
}
