//
//  Individual.h
//  picassevo
//
//  Created by Misha Denil on 06/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#ifndef __picassevo__Individual__
#define __picassevo__Individual__

#include <GLUT/glut.h>

#include <memory>
#include <vector>

#include "Gene.h"

class AbstractIndividual
{
public:
    AbstractIndividual(unsigned width, unsigned height);
    virtual ~AbstractIndividual() {}
    
    virtual void mutate() = 0;
    virtual std::unique_ptr<AbstractIndividual> clone() const = 0;
    
    virtual void draw() const;
    
    virtual std::vector<Gene>& get_genes() { return m_genes; }
    virtual std::vector<Gene> const& get_genes() const { return m_genes; }
    
    virtual unsigned get_width() const { return m_width; }
    virtual unsigned get_height() const { return m_height; }
    virtual unsigned get_size() const { return m_width * m_height; };
    
    virtual std::vector<unsigned char> const& get_pixels() const { return m_pixels; }
    

protected:
    std::vector<Gene> m_genes;
    unsigned m_width, m_height;
    
    GLenum m_primitive_type;
    std::vector<unsigned char> m_pixels;
    
    GLuint m_vbo;
};

#define CLONEABLE(BASE, DERIVED) \
virtual std::unique_ptr<BASE> clone() const { \
    return std::make_unique<DERIVED>(*this); \
}

#endif /* defined(__picassevo__Individual__) */
