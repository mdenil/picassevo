//
//  Individual.cpp
//  picassevo
//
//  Created by Misha Denil on 06/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#include "AbstractIndividual.h"

AbstractIndividual::AbstractIndividual(unsigned width, unsigned height):
    m_width(width),
    m_height(height),
    m_primitive_type(GL_TRIANGLES)
{
    glGenBuffers(1, &m_vbo);
    
    m_pixels.resize(get_size() * 4);
    for (int i = 0; i < m_pixels.size(); ++i) {
        // black with full alpha
        //m_pixels[i] = i % 4 != 3 ? 0 : 255;
        
        // white
        m_pixels[i] = 255;
    }
}

void AbstractIndividual::draw() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 m_genes.size() * sizeof(m_genes[0]),
                 m_genes.data(),
                 GL_DYNAMIC_DRAW);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glVertexPointer(2, GL_FLOAT, sizeof(m_genes[0]), (void*)offsetof(Gene, location));
    glColorPointer(4, GL_FLOAT, sizeof(m_genes[0]), (void*)offsetof(Gene, color));
    
    glDrawArrays(m_primitive_type, 0, (GLsizei)m_genes.size());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}