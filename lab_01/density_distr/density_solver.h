#ifndef _DENSITY_SOLVER_H_
#define _DENSITY_SOLVER_H_

#include <tuple>
#include <cstddef>
#include <vector>

using tuple_ddu = std::tuple<double, double, size_t>;

class BaseDensity {
public:
    BaseDensity();
    virtual ~BaseDensity();

    void set_range(const tuple_ddu abn_range);

    virtual std::vector<double> compute_x_data() const;
    virtual std::vector<double> compute_y_data() const;

    virtual void set_parameter(const double param, const size_t index);

protected:
    virtual double density_value_(const double x) const = 0;

private:
    tuple_ddu range_abn_;
};


class UniformDensity final : public BaseDensity {
public:
    UniformDensity();
    virtual ~UniformDensity();

    void set_parameter(const double param, const size_t index);

protected:
    virtual double density_value_(const double ) const;

private:
    double a_left_;
    double b_right_;
};

// Poisson
// ..

// Gauss
// ..

#endif // _DENSITY_SOLVER_H_
