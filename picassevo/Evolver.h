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

#include "Individual.h"
#include "Painter.h"
#include "FitnessFunction.h"

class Evolver
{
public:
    Evolver(Individual const& seed, Painter const* painter, FitnessFunction const* fitness);
    
    void run();
    
    Individual const& get_best_individual() const { return *m_best; }
    
private:
    std::unique_ptr<Individual> m_best;
    float m_best_fitness;
    
    Painter const* m_painter;
    FitnessFunction const* m_fitness_function;
    
    int m_step_count;
    int m_rejection_count;
    int m_n_generations;
    std::chrono::time_point<std::chrono::system_clock> m_last_best_time;
};

#endif /* defined(__picassevo__Evolver__) */
