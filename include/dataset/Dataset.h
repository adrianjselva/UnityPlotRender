#ifndef UNITYPLOTRENDER_DATASET_H
#define UNITYPLOTRENDER_DATASET_H

#include <memory>
#include <vector>

#include "dataset/Summary.h"

class Dataset : std::enable_shared_from_this<Dataset> {
public:
    explicit Dataset();
    explicit Dataset(float* x, int x_length, float* y, int y_length);

    [[nodiscard]] Summary summary() const;
    [[nodiscard]] std::vector<float>& x();
    [[nodiscard]] std::vector<float>& y();

    virtual void Add(float x, float y);
protected:
    std::unique_ptr<Summary> summary_;
    std::vector<float> x_;
    std::vector<float> y_;
    int count_;

    static void CheckSizes(const std::vector<float>&x, const std::vector<float>&y);
};


#endif //UNITYPLOTRENDER_DATASET_H
