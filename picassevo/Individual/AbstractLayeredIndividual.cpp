//
//  AbstractLayeredIndividual.cpp
//  picassevo
//
//  Created by Misha Denil on 08/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#include "AbstractLayeredIndividual.h"


void AbstractLayeredIndividual::mutate()
{
    m_genes.clear();
    generate_mutation_genes();
    
    glClear(GL_COLOR_BUFFER_BIT);
    draw();
    AbstractIndividual::draw();
    
    glReadPixels(0,
                 0,
                 get_width(),
                 get_height(),
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 m_pixels.data());
}

void AbstractLayeredIndividual::draw() const
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