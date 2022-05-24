#ifndef UNITYPLOTRENDER_SUMMARY_H
#define UNITYPLOTRENDER_SUMMARY_H

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <memory>

#include "dataset/Dataset.h"

class Summary {
public:
    explicit Summary();
    explicit Summary(const std::vector<float>& x, const std::vector<float>& y);

    void Add(float x, float y);

    [[nodiscard]] float x_min() const;
    [[nodiscard]] float y_min() const;

    [[nodiscard]] float x_max() const;
    [[nodiscard]] float y_max() const;

    [[nodiscard]] float x_range() const;
    [[nodiscard]] float y_range() const;

private:
    float x_min_;
    float y_min_;

    float x_max_;
    float y_max_;

    float x_range_;
    float y_range_;

    void UpdateSummaries(float x, float y);
};


#endif //UNITYPLOTRENDER_SUMMARY_H
