#include "density_solver.h"
#include <utility>
#include <algorithm>

BaseDensity::BaseDensity():
range_abn_(0.0, 0.0, 0) {

}

//virtual
BaseDensity::~BaseDensity() {

}

void BaseDensity::set_range(const tuple_ddu abn_range) {
    range_abn_ = abn_range;
}

//virtual
std::vector<double> BaseDensity::compute_x_data() const {

    const double a_left  = std::get<0>(range_abn_);
    const double b_right = std::get<1>(range_abn_);
    const size_t n_size  = std::get<2>(range_abn_);

    if (n_size < 2) throw std::out_of_range("Wrong input range...");

    std::vector<double> tmp_x(n_size + 1);

    const double h = (b_right - a_left) / static_cast<double>(n_size);

    for (size_t i = 0; i <= n_size; ++i) {
        tmp_x.at(i) = a_left + static_cast<double>(i) * h;
    }

    return std::move(tmp_x);
}

//virtual
std::vector<double> BaseDensity::compute_y_data() const {

    const double a_left  = std::get<0>(range_abn_);
    const double b_right = std::get<1>(range_abn_);
    const size_t n_size  = std::get<2>(range_abn_);

    if (n_size < 2) throw std::out_of_range("Wrong input range...");

    std::vector<double> tmp_y_data(n_size + 1);

    const double h = (b_right - a_left) / static_cast<double>(n_size);

    for (size_t i = 0; i <= n_size; ++i) {
        const double x_i = a_left + static_cast<double>(i) * h;
        tmp_y_data.at(i) = density_value_(x_i);
    }

    return std::move(tmp_y_data);
}

//virtual
void BaseDensity::set_parameter(const double /*unused*/,
                                const size_t /*unused*/) {
}

UniformDensity::UniformDensity():
BaseDensity(),
a_left_(0),
b_right_(0) {

}

//virtual
UniformDensity::~UniformDensity() {

}

//virtual
void UniformDensity::set_parameter(const double param,
                                   const size_t index) {

    if (index > 1) {
        throw std::invalid_argument("Index is out of range!");
    }

    if (0 == index) {
        a_left_ = param;
    }
    if (1 == index) {
        b_right_ = param;
    }

    if (a_left_ >= b_right_) {
        throw std::invalid_argument("a >= b which is wrong.");
    }
}

//virtual
double UniformDensity::density_value_(const double /* unused */) const {
    return 1.0 / (b_right_ - a_left_);
}

// End of the file
