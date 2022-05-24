#include "dataset/NormalizedDataset.h"

NormalizedDataset::NormalizedDataset(float* x, int x_length, float* y, int y_length, float x_normalized_range,
                                     float y_normalized_range, float x_offset, float y_offset)
                                     : x_normalized_range_(x_normalized_range),
                                       y_normalized_range_(y_normalized_range),
                                       x_offset_(x_offset),
                                       y_offset_(y_offset),
                                       raw_dataset_(std::make_unique<Dataset>(x, x_length, y, y_length)),
                                       normalized_dataset_(std::make_unique<Dataset>(x, x_length, y, y_length)) {
    Normalize();
}

NormalizedDataset::NormalizedDataset(float x_normalized_range, float y_normalized_range, float x_offset,
                                     float y_offset)
                                     : x_normalized_range_(x_normalized_range),
                                       y_normalized_range_(y_normalized_range),
                                       x_offset_(x_offset),
                                       y_offset_(y_offset),
                                       raw_dataset_(std::make_unique<Dataset>()),
                                       normalized_dataset_(std::make_unique<Dataset>()) {}

NormalizedDataset::NormalizedDataset(float *x, int x_length, float *y, int y_length)
        : x_normalized_range_(0),
          y_normalized_range_(0),
          x_offset_(0),
          y_offset_(0),
          raw_dataset_(std::make_unique<Dataset>(x, x_length, y, y_length)),
          normalized_dataset_(std::make_unique<Dataset>(x, x_length, y, y_length)) {}

void NormalizedDataset::Add(float x, float y) {
    raw_dataset_->Add(x, y);
    normalized_dataset_->Add(NormalizedX(x), NormalizedY(y));
}

void NormalizedDataset::Normalize() {
    std::vector<float>* x = &normalized_dataset_->x();
    std::vector<float>* y = &normalized_dataset_->y();

    for(auto i = 0; i < x->size(); i++) {
        x->at(i) = NormalizedX(x->at(i));
        y->at(i) = NormalizedY(y->at(i));
    }
}

float NormalizedDataset::NormalizedX(float x) {
    return ((x - raw_dataset_->summary().x_min()) / raw_dataset_->summary().x_range()) * (x_normalized_range_) + x_offset_;
}

float NormalizedDataset::NormalizedY(float y) {
    return ((y - raw_dataset_->summary().y_min()) / raw_dataset_->summary().y_range()) * (y_normalized_range_) + y_offset_;
}

void NormalizedDataset::UpdateParameters(float x_normalized_range, float y_normalized_range, float x_offset, float y_offset) {
    x_normalized_range_ = x_normalized_range;
    y_normalized_range_ = y_normalized_range;
    x_offset_ = x_offset;
    y_offset_ = y_offset;

    Normalize();
}
