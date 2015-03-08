//
//  Evolver.h
//  picassevo
//
//  Created by Misha Denil on 05/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#ifndef __picassevo__Evolver__
#define __picassevo__Evolver__

#include <memory>
#include <chrono>

#include "AbstractIndividual.h"
#include "FitnessFunction.h"

class Evolver
{
public:
    Evolver(AbstractIndividual const& seed, FitnessFunction* fitness);
    
    void run();
    
    AbstractIndividual const& get_best_individual() const { return *m_best; }
    
private:
    std::unique_ptr<AbstractIndividual> m_best;
    float m_best_fitness;
    
    FitnessFunction* m_fitness_function;
    
    int m_step_count;
    int m_rejection_count;
    int m_n_generations;
    int m_n_success;
    std::chrono::time_point<std::chrono::system_clock> m_last_best_time;
};

#endif /* defined(__picassevo__Evolver__) */
