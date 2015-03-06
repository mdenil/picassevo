//
//  Gene.h
//  picassevo
//
//  Created by Misha Denil on 05/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#ifndef __picassevo__Gene__
#define __picassevo__Gene__

struct Gene
{
    struct Point { float x, y; };
    struct Color { float r, g, b, a; };
    
    Point location;
    Color color;
};

#endif /* defined(__picassevo__Gene__) */
