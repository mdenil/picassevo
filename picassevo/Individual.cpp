//
//  Individual.cpp
//  picassevo
//
//  Created by Misha Denil on 06/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#include "Individual.h"

Individual::Individual(unsigned width, unsigned height):
    m_width(width),
    m_height(height),
    m_primitive_type(GL_TRIANGLES)
{
    glGenBuffers(1, &m_vbo);
}

void Individual::draw() const {
    //glClear(GL_COLOR_BUFFER_BIT);
    
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