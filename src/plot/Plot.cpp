#include "plot/Plot.h"

Plot::Plot(float *x, int x_length, float *y, int y_length, void* texture, int texture_width, int texture_height)
          : dataset_(std::make_unique<NormalizedDataset>(x, x_length, y, y_length)),
            texture_width_(texture_width),
            texture_height_(texture_height),
            texture_(texture){
}

Plot::Plot(void* texture, int texture_width, int texture_height)
          : texture_(texture),
            texture_width_(texture_width),
            texture_height_(texture_height),
            dataset_(std::make_unique<NormalizedDataset>(texture_width, texture_height, 0, 0)){}

void Plot::render() {
    if(!texture_) {
        return;
    }
}
    