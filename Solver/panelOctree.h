//
//  panelOctree.h
//  CPanel
//
//  Created by Chris Satterwhite on 5/5/14.
//  Copyright (c) 2014 Chris Satterwhite. All rights reserved.
//

#ifndef __CPanel__panelOctree__
#define __CPanel__panelOctree__

#include <iostream>
#include "octree.h"
#include "panel.h"

class panel;

class panelOctree : public octree<panel>
{
    
public:
    panelOctree() : octree() {}
    
    std::array<double,3> findRefPoint(const panel &obj);
};

#endif /* defined(__CPanel__panelOctree__) */
