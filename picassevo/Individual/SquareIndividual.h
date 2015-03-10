//
//  SquareIndividual.h
//  picassevo
//
//  Created by Misha Denil on 09/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#ifndef __picassevo__SquareIndividual__
#define __picassevo__SquareIndividual__

#include "AbstractLayeredIndividual.h"

class SquareIndividual : public AbstractLayeredIndividual
{
public:
    SquareIndividual(unsigned width, unsigned height, std::string const& bg_color);
    
    CLONEABLE(AbstractIndividual, SquareIndividual);
protected:
    virtual void generate_mutation_genes();
};

#endif /* defined(__picassevo__SquareIndividual__) */
