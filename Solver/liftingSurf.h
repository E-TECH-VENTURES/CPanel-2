//
//  liftingSurf.h
//  CPanel
//
//  Created by Chris Satterwhite on 10/15/14.
//  Copyright (c) 2014 Chris Satterwhite. All rights reserved.
//

#ifndef __CPanel__liftingSurf__
#define __CPanel__liftingSurf__

#include <stdio.h>
#include "surface.h"
#include "wake.h"

class liftingSurf : public surface
{
    wake* wakeSurf;
    
public:
    liftingSurf(int surfID,Eigen::MatrixXd* nodes) : surface(surfID,nodes)
    {
        wakeSurf = new wake();
    }
    
    ~liftingSurf()
    {
        delete wakeSurf;
    }
    
    void addPanel(const Eigen::VectorXi &verts, Eigen::Matrix<bool,Eigen::Dynamic,1> TEnodes,int surfID);
    void setTEneighbors(panelOctree* oct);
    wake* getWake() {return wakeSurf;}
    std::vector<panel*> getAllPanels();
    std::vector<wakePanel*> getWakePanels() {return wakeSurf->getPanels();}
};

#endif /* defined(__CPanel__liftingSurf__) */
