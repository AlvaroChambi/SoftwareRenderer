//
//  Color.h
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 11/1/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef Color_h
#define Color_h

class Color
{
public:
    Color(int r, int g, int b) :
        r(r),
        g(g),
        b(b),
        a(255)
    {
    
    }
    Color(int r, int g, int b, int a) :
        r(r),
        g(g),
        b(b),
        a(a)
    {
        
    }
    ~Color(){}
    int r;
    int g;
    int b;
    int a;
};

#endif /* Color_h */
