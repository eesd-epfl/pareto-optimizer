//
// Created by shaqfa on 06/12/2019.
//

#include "pareto_interface.h"

pareto_interface::pareto_interface(UInt& population_size, UInt& iterations, UInt& dimensions, Real& step_size,
        Real& w1, Real& w2, Real& acceptance_probability, std::shared_ptr<objective>& obj, std::string& sampling_method,
        bool& plot, bool& dump_data, bool& nonuniform_objective)
        : population_size(population_size), iterations(iterations), dimensions(dimensions), step_size(step_size), w1(w1),
        w2(w2), acceptance_probability(acceptance_probability), obj(obj), sampling_method(sampling_method),
        plot(plot), dump_data(dump_data), nonuniform_objective(nonuniform_objective){

    // Initialize the needed containers
    penalty.resize(population_size);
    penalty_history.resize(iterations + 1);
    funval.resize(population_size);
    funval_history.resize(iterations + 1);
    LB.resize(dimensions);
    UB.resize(dimensions);
    steps.resize(dimensions);
    population.resize(population_size);
    //random_population.resize(population_size);
    bounds_history.resize(iterations + 1);
    population_history.resize((iterations + 1) * population_size);
    funval_populations_history.resize((iterations + 1) * population_size);
    limits_history.resize(iterations + 1);

    // Fill-up the containers
    std::fill(penalty.begin(), penalty.end(), 0.);
    std::fill(penalty_history.begin(), penalty_history.end(), 0.);
    std::fill(funval.begin(), funval.end(), 0.);
    std::fill(funval_history.begin(), funval_history.end(), 0.);
    if (nonuniform_objective){
        // for nonuniform bandwidths (the first half of a tuple will be LB and the second half for the UB)
        for(UInt i = 0; i < dimensions; ++i)
            LB[i] = obj->get_bounds()[i],
            UB[i] = obj->get_bounds()[i + dimensions];
    }
    else{
        std::fill(LB.begin(), LB.end(), obj->get_bounds()[0]);
        std::fill(UB.begin(), UB.end(), obj->get_bounds()[1]);
    }
    std::fill(steps.begin(), steps.end(), step_size);
    std::fill(population.begin(), population.end(), RealVec(dimensions, 0.));
    //std::fill(random_population.begin(), random_population.end(), RealVec(dimensions, 0.)); // for different sampling methods
    std::fill(population_history.begin(), population_history.end(), RealVec(dimensions, 0.));
    std::fill(funval_populations_history.begin(), funval_populations_history.end(), 0.);
    std::fill(limits_history.begin(), limits_history.end(), RealVec(dimensions * 2, 0));
}

void pareto_interface::optimize() {

    /// start optimizing here
    std::clock_t t1;
    t1 = clock();

    /// The core of the algorithm is called here
    pareto_optimizer->simulate(funval, funval_history, funval_populations_history, penalty,
            penalty_history, LB, UB, steps, population, population_history, limits_history,
            w1, w2);

    std::cout << "\n\nThe processing elapsed time: "<< (Real)(clock() - t1)/CLOCKS_PER_SEC << " sec"<< std::endl;

    if (dump_data){
        // Dump all the data to HDD/SSD
        // *.csv files

        std::string dump_funval = "funval";
        std::string dump_funval_history = "funval_history";
        std::string dump_penalty_history = "penalty_history";
        std::string dump_funval_populations_history = "funval_populations_history";
        std::string dump_population_history = "population_history";
        std::string dump_limits_history = "limits_history";
        std::string dump_inputs = "input_data";

        std::unique_ptr<csv_dump> dump_funval_d = std::make_unique<csv_dump>(dump_funval);
        std::unique_ptr<csv_dump> dump_funval_history_d = std::make_unique<csv_dump>(dump_funval_history);
        std::unique_ptr<csv_dump> dump_penalty_history_d = std::make_unique<csv_dump>(dump_penalty_history);
        std::unique_ptr<csv_dump> dump_population_history_d = std::make_unique<csv_dump>(dump_population_history);
        std::unique_ptr<csv_dump> dump_funval_populations_history_d =
                std::make_unique<csv_dump>(dump_funval_populations_history);
        std::unique_ptr<csv_dump> dump_limits_history_d = std::make_unique<csv_dump>(dump_limits_history);
        std::unique_ptr<csv_dump> dump_inputs_d = std::make_unique<csv_dump>(dump_inputs);

        dump_funval_d->dump(funval);
        dump_funval_history_d->dump(funval_history);
        dump_penalty_history_d->dump(penalty_history);
        dump_population_history_d->dump(population_history);
        dump_limits_history_d->dump(limits_history);
        dump_funval_populations_history_d ->dump(funval_populations_history);

        // Define the inputs to be exported
        RealVec input_data {(Real)population_size, (Real)iterations, (Real)dimensions, acceptance_probability};
        dump_inputs_d->dump(input_data);

        std::cout<< "\nAdditional processes:"<<std::endl;
        std::cout<< "\t|__ 1- Data has been flushed."<<std::endl;
    }

    if(dump_data and plot){
        // Plot the data using Python 3.6
        // works if and only if dump_data was true too.
        std::system("python3 plotter.py");
        std::cout << "\t|__ 2- Data has been plotted and saved." << std::endl;
    }
}