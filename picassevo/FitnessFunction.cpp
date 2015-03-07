//
//  FitnessFunction.cpp
//  picassevo
//
//  Created by Misha Denil on 05/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#include <cassert>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <iterator>

#include "lodepng/lodepng.h"

#include "FitnessFunction.h"


FitnessFunction::FitnessFunction(std::string const& target_image_name)
{
    unsigned err = lodepng::decode(m_target_image_data, m_width, m_height, target_image_name);
    assert(err == 0);
    
    // turn target upside down so it looks right side up
    int cs = 4;
    int rs = m_width*cs;
    
    for (int i = 0; i < m_height / 2; ++i) {
        for (int j = 0; j < m_width; ++j) {
            for (int c = 0; c < 4; ++c) {
                std::swap(m_target_image_data[i*rs + j*cs + c],
                          m_target_image_data[(m_height - i - 1)*rs + j*cs + c]);
            }
        }
    }
    
    //lodepng::encode("test.png", m_target_image_data, m_width, m_height);
}

float FitnessFunction::evaluate(Individual const& individual) const
{
    std::vector<unsigned char> const& pixels = individual.get_pixels();
    
    assert(pixels.size() == m_target_image_data.size());
    
    std::vector<float> errors;
    std::transform(pixels.begin(), pixels.end(),
                   m_target_image_data.begin(),
                   std::back_inserter(errors),
                   [](unsigned char x, unsigned char y) -> float {
                       return std::abs((float)x - (float)y);
                   });
    
    return std::accumulate(errors.begin(), errors.end(), 0.0f);
}