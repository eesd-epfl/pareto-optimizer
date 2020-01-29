//
// Created by shaqfa on 06/12/2019.
//

#ifndef C__14_RANDOM_GENERATOR_H
#define C__14_RANDOM_GENERATOR_H

#include <random>
#include <ctime>
#include "types.h"
#include <iostream>
#include <cstdlib>

class randomness{
    /**
     * A uniform random number generator engine
     */
public:
    std::mt19937 generator;
    std::uniform_real_distribution<Real> distribution;
public:
    explicit randomness() {generator.seed(std::random_device()());};
    double generate(){return distribution(generator);}
    ~randomness() = default;
};
#endif //C__14_RANDOM_GENERATOR_H