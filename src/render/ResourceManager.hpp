/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

class ResourceManager {
public:
    ResourceManager();
    int getCurrentIndex();

protected:
    int currentIndex;

};

#endif
