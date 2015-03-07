//
//  CircleIndividual.h
//  picassevo
//
//  Created by Misha Denil on 06/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#ifndef __picassevo__CircleIndividual__
#define __picassevo__CircleIndividual__

#include <vector>

#include "Individual.h"

class CircleIndividual : public Individual
{
public:
    CircleIndividual(unsigned width, unsigned height);
    
    virtual void mutate();
    
    void draw() const;
    
    virtual std::unique_ptr<Individual> clone() const {
        return std::make_unique<CircleIndividual>(*this);
    }
    
private:
    void generate_mutation_genes();
};

#endif /* defined(__picassevo__CircleIndividual__) */
