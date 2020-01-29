//
// Created by shaqfa on 06/12/2019.
//

#ifndef C__14_PARETO_INTERFACE_H
#define C__14_PARETO_INTERFACE_H

#include <iostream>
#include <ctime>
#include <string>
#include "types.h"
#include "objective.h"
#include "csv_writer.h"
#include "random_generator.h"
#include "pareto.h"

class pareto_interface {
/**
   This is the general interface of the Pareto Algorithm
 */
public:
    UInt population_size, iterations, dimensions, step_size;
    Real acceptance_probability, w1, w2;
    std::string sampling_method; // to be implemented ..
    std::shared_ptr<objective> obj;
    bool plot, dump_data, nonuniform_objective;
public:
    RealMat population, bounds_history, population_history, limits_history; //,random_population;
    RealVec funval, penalty, penalty_history, funval_history, LB, UB, steps, funval_populations_history;
private:
    std::unique_ptr<pareto> pareto_optimizer = std::make_unique<pareto>(population_size,
            iterations, dimensions,acceptance_probability, obj,sampling_method);
public:
    explicit pareto_interface(UInt&, UInt&, UInt&, Real&, Real&, Real&, Real&, std::shared_ptr<objective>&,
            std::string&, bool&, bool&, bool&);
    void optimize();
};
#endif //C__14_PARETO_INTERFACE_H