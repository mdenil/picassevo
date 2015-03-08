//
//  TriangleIndividual.cpp
//  picassevo
//
//  Created by Misha Denil on 08/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#include <GLUT/glut.h>

#include "../lodepng/lodepng.h"

#include "TriangleIndividual.h"
#include "Random.h"

TriangleIndividual::TriangleIndividual(unsigned width, unsigned height):
AbstractLayeredIndividual(width, height)
{
    m_primitive_type = GL_TRIANGLES;
}

void TriangleIndividual::generate_mutation_genes()
{
    // generate a new triangle
    auto randx = std::uniform_real_distribution<float>(0, m_width);
    auto randy = std::uniform_real_distribution<float>(0, m_height);
    auto randoffset = std::uniform_real_distribution<float>(-25, 25);
    auto randc = std::uniform_real_distribution<float>(0, 1);
     
    Gene::Color color = {
        randc(randomness), randc(randomness), randc(randomness), 1.0};
     
    float x = randx(randomness);
    float y = randy(randomness);
    
    m_genes.reserve(3);
    for (int i = 0; i < 3; ++i) {
        m_genes.push_back({
            x + randoffset(randomness), y + randoffset(randomness), color});
    }
}