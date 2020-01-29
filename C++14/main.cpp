#include <iostream>
#include "pareto_interface.h"

int main() {

    // Define the user inputs (API)
    /// Algorithmic parameters
    UInt population_size = 30;
    UInt iterations = 20;
    Real acceptance_probability = 0.70;
    std::string sampling_process = "MonteCarlo"; // MonteCarlo or LHS (not implemented yet)
    /**
     *
     * Sphere function -> [2]
     * Sum squares function -> [16]
     * Chung Reynolds function -> [17]
     * Schwefel2.21 function -> [6]
     * Schwefel2.22 function -> [7]
     * Rosenbrock function -> [3]
     * Zakharov function -> [15]
     *
     * De Jong 5 function -> [11] (fixed dimensions 2D)
     * Schwefel function -> [1]
     * Schwefel function -> [1]
     * Griewank function -> [4]
     * Ackley function -> [5]
     * Six-hump camel function -> [12] (fixed dimensions 2D)
     * Michalewicz function (m = 10) -> [8]
     * Rastrangin function -> [9]
     * Shubert function -> [10] (fixed dimensions 2D)
     * Goldstein Price -> [20] (fixed dimensions 2D)
     *
     * Gear train design problem -> [13]
     * Three-bar truss design problem -> [14]
     * Cantilever beam design function -> [18]
     */

    Real objective_option = 1;

    /// Outputs parameters
    bool nonuniform_objective = false; // for problems with non-identical search bandwidths
    bool plot = true;
    bool dump_data = true;

    /// Select objective function
    UInt dimensions = 2;
    Real step_size = 10.e-20; // continuous landscape
    Real w1 = 0., w2 = 0.;

    std::shared_ptr<objective> ob = nullptr;
    if (objective_option == 1)
        ob = std::make_shared<schwefel>();
    else if (objective_option == 2)
        ob = std::make_shared<sphere>();
    else if (objective_option == 3)
        ob = std::make_shared<rosenbrock>();
    else if (objective_option == 4)
        ob = std::make_shared<griewank>();
    else if (objective_option == 5)
        ob = std::make_shared<ackley>();
    else if (objective_option == 6)
        ob = std::make_shared<schwefel2_21>();
    else if (objective_option == 7)
        ob = std::make_shared<schwefel2_22>();
    else if (objective_option == 8)
        ob = std::make_shared<michalewicz>();
    else if (objective_option == 9)
        ob = std::make_shared<rastrangin>();
    else if (objective_option == 10)
        ob = std::make_shared<shubert>();
    else if (objective_option == 11)
        ob = std::make_shared<dejong5>(), dimensions = 2;
    else if (objective_option == 12)
        ob = std::make_shared<six_hump_camel>(), dimensions = 2;
    else if (objective_option == 13)
        ob = std::make_shared<gear_design>(), dimensions = 4, step_size = 1.0e-50;
    else if (objective_option == 14)
        ob = std::make_shared<three_bar_truss>(), dimensions = 2, step_size = 10.e-50, w1 = 1., w2 = 2;
    else if (objective_option == 15)
        ob = std::make_shared<zakharov>();
    else if (objective_option == 16)
        ob = std::make_shared<sum_squares>();
    else if (objective_option == 17)
        ob = std::make_shared<chung_reynolds>();
    else if (objective_option == 18)
        ob = std::make_shared<cantilever_beam_design>(), dimensions = 5, step_size = 10.e-50, w1 = 1., w2 = 2.;
    else if (objective_option == 19)
        ob = std::make_shared<mod_schwefel>();
    else if (objective_option == 20)
        ob = std::make_shared<goldstein>(), dimensions = 2;

    /// The main interface of the algorithm
    std::unique_ptr<pareto_interface> interface  =
            std::make_unique<pareto_interface>(population_size, iterations, dimensions, step_size,
                    w1, w2,acceptance_probability, ob, sampling_process, plot, dump_data,
                    nonuniform_objective);
    interface->optimize();
}
// The End XD