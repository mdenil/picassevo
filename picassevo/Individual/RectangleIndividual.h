//
//  RectangleIndividual.h
//  picassevo
//
//  Created by Misha Denil on 08/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#ifndef __picassevo__RectangleIndividual__
#define __picassevo__RectangleIndividual__

#include "AbstractLayeredIndividual.h"

class RectangleIndividual : public AbstractLayeredIndividual
{
public:
    RectangleIndividual(unsigned width, unsigned height, std::string const& bg_color);
    
    CLONEABLE(AbstractIndividual, RectangleIndividual);
protected:
    virtual void generate_mutation_genes();
};

#endif /* defined(__picassevo__RectangleIndividual__) */
