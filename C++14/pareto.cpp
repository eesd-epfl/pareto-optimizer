//
// Created by shaqfa on 2019-12-07.
//

#include "pareto.h"
#include <iomanip>

pareto::pareto(UInt &population_size, UInt &iterations, UInt &dimensions, Real &acceptance_probability,
        std::shared_ptr <objective> &obj, std::string &sampling_method): population_size(population_size),
        iterations(iterations), dimensions(dimensions), acceptance_probability(acceptance_probability), obj(obj),
        sampling_method(sampling_method){}

void pareto::simulate(RealVec& funval, RealVec& funval_history, RealVec& funval_populations_history, RealVec& penalty,
        RealVec& penalty_history, RealVec& LB, RealVec& UB, RealVec& steps, RealMat& population,
        RealMat& population_history, RealMat& limits_history, Real& w1, Real& w2)
        {
    // Note: sampling_methods will be ignored in this version (only simple MonteCarlo will be implemented)

    /// Misc variables
    UInt counter = 0; RealVec ans; RealVec best_sol; UInt best_idx; bool new_solution = true;
    Real deviation = 0., reduced_LB, reduced_UB;

    /// Initialize the basic population
    for (UInt i = 0; i < population_size; ++i){
        for (UInt j = 0; j < dimensions; ++j){
            population[i][j] += LB[j] + std::round((UB[j] - LB[j]) *
                    rand_gen->generate() / steps[j]) * steps[j];
        }
        population_history[i] = population[i];
    }

    /// Evaluate the initial population
    for (auto && v : population){
        ans = obj->eval(v, w1, w2);
        funval[counter] = ans[0]; penalty[counter] = ans[1];
        funval_populations_history[counter] = ans[0];
        counter++;
    }

    /// Find the current best solution
    best_idx = vo::min_idx(funval);
    best_sol = population[best_idx];
    funval_history[0] = funval[best_idx];
    penalty_history[0] = penalty[best_idx];

    /// The core of the algorithm (critical loop)
    for(UInt i = 1; i <iterations + 1; ++i) {
        for (UInt j = 0; j < population_size; ++j) {
            for (UInt k = 0; k < dimensions; ++k) {
                if (new_solution)
                    deviation = std::abs(0.5 * (1 - acceptance_probability) * \
                    (1 - ((Real) i / (Real) iterations))) * (UB[k] - LB[k]);

                reduced_LB = best_sol[k] - deviation;
                reduced_LB = vo::max(reduced_LB, LB[k]);

                reduced_UB = reduced_LB + 2 * deviation;
                reduced_UB = vo::min(reduced_UB, UB[k]);

                limits_history[i][k * 2] = reduced_LB;
                limits_history[i][k * 2 + 1] = reduced_UB;

                // Choose a new solution
                if (rand_gen->generate() <= acceptance_probability){
                    population[j][k] = std::round((reduced_LB + rand_gen->generate() *
                            (reduced_UB - reduced_LB)) / steps[k]) * steps[k];
                } else{
                    population[j][k] = std::round((LB[k] + rand_gen->generate() *
                            (UB[k] - LB[k])) / steps[k]) * steps[k];
                }
            }

            // Evaluate the solution
            ans = obj->eval(population[j], w1, w2);
            funval[j] = ans[0]; penalty[j] = ans[1];
            // Hold the population memory
            population_history[i * population_size + j] = population[j];
            funval_populations_history[i * population_size + j] = ans[0];
        }

        // Update the current best solution
        if (vo::min_val(funval) < funval_history[i - 1]){
            new_solution = true;
            best_idx =  vo::min_idx(funval);
            best_sol = population[best_idx];
            funval_history[i] = funval[best_idx];
            penalty_history[i] = penalty[best_idx];
            // we need to add the penalty part
        } else{
            new_solution = false;
            funval_history[i] = funval_history[i - 1];
            penalty_history[i] = penalty_history[i - 1];
        }

        // Inform the user - online monitoring of convergence
        std::cout<< std::setprecision(15) <<"Iteration No. "<< i << " and best fitness is: " <<
        funval_history[i] <<" | Penalty value is: " << penalty_history[i] << std::endl;
    }

    // Inform the user with the final results
    std::cout<< "The best solution is: \n"<<std::endl;
    vo::print(best_sol);
    std::cout<< "\nThe best fitness is: "<< funval_history[iterations] << std::endl;
    if (penalty_history[iterations] > 0)
        std::cout << "Warning: the obtained solution is not valid, penalty value = "
        << penalty_history[iterations] << std::endl;
}