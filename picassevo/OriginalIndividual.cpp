//
//  OriginalIndividual.cpp
//  picassevo
//
//  Created by Misha Denil on 05/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#include <cassert>

#include "OriginalIndividual.h"
#include "Random.h"

OriginalIndividual::OriginalIndividual(unsigned width, unsigned height):
    Individual(width, height)
{
    for (int i = 0; i < 10; ++i) {
        add_triange();
    }
}

void OriginalIndividual::mutate()
{
    /*
    auto random_mutation_type = std::discrete_distribution<>({1, 100, 25});
    auto random_vertex = std::uniform_int_distribution<size_t>(0, m_genes.size() - 1);
    
    size_t target_vertex = random_vertex(randomness);
    
    switch (random_mutation_type(randomness))
    {
        case 0: add_triange(); break;
        case 1: change_triangle_color(target_vertex - 0*(target_vertex % 3)); break;
        case 2: change_vertex_position(random_vertex(randomness)); break;
        default: break;
    }
     */
    add_triange();
}

void OriginalIndividual::add_triange()
{
    auto randx = std::uniform_real_distribution<float>(0, m_width);
    auto randy = std::uniform_real_distribution<float>(0, m_height);
    auto randoffset = std::uniform_real_distribution<float>(-100, 100);
    auto randc = std::uniform_real_distribution<float>(0, 1);
    
    Gene::Color triangle_color = {
        randc(randomness), randc(randomness), randc(randomness), 1.0};
    
    float x = randx(randomness);
    float y = randy(randomness);
    
    for (int i = 0; i < 3; ++i) {
        m_genes.push_back({
            {x + randoffset(randomness), y + randoffset(randomness)}, triangle_color
        });
    }
}

void OriginalIndividual::change_triangle_color(size_t i)
{
    auto channel_picker = std::uniform_int_distribution<>(0, 2);
    auto random_step = std::uniform_real_distribution<float>(-0.1, 0.1);
    
    float step = random_step(randomness);
    int channel = channel_picker(randomness);
    int j = 0;
    //for (size_t j = 0; j < 3; ++j) {
        switch (channel) {
            case 0: m_genes[i+j].color.r += step; break;
            case 1: m_genes[i+j].color.g += step; break;
            case 2: m_genes[i+j].color.b += step; break;
            //case 3: m_genes[i+j].color.a += step; break;
        }
    //}
}

void OriginalIndividual::change_vertex_position(size_t i)
{
    auto random_step = std::uniform_real_distribution<float>(-25, 25);
    
    m_genes[i].location.x += random_step(randomness);
    m_genes[i].location.y += random_step(randomness);
}