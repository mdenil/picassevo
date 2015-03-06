//
//  Painter.cpp
//  picassevo
//
//  Created by Misha Denil on 05/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#include <cstddef>

#include "Painter.h"

Painter::Painter()
{
    glGenBuffers(1, &m_vbo);
}

std::vector<unsigned char> Painter::paint(Individual const& individual) const
{
    auto const& genes = individual.get_genes();
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 genes.size() * sizeof(genes[0]),
                 genes.data(),
                 GL_DYNAMIC_DRAW);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glVertexPointer(2, GL_FLOAT, sizeof(genes[0]), (void*)offsetof(Gene, location));
    glColorPointer(4, GL_FLOAT, sizeof(genes[0]), (void*)offsetof(Gene, color));
    
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)genes.size());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    std::vector<unsigned char> pixels(individual.get_size() * 4);
    glReadPixels(0,
                 0,
                 individual.get_width(),
                 individual.get_height(),
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 pixels.data());
    
    return pixels;
}