//
//  PanelTest.cpp
//  CPanel
//
//  Created by Chris Satterwhite on 3/26/14.
//  Copyright (c) 2014 Chris Satterwhite. All rights reserved.
//

#include "PanelTest.h"


PanelTest::PanelTest()
{
    TEST_ADD(PanelTest::test_setGeomTri);
    TEST_ADD(PanelTest::test_setGeomQuad);
    TEST_ADD(PanelTest::test_addNeighbor);
}


void PanelTest::test_setGeomTri()
{
    Eigen::Vector3i vertices = {0,1,2};
    Eigen::MatrixXd nodes(3,3);
    nodes << 0,0,0,3,0,0,0,3,0;
    panel p(vertices,&nodes,1);
    
    bool flag = true;
    Eigen::Vector3i verts = p.getVerts();
    if (verts(0) != vertices(0) || verts(1) != vertices(1) || verts(2) != vertices(2))
    {
        flag = false;
    }
    TEST_ASSERT_MSG(flag, "Vertices Set Incorrectly")
    
    flag = true;
    Eigen::Vector3d center = p.getCenter();
    if (center(0) != 1 || center(1) != 1 || center(2) != 0)
    {
        flag = false;
    }
    TEST_ASSERT_MSG(flag, "Center Set Incorrectly");
    
    flag = true;
    Eigen::Vector3d norm = p.getNormal();
    if (norm(0) != 0 || norm(1) != 0 || norm(2) != 1)
    {
        flag = false;
    }
    TEST_ASSERT_MSG(flag,"Normal Set Incorrectly");
}

void PanelTest::test_setGeomQuad()
{
    Eigen::Vector4i vertices = {0,1,2,3};
    Eigen::MatrixXd nodes(4,3);
    nodes << 0,0,0,1,0,0,1,1,0,0,1,0;
    panel p(vertices,&nodes,1);
    
    bool flag = true;
    Eigen::Vector4i verts = p.getVerts();
    if (verts(0) != vertices(0) || verts(1) != vertices(1) || verts(2) != vertices(2) || verts(3) != vertices(3))
    {
        flag = false;
    }
    TEST_ASSERT_MSG(flag, "Vertices Set Incorrectly")
    
    flag = true;
    Eigen::Vector3d center = p.getCenter();
    if (center(0) != 0.5 || center(1) != 0.5 || center(2) != 0)
    {
        flag = false;
    }
    TEST_ASSERT_MSG(flag, "Center Set Incorrectly");
    
    flag = true;
    Eigen::Vector3d norm = p.getNormal();
    if (norm(0) != 0 || norm(1) != 0 || norm(2) != 1)
    {
        flag = false;
    }
    TEST_ASSERT_MSG(flag,"Normal Set Incorrectly");
    
}

void PanelTest::test_addNeighbor()
{
    Eigen::MatrixXd nodes(6,3);
    Eigen::MatrixXi indices(4,3);
    std::vector<panel*> panels;
    
    nodes << 0,0,0 , 1,0,0 , 2,0,0 , 2,1,0 , 1,1,0 , 0,1,0;
    
    indices << 0,1,5 , 5,1,4 , 4,1,2 , 2,3,4;
    
    //  5 ___4___3
    //   |\  |\  |
    //   | \ | \ |
    //   |__\|__\|
    //  0    1    2
    
    panel* p;
    for (int i=0; i<4; i++)
    {
        p = new panel(indices.row(i),&nodes,1);
        panels.push_back(p);
    }
    
    panelOctree oct;
    oct.addData(panels);
    
    for (int i=0; i<panels.size(); i++)
    {
        panels[i]->setNeighbors(&oct,false);
    }
    
    TEST_ASSERT_MSG(panels[0]->getNeighbors().size() == 1, "Wrong number of primary neighbors")
    TEST_ASSERT_MSG(panels[1]->getNeighbors().size() == 2, "Reciprocal addition of neighbor failed")
    TEST_ASSERT_MSG(panels[2]->getNeighbors().size() == 2, "False neighbor added to panel")
    TEST_ASSERT_MSG(panels[3]->getNeighbors().size() == 1, "False neighbor added to panel")
    
    
    
    for (int i=0; i<4; i++)
    {
        delete panels[i];
    }
}

