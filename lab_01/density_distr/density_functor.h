#ifndef _DENSITY_FUNCTORS_H_
#define _DENSITY_FUNCTORS_H_

template <typename T>
class BaseDensityFunctor {
public:
    virtual ~BaseDensityFunctor();

    virtual T value(const T x) const = 0;
    virtual T operator() (const T x) const = 0;
};


template <typename T>
class UnaryDensityFunctor : public BaseDensityFunctor<T> {
public:
    UnaryDensityFunctor();
    virtual ~UnaryDensityFunctor();

    virtual T value(const T x) const;
    virtual T operator() (const T x) const;
};

template <typename T>
class UniformDensityFunctor : public BaseDensityFunctor<T> {
public:
    UniformDensityFunctor();
    virtual ~UniformDensityFunctor();

    void set_a_left (const T a_in);
    void set_b_right(const T b_in);

    virtual T value(const T x) const;
    virtual T operator() (const T x) const;

protected:
    T a_left_;
    T b_right_;
};

template <typename T>
class UniformDistributionFFunctor : public UniformDensityFunctor<T> {
public:
    UniformDistributionFFunctor();
    virtual ~UniformDistributionFFunctor();

    virtual T value(const T x) const;
    virtual T operator() (const T x) const;
};


// Exponential
// ..

// Normal
// ..

// Poisson
// ..

#endif // _DENSITY_FUNCTORS_H_
