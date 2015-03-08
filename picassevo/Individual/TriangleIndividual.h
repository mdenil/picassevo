//
//  TriangleIndividual.h
//  picassevo
//
//  Created by Misha Denil on 08/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#ifndef __picassevo__TriangleIndividual__
#define __picassevo__TriangleIndividual__

#include "AbstractLayeredIndividual.h"

class TriangleIndividual : public AbstractLayeredIndividual
{
public:
    TriangleIndividual(unsigned width, unsigned height);
    
    CLONEABLE(AbstractIndividual, TriangleIndividual);
protected:
    virtual void generate_mutation_genes();
};

#endif /* defined(__picassevo__TriangleIndividual__) */
