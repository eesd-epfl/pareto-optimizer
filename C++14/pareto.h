//
// Created by shaqfa on 2019-12-07.
//

#ifndef PARETO_ALGORITHM_PARETO_H
#define PARETO_ALGORITHM_PARETO_H

#include <cmath>
#include "types.h"
#include "random_generator.h"
#include "objective.h"

class pareto {
public:
    UInt population_size, iterations, dimensions;
    Real acceptance_probability;
    std::shared_ptr <objective> obj;
    std::string sampling_method;
    std::shared_ptr<randomness> rand_gen =
            std::make_shared<randomness>();
public:
    pareto(UInt&, UInt&, UInt&, Real&, std::shared_ptr<objective>&, std::string&);
    ~pareto() = default;
    void simulate(RealVec&, RealVec&, RealVec&, RealVec&, RealVec&, RealVec&, RealVec&, RealVec&,
            RealMat&, RealMat&, RealMat&, Real&, Real&);
};
#endif //PARETO_ALGORITHM_PARETO_H