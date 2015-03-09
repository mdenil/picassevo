//
//  AbstractLayeredIndividual.h
//  picassevo
//
//  Created by Misha Denil on 08/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#ifndef __picassevo__AbstractLayeredIndividual__
#define __picassevo__AbstractLayeredIndividual__

#include "AbstractIndividual.h"

class AbstractLayeredIndividual : public AbstractIndividual
{
public:
    AbstractLayeredIndividual(unsigned width, unsigned height, std::string const& bg_color):
        AbstractIndividual(width, height, bg_color)
    {}
    
    virtual void mutate();
    virtual void draw() const;
    
protected:
    virtual void generate_mutation_genes() = 0;
};

#endif /* defined(__picassevo__AbstractLayeredIndividual__) */
