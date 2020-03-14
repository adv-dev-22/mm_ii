#include "density_functor.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////////////

//virtual
template <typename T>
BaseDensityFunctor<T>::~BaseDensityFunctor() {

}

template class BaseDensityFunctor<float>;
template class BaseDensityFunctor<double>;

///////////////////////////////////////////////////////////////////////////////

template <typename T>
UnaryDensityFunctor<T>::UnaryDensityFunctor():
BaseDensityFunctor<T>() {

    std::cout << "constructor Unary F" << std::endl;
}

//virtual
template <typename T>
UnaryDensityFunctor<T>::~UnaryDensityFunctor() {

}

//virtual
template <typename T>
T UnaryDensityFunctor<T>::value(const T x) const {
    return x;
}

//virtual
template <typename T>
T UnaryDensityFunctor<T>::operator() (const T x) const {
    return x;
}

template class UnaryDensityFunctor<float>;
template class UnaryDensityFunctor<double>;

///////////////////////////////////////////////////////////////////////////////

template <typename T>
UniformDensityFunctor<T>::UniformDensityFunctor():
BaseDensityFunctor<T>(),
a_left_(0.),
b_right_(0.) {

}

//virtual
template <typename T>
UniformDensityFunctor<T>::~UniformDensityFunctor() {

}

template <typename T>
void UniformDensityFunctor<T>::set_a_left (const T a_in) {
    a_left_ = a_in;
}

template <typename T>
void UniformDensityFunctor<T>::set_b_right(const T b_in) {
    b_right_ = b_in;
}

//virtual
template <typename T>
T UniformDensityFunctor<T>::value(const T x) const {
    return this->operator()(x);
}

//virtual
template <typename T>
T UniformDensityFunctor<T>::operator() (const T x) const {
    const T tmp_factor = b_right_ - a_left_;
    // check non zero condition
    return 1.0 / tmp_factor;
}

template class UniformDensityFunctor<float>;
template class UniformDensityFunctor<double>;

///////////////////////////////////////////////////////////////////////////////

template <typename T>
UniformDistributionFFunctor<T>::UniformDistributionFFunctor():
UniformDensityFunctor<T>() {

}

template <typename T>
UniformDistributionFFunctor<T>::~UniformDistributionFFunctor() {

}

//virtual
template <typename T>
T UniformDistributionFFunctor<T>::value(const T x) const {
    return this->operator()(x);
}

//virtual
template <typename T>
T UniformDistributionFFunctor<T>::operator() (const T x) const {
    const T tmp_factor = this->b_right_ - this->a_left_;
    return tmp_factor * (x - this->a_left_) ;
}

template class UniformDistributionFFunctor<float>;
template class UniformDistributionFFunctor<double>;

///////////////////////////////////////////////////////////////////////////////



// ..

// End of the file
