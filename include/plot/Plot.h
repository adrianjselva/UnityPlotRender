#ifndef UNITYPLOTRENDER_PLOT_H
#define UNITYPLOTRENDER_PLOT_H

#include <memory>

#include "dataset/NormalizedDataset.h"

class Plot {
    explicit Plot(float* x, int x_length, float* y, int y_length, void* texture, int texture_width, int texture_height);
    explicit Plot(void* texture, int texture_width, int texture_height);

    void render();
private:
    std::unique_ptr<NormalizedDataset> dataset_;
    void* texture_;
    int texture_width_;
    int texture_height_;
};


#endif //UNITYPLOTRENDER_PLOT_H
