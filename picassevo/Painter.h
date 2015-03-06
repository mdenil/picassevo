//
//  Painter.h
//  picassevo
//
//  Created by Misha Denil on 05/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#ifndef __picassevo__Painter__
#define __picassevo__Painter__

#include <vector>

#include <GLUT/glut.h>

#include "Individual.h"

class Painter
{
public:
    Painter();
    
    std::vector<unsigned char> paint(Individual const& individual) const;
    
private:
    GLuint m_vbo;
};

#endif /* defined(__picassevo__Painter__) */
