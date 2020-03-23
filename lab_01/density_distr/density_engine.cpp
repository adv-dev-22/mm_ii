#include "density_engine.h"
#include <utility>
#include <algorithm>

#include <QDebug>

template <typename T>
BaseDensityEngine<T>::BaseDensityEngine():
functor_(nullptr),
range_abn_(0.0, 0.0, 0),
vec_data_() {
}

//virtual
template <typename T>
BaseDensityEngine<T>::~BaseDensityEngine() {
}

template <typename T>
void BaseDensityEngine<T>::set_range(const tuple_ttu<T> & abn_range) {
    range_abn_ = abn_range;
    update_functor_range_();
}

template <typename T>
void BaseDensityEngine<T>::compute() {
    vec_data_ = compute_functor_data_(*functor_);
}

//virtual
template <typename T>
void BaseDensityEngine<T>::set_parameter(const T /*unused*/,
                                         const uint8_t /*unused*/) {
    // Reimplement in inherited classes,
    // in case additional parameters input is required.
}

template <typename T>
template <typename Func>
std::vector<T> BaseDensityEngine<T>::compute_functor_data_(Func & ffun) const {

    const double a_left  = std::get<0>(range_abn_);
    const double b_right = std::get<1>(range_abn_);
    const size_t n_size  = std::get<2>(range_abn_);

    if (n_size < 2) throw std::out_of_range("Wrong input range...");

    std::vector<T> buffer_data(n_size + 1);

    const T h = (b_right - a_left) / static_cast<T>(n_size);

    for (size_t i = 0; i <= n_size; ++i) {
        const T x_i = a_left + static_cast<T>(i) * h;
        buffer_data.at(i) = ffun(x_i);

        //qDebug() << buffer_data.at(i);
    }

    return std::move(buffer_data);
}

//virtual
template <typename T>
void BaseDensityEngine<T>::update_functor_range_() {
    // it is reimplemented in uniform density class.
}

template class BaseDensityEngine<float>;
template class BaseDensityEngine<double>;

///////////////////////////////////////////////////////////////////////////////

template <typename T>
UniformRange<T>::UniformRange():
BaseDensityEngine<T>() {
    this->functor_ = std::make_unique<UnaryDensityFunctor<T>>();
}

template class UniformRange<float>;
template class UniformRange<double>;

///////////////////////////////////////////////////////////////////////////////

template <typename T>
UniformDensity<T>::UniformDensity():
BaseDensityEngine<T>() {
}

//virtual
template <typename T>
UniformDensity<T>::~UniformDensity() {
}

//virtual
template <typename T>
void UniformDensity<T>::update_functor_range_() {

    const T tmp_a_left  = std::get<0>(this->range_abn_);
    const T tmp_b_right = std::get<1>(this->range_abn_);

    auto f_buffer = std::make_unique<UniformDensityFunctor<T>>();
    f_buffer->set_a_left (tmp_a_left);
    f_buffer->set_b_right(tmp_b_right);
    this->functor_.reset(f_buffer.release());
}

///////////////////////////////////////////////////////////////////////////////

// End of the file

