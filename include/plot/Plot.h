//
// Created by adrianselva on 5/23/22.
//

#ifndef UNITYPLOTRENDER_PLOT_H
#define UNITYPLOTRENDER_PLOT_H

#include <memory>

#include "dataset/NormalizedDataset.h"

class Plot {
private:
    std::unique_ptr<NormalizedDataset> dataset_;
    long id_;
};


#endif //UNITYPLOTRENDER_PLOT_H
