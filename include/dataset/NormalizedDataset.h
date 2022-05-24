#ifndef UNITYPLOTRENDER_NORMALIZEDDATASET_H
#define UNITYPLOTRENDER_NORMALIZEDDATASET_H

#include "Dataset.h"

class NormalizedDataset : Dataset {
public:
    explicit NormalizedDataset(float* x, int x_length, float* y, int y_length,
                               float x_normalized_range, float y_normalized_range, float x_offset, float y_offset);
    explicit NormalizedDataset(float x_normalized_range, float y_normalized_range, float x_offset, float y_offset);

    void Add(float x, float y) override;
private:
    float x_normalized_range_;
    float y_normalized_range_;
    float x_offset_;
    float y_offset_;

    std::unique_ptr<Dataset> normalized_dataset_;

    void Normalize();
    [[nodiscard]] float NormalizedX(float x);
    [[nodiscard]] float NormalizedY(float y);
    void UpdateParameters(float x_normalized_range, float y_normalized_range, float x_offset, float y_offset);
};


#endif //UNITYPLOTRENDER_NORMALIZEDDATASET_H
