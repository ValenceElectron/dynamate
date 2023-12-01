/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

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
