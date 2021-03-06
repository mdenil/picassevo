//
//  FitnessFunction.h
//  picassevo
//
//  Created by Misha Denil on 05/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#ifndef __picassevo__FitnessFunction__
#define __picassevo__FitnessFunction__

#include <string>
#include <vector>

#include "AbstractIndividual.h"

class FitnessFunction
{
public:
    FitnessFunction(std::string const& target_image_name);
    
    float evaluate(AbstractIndividual const& individual) const;
    
    unsigned int get_width() const { return m_width; }
    unsigned int get_height() const { return m_height; }
    
    std::vector<unsigned char> const& get_target() const { return m_target_image_data; }
    
private:
    std::vector<unsigned char> m_target_image_data;
    unsigned int m_width, m_height;
};

#endif /* defined(__picassevo__FitnessFunction__) */
