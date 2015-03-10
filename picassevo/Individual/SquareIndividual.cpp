//
//  SquareIndividual.cpp
//  picassevo
//
//  Created by Misha Denil on 09/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#include "SquareIndividual.h"

#include "Random.h"

SquareIndividual::SquareIndividual(unsigned width, unsigned height, std::string const& bg_color):
    AbstractLayeredIndividual(width, height, bg_color)
{
    m_primitive_type = GL_QUADS;
}


void SquareIndividual::generate_mutation_genes()
{
    // generate a new rectangle
    auto randx = std::uniform_real_distribution<float>(0, m_width);
    auto randy = std::uniform_real_distribution<float>(0, m_height);
    auto randr = std::lognormal_distribution<float>(1, 1.0);
    auto randc = std::uniform_real_distribution<float>(0, 1);
    
    Gene::Color color = {
        randc(randomness), randc(randomness), randc(randomness), 1.0};
    
    float x = randx(randomness);
    float y = randy(randomness);
    float r = randr(randomness);
    
    m_genes.reserve(4);
    m_genes.push_back({x - r, y - r, color});
    m_genes.push_back({x - r, y + r, color});
    m_genes.push_back({x + r, y + r, color});
    m_genes.push_back({x + r, y - r, color});
}
