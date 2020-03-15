#ifndef _DENSITY_SOLVER_H_
#define _DENSITY_SOLVER_H_

#include "density_functor.h"
#include <tuple>
#include <cstddef>
#include <vector>
#include <memory>
#include <cstdint>

template <typename T>
using tuple_ttu = std::tuple<T, T, size_t>;

template <typename T>
class BaseDensityEngine {
public:
    BaseDensityEngine();
    virtual ~BaseDensityEngine();

    void set_range(const tuple_ttu<T> & abn_range);
    void compute();

    virtual void set_parameter(const T param, const uint8_t index);

    const std::vector<T> & get_data() const;

protected:
    std::unique_ptr<BaseDensityFunctor<T>> functor_;
    tuple_ttu<T> range_abn_;

private:
    std::vector<T> vec_data_;

    template <typename Func>
    std::vector<T> compute_functor_data_(Func & ffun) const;

    // Initially empty. Is needed for uniform density.
    virtual void update_functor_range_();
};


template <typename T>
class UniformRange final : public BaseDensityEngine<T> {
public:
    UniformRange();
};


template <typename T>
class UniformDensity final : public BaseDensityEngine<T> {
public:
    UniformDensity();
    virtual ~UniformDensity();

private:
    virtual void update_functor_range_() final;
};

// Exponential
// ..

// Normal
// ..

// Poisson
// ..


#endif // _DENSITY_SOLVER_H_
