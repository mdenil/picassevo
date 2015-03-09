//
//  CircleIndividual.h
//  picassevo
//
//  Created by Misha Denil on 06/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#ifndef __picassevo__CircleIndividual__
#define __picassevo__CircleIndividual__

#include "AbstractLayeredIndividual.h"

class CircleIndividual : public AbstractLayeredIndividual
{
public:
    CircleIndividual(unsigned width, unsigned height, std::string const& bg_color);
    
    CLONEABLE(AbstractIndividual, CircleIndividual);
protected:
    virtual void generate_mutation_genes();
};

#endif /* defined(__picassevo__CircleIndividual__) */
