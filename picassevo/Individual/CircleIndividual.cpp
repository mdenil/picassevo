//
//  CircleIndividual.cpp
//  picassevo
//
//  Created by Misha Denil on 06/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#include <GLUT/glut.h>

#include "../lodepng/lodepng.h"

#include "CircleIndividual.h"
#include "Random.h"

CircleIndividual::CircleIndividual(unsigned width, unsigned height, std::string const& bg_color):
    AbstractLayeredIndividual(width, height, bg_color)
{
    m_primitive_type = GL_TRIANGLE_FAN;
}

void CircleIndividual::generate_mutation_genes()
{
    // generate a new circle
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
    
    m_genes.reserve(detail * 3);
    
    m_genes.push_back({x, y, color});
    for (int i = 0; i <= detail; ++i) {
        float o = 2*M_PI*i / detail;
        
        m_genes.push_back({x + r * std::cosf(o), y + r * std::sinf(o), color});
    }
}
