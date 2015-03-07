//
//  CircleIndividual.cpp
//  picassevo
//
//  Created by Misha Denil on 06/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#include "CircleIndividual.h"
#include "Random.h"

CircleIndividual::CircleIndividual(unsigned width, unsigned height):
    Individual(width, height)
{
    for (int i=0; i < 1; ++i) {
        add_circle();
    }
}

void CircleIndividual::mutate()
{
    add_circle();
}

void CircleIndividual::add_circle()
{
    auto randx = std::uniform_real_distribution<float>(0, m_width);
    auto randy = std::uniform_real_distribution<float>(0, m_height);
    auto randr = std::lognormal_distribution<float>(1, 0.7);
    auto randc = std::uniform_real_distribution<float>(0, 1);
    
    //float c = randc(randomness);
    Gene::Color color = {
        //c, c, c, 1.0};
        randc(randomness), randc(randomness), randc(randomness), 1.0};
    
    float x = randx(randomness);
    float y = randy(randomness);
    float r = randr(randomness);
    
    int detail = 10;
    
    for (int i = 0; i < detail; ++i) {
        float o1 = 2*M_PI*i / detail;
        float o2 = 2*M_PI*(i+1) / detail;
        
        m_genes.push_back({x, y, color});
        m_genes.push_back({x + r * std::cosf(o1), y + r * std::sinf(o1), color});
        m_genes.push_back({x + r * std::cosf(o2), y + r * std::sinf(o2), color});
    }
}
