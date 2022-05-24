#ifndef UNITYPLOTRENDER_PLOT_H
#define UNITYPLOTRENDER_PLOT_H

#include <memory>

#include "dataset/NormalizedDataset.h"

class Plot {
    explicit Plot(float* x, int x_length, float* y, int y_length);

    void render();
private:
    std::unique_ptr<NormalizedDataset> dataset_;
};


#endif //UNITYPLOTRENDER_PLOT_H
