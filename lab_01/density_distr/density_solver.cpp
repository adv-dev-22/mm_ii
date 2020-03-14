#include "density_solver.h"
#include <utility>
#include <algorithm>

BaseDensity::BaseDensity():
xrange_functor_(nullptr),
f_dens_functor_(nullptr),
F_prob_functor_(nullptr),
range_abn_(0.0, 0.0, 0) {

}

//virtual
BaseDensity::~BaseDensity() {
}

void BaseDensity::set_range(const tuple_ddu & abn_range) {
    range_abn_ = abn_range;
    update_functor_range_();
}

std::vector<double> BaseDensity::compute_xrange_array() const {
    return compute_functor_data_(*xrange_functor_);
}

std::vector<double> BaseDensity::compute_f_dens_array() const {
    return compute_functor_data_(*f_dens_functor_);
}

std::vector<double> BaseDensity::compute_F_prob_array() const {
    return compute_functor_data_(*F_prob_functor_);
}

//virtual
void BaseDensity::set_parameter(const double /*unused*/,
                                const size_t /*unused*/) {
    // Reimplement in inherited classes,
    // in case additional parameters input is required.
}

template <typename Func>
std::vector<double> BaseDensity::compute_functor_data_(Func & ffun) const {

    const double a_left  = std::get<0>(range_abn_);
    const double b_right = std::get<1>(range_abn_);
    const size_t n_size  = std::get<2>(range_abn_);

    if (n_size < 2) throw std::out_of_range("Wrong input range...");

    std::vector<double> buffer_data(n_size + 1);

    const double h = (b_right - a_left) / static_cast<double>(n_size);

    for (size_t i = 0; i <= n_size; ++i) {

        const double x_i = a_left + static_cast<double>(i) * h;
        buffer_data.at(i) = ffun(x_i);
    }

    return std::move(buffer_data);
}

//virtual
void BaseDensity::update_functor_range_() {
    // it is reimplemented in uniform density class.
}

///////////////////////////////////////////////////////////////////////////////

UniformDensity::UniformDensity():
BaseDensity() {
    xrange_functor_ = std::make_unique<UnaryDensityFunctor<double>>();
}

//virtual
UniformDensity::~UniformDensity() {
}

//virtual
void UniformDensity::update_functor_range_() {

    const double tmp_a_left  = std::get<0>(range_abn_);
    const double tmp_b_right = std::get<1>(range_abn_);

    auto f_buffer = std::make_unique<UniformDensityFunctor<double>>();
    f_buffer->set_a_left (tmp_a_left);
    f_buffer->set_b_right(tmp_b_right);
    f_dens_functor_.reset(f_buffer.release());

    auto F_buffer = std::make_unique<UniformDistributionFFunctor<double>>();
    F_buffer->set_a_left (tmp_a_left);
    F_buffer->set_b_right(tmp_b_right);
    F_prob_functor_.reset(F_buffer.release());
}

///////////////////////////////////////////////////////////////////////////////

// End of the file

