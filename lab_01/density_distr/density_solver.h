#ifndef _DENSITY_SOLVER_H_
#define _DENSITY_SOLVER_H_

#include "density_functor.h"
#include <tuple>
#include <cstddef>
#include <vector>
#include <memory>

using tuple_ddu = std::tuple<double, double, size_t>;

class BaseDensity {
public:
    BaseDensity();
    virtual ~BaseDensity();

    void set_range(const tuple_ddu & abn_range);

    std::vector<double> compute_xrange_array() const;
    std::vector<double> compute_f_dens_array() const;
    std::vector<double> compute_F_prob_array() const;

    virtual void set_parameter(const double param, const size_t index);

protected:

    std::unique_ptr<BaseDensityFunctor<double>> xrange_functor_;
    std::unique_ptr<BaseDensityFunctor<double>> f_dens_functor_;
    std::unique_ptr<BaseDensityFunctor<double>> F_prob_functor_;

    tuple_ddu range_abn_;

private:

    template <typename Func>
    std::vector<double> compute_functor_data_(Func & ffun) const;

    // Initially empty. Is needed for uniform density.
    virtual void update_functor_range_();
};


class UniformDensity final : public BaseDensity {
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
