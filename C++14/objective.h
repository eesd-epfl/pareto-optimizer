//
// Created by shaqfa on 06/12/2019.
//

#ifndef C__14_OBJECTIVE_H
#define C__14_OBJECTIVE_H

#include <cmath>
#include <tuple>
#include "types.h"

// Abstract class - Objective Interface
class objective{
public:
    virtual RealVec& eval(RealVec&, Real&, Real&) = 0;
    virtual RealVec get_bounds() = 0;
private:
    virtual void penalize(RealVec&, Real&, Real&){};
};

// Schwefel Function
class schwefel : public objective{

public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:
    void penalize(RealVec&, Real&, Real&) override;
};

// Modified Schwefel Function
class mod_schwefel : public objective{
public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:
    void penalize(RealVec&, Real&, Real&) override;
};

// Sphere Function
class sphere : public objective{

public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:;
    void penalize(RealVec&, Real&, Real&) override;
};

// Sum squares Function
// The exact answer should be f(x) = 0. at x = [0, 0, ..etc]
class sum_squares : public objective{
public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:;
    void penalize(RealVec&, Real&, Real&) override;
};

// Sum squares Function
// The exact answer should be f(x) = 0. at x = [0, 0, ..etc]
class chung_reynolds : public objective{
public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:;
    void penalize(RealVec&, Real&, Real&) override;
};

// Rosenbrock function
class rosenbrock : public objective{
// The exact answer should be f(x) = 0. at x = [1, 1, ..etc]
public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:;
    void penalize(RealVec&, Real&, Real&) override;
};

// Griewank function
class griewank : public objective{
// The exact answer should be f(x) = 0. at x = [0, 0, ..etc]
public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:
    void penalize(RealVec&, Real&, Real&) override;
};

// Ackley function
class ackley : public objective{
// The exact answer should be f(x) = 0. at x = [0, 0, ..etc]
public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:
    void penalize(RealVec&, Real&, Real&) override;
};

// Schwefel 2.22 function
class schwefel2_22 : public objective{
// The exact answer should be f(x) = 0. at x = [0, 0, ..etc]
public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:
    void penalize(RealVec&, Real&, Real&) override;
};

// Schwefel 2.21 function
class schwefel2_21 : public objective{
// The exact answer should be f(x) = 0. at x = [0, 0, ..etc]
public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:
    void penalize(RealVec&, Real&, Real&) override;
};

// Michalewicz function
class michalewicz : public objective{

public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:
    void penalize(RealVec&, Real&, Real&) override;
};

// Rastrangin function
class rastrangin : public objective{

public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:
    void penalize(RealVec&, Real&, Real&) override;
};

// Shubert function
// Exact answer = -186.7309
class shubert : public objective{

public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:
    void penalize(RealVec&, Real&, Real&) override;
};

// DeJong5 function
// Exact answer =
class dejong5 : public objective{

public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:
    void penalize(RealVec&, Real&, Real&) override;
};

// Six-hump camel function
// Exact answer = −1.0316
class six_hump_camel : public objective{
public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:
    void penalize(RealVec&, Real&, Real&) override;
};

// Zakharov function
// Exact answer = 0. for all x = [0, ..., 0]
class zakharov : public objective{
public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:
    void penalize(RealVec&, Real&, Real&) override;
};

// Goldstein price function
// Exact answer = 0. for all x = [0, ..., 0]
class goldstein : public objective{
public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:
    void penalize(RealVec&, Real&, Real&) override;
};

//********************* Engineering problems *********************

// Gear train design problem
class gear_design : public objective{
public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:
    void penalize(RealVec&, Real&, Real&) override;
};

// Three-bar truss problem
class three_bar_truss : public objective{
public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:
    void penalize(RealVec&, Real&, Real&) override;
};

// Cantilever beam design problem
class cantilever_beam_design : public objective{
public:
    RealVec& eval(RealVec&, Real&, Real&) override;
    RealVec get_bounds() override;
private:
    void penalize(RealVec&, Real&, Real&) override;
};
#endif