//
// Created by adrianselva on 5/23/22.
//

#ifndef UNITYPLOTRENDER_PLOTMANAGER_H
#define UNITYPLOTRENDER_PLOTMANAGER_H

#include <unordered_map>
#include "Plot.h"


class PlotManager {
private:
    std::unordered_map<std::string, Plot> plots_;
public:

};


#endif //UNITYPLOTRENDER_PLOTMANAGER_H
