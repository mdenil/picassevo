//
//  OriginalIndividual.h
//  picassevo
//
//  Created by Misha Denil on 05/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#ifndef __picassevo__OriginalIndividual__
#define __picassevo__OriginalIndividual__

#include <vector>

#include "Individual.h"

class OriginalIndividual : public Individual
{
public:
    OriginalIndividual(unsigned width, unsigned height);
    
    virtual void mutate();
    
    virtual std::unique_ptr<Individual> clone() const {
        return std::make_unique<OriginalIndividual>(*this);
    }
    
private:
    void add_triange();
    void change_triangle_color(size_t i);
    void change_vertex_position(size_t i);
};


#endif /* defined(__picassevo__OriginalIndividual__) */
