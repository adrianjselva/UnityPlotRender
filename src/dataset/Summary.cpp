#include "dataset/Summary.h"

Summary::Summary() {
    x_min_ = 0;
    y_min_ = 0;

    x_max_ = 0;
    y_max_ = 0;

    x_range_ = 0;
    y_range_ = 0;
}

Summary::Summary(const std::vector<float>& x, const std::vector<float>& y) {
    if (x.size() != y.size()) {
       const std::string x_length = "[x]: " + std::to_string(x.size()) + "\n";
       const std::string y_length = "[y]: " + std::to_string(y.size()) + "\n";

       const std::string message = x_length + y_length + "Lists must be same length.\n";
       throw std::invalid_argument(message);
    }

    x_min_ = *std::min_element(std::begin(x), std::end(x));
    y_min_ = *std::min_element(std::begin(y), std::end(y));

    x_max_ = *std::max_element(std::begin(x), std::end(x));
    y_max_ = *std::max_element(std::begin(y), std::end(y));

    x_range_ = x_max_ - x_min_;
    y_range_ = y_max_ - y_min_;
}

void Summary::Add(float x, float y) {
    UpdateSummaries(x, y);
}

void Summary::UpdateSummaries(float x, float y) {
    x_min_ = std::min(x_min_, x);
    y_min_ = std::min(y_min_, y);

    x_max_ = std::max(x_max_, x);
    y_max_ = std::max(y_max_, y);

    x_range_ = x_max_ - x_min_;
    y_range_ = y_max_ - y_min_;
}

float Summary::y_min() const {
    return y_min_;
}

float Summary::x_min() const {
    return x_min_;
}

float Summary::x_max() const {
    return x_max_;
}

float Summary::y_max() const {
    return y_max_;
}

float Summary::x_range() const {
    return x_range_;
}

float Summary::y_range() const {
    return y_range_;
}
