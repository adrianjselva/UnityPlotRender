#include "dataset/Dataset.h"

Dataset::Dataset() {
    count_ = 0;
    summary_ = std::make_unique<Summary>();
}

Dataset::Dataset(float* x, int x_length, float* y, int y_length) : x_(x, x + x_length),
                                                                   y_(y, y + y_length) {
    CheckSizes(x_, y_);

    count_ = (int) x_.size();
    summary_ = std::make_unique<Summary>(x_, y_);
}

Summary Dataset::summary() const {
    return *summary_;
}

std::vector<float>& Dataset::x() {
    return x_;
}

std::vector<float>& Dataset::y() {
    return y_;
}

void Dataset::Add(float x, float y) {
    count_ += 1;
    x_.push_back(x);
    y_.push_back(y);

    summary_->Add(x, y);
}

void Dataset::CheckSizes(const std::vector<float>& x, const std::vector<float>& y) {
    if (x.size() != y.size()) {
        const std::string x_length = "[x]: " + std::to_string(x.size()) + "\n";
        const std::string y_length = "[y]: " + std::to_string(y.size()) + "\n";

        const std::string message = x_length + y_length + "Lists must be same length.\n";
        throw std::invalid_argument(message);
    }
}
