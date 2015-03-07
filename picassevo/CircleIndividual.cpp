//
//  CircleIndividual.cpp
//  picassevo
//
//  Created by Misha Denil on 06/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#include <GLUT/glut.h>
#include <iostream>

#include "lodepng/lodepng.h"

#include "CircleIndividual.h"
#include "Random.h"

CircleIndividual::CircleIndividual(unsigned width, unsigned height):
    Individual(width, height)
{
    m_primitive_type = GL_QUADS;
    
    m_pixels.clear();
    m_pixels.resize(get_size() * 4);
    
    for (int i = 0; i < m_pixels.size(); ++i) {
        // black with full alpha
        //m_pixels[i] = i % 4 != 3 ? 0 : 255;
        
        // white
        m_pixels[i] = 255;
    }
}

void CircleIndividual::mutate()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw our current state.
    draw();
    
    // generate a mutation
    generate_mutation_genes();
    
    // apply the mutation
    Individual::draw();
    
    // save our new state
    glReadPixels(0,
                 0,
                 get_width(),
                 get_height(),
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 m_pixels.data());
}


void CircleIndividual::generate_mutation_genes()
{
    //*
    // generate a new rectangle
    auto randx = std::uniform_real_distribution<float>(0, m_width);
    auto randy = std::uniform_real_distribution<float>(0, m_height);
    auto randr = std::lognormal_distribution<float>(1, 1.0);
    auto randc = std::uniform_real_distribution<float>(0, 1);
    
    Gene::Color color = {
        randc(randomness), randc(randomness), randc(randomness), 1.0};
    
    float x = randx(randomness);
    float y = randy(randomness);
    float rx = randr(randomness);
    float ry = randr(randomness);
    
    m_genes.clear();
    m_genes.reserve(6);
    
    m_genes.push_back({x - rx, y - ry, color });
    m_genes.push_back({x - rx, y + ry, color });
    m_genes.push_back({x + rx, y + ry, color });
    m_genes.push_back({x + rx, y - ry, color });
    //*/
    
    /*
    // generate a new triangle
    auto randx = std::uniform_real_distribution<float>(0, m_width);
    auto randy = std::uniform_real_distribution<float>(0, m_height);
    auto randoffset = std::uniform_real_distribution<float>(-25, 25);
    auto randc = std::uniform_real_distribution<float>(0, 1);
    
    Gene::Color triangle_color = {
        randc(randomness), randc(randomness), randc(randomness), 1.0};
    
    float x = randx(randomness);
    float y = randy(randomness);
    
    m_genes.clear();
    m_genes.reserve(3);
    for (int i = 0; i < 3; ++i) {
        m_genes.push_back({
            {x + randoffset(randomness), y + randoffset(randomness)}, triangle_color
        });
    }
    //*/
    
    /*
    // generate a new circle
    auto randx = std::uniform_real_distribution<float>(0, m_width);
    auto randy = std::uniform_real_distribution<float>(0, m_height);
    auto randr = std::lognormal_distribution<float>(1, 0.7);
    //auto randr = std::uniform_real_distribution<float>(10, 30);
    auto randc = std::uniform_real_distribution<float>(0, 1);
    
    //float c = randc(randomness);
    Gene::Color color = {
        //c, c, c, 1.0};
        randc(randomness), randc(randomness), randc(randomness), 1.0};
    
    float x = randx(randomness);
    float y = randy(randomness);
    float r = randr(randomness);
    
    int detail = 10;
    
    m_genes.clear();
    m_genes.reserve(detail * 3);
    for (int i = 0; i < detail; ++i) {
        float o1 = 2*M_PI*i / detail;
        float o2 = 2*M_PI*(i+1) / detail;
        
        m_genes.push_back({x, y, color});
        m_genes.push_back({x + r * std::cosf(o1), y + r * std::sinf(o1), color});
        m_genes.push_back({x + r * std::cosf(o2), y + r * std::sinf(o2), color});
    }
    //*/
}


void CircleIndividual::draw() const
{
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 get_width(),
                 get_height(),
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 m_pixels.data());
    
    glBegin(GL_QUADS);
    glTexCoord2d(0, 1); glVertex2f(0, 0);
    glTexCoord2d(1, 1); glVertex2f(get_width(), 0);
    glTexCoord2d(1, 0); glVertex2f(get_width(), get_height());
    glTexCoord2d(0, 0); glVertex2f(0, get_height());
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}