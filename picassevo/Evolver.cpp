//
//  Evolver.cpp
//  picassevo
//
//  Created by Misha Denil on 05/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#include <iostream>
#include <chrono>

#include "Evolver.h"

Evolver::Evolver(Individual const& seed, Painter const* painter, FitnessFunction const* fitness):
    m_best(seed.clone()),
    m_painter(painter),
    m_fitness_function(fitness),
    m_step_count(0),
    m_rejection_count(0),
    m_n_generations(0),
    m_last_best_time(std::chrono::system_clock::now())
{
    m_best_fitness = m_fitness_function->evaluate(*m_best, m_painter);
    
}


void Evolver::run()
{
    auto candidate = m_best->clone();
    candidate->mutate();
    float candidate_fitness = m_fitness_function->evaluate(*candidate, m_painter);
    
    m_step_count += 1;
        
    if (candidate_fitness < m_best_fitness) {
        std::swap(m_best, candidate);
        std::swap(m_best_fitness, candidate_fitness);
        
        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_last_best_time);
        m_last_best_time = now;
        
        float fps = (float)m_step_count / elapsed.count() * 1000;
        
        m_n_generations += 1;
        
        std::cout
            << "C: " << m_best_fitness << " "
            << "FPS: " << fps << " "
            << "R: " << m_rejection_count << " "
            << "G: " << m_n_generations
            << std::endl;
        
        m_step_count = 0;
        m_rejection_count = 0;
    }
    else {
        m_rejection_count += 1;
    }
}