#include "plot/Plot.h"

Plot::Plot(float *x, int x_length, float *y, int y_length)
          : dataset_(std::make_unique<NormalizedDataset>(x, x_length, y, y_length)) {

}
    