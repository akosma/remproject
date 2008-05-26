/*
 * Rem - Requirements and Entity Modeler = UML + AOP + Open Source + Cross Platform
 * Copyright (C) 2008 Adrian Kosmaczewski - http://remproject.org/
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

//! Contains the implementation of the tests::DiagramTest class.
/*!  
 * \file DiagramTest.h
 * 
 * Contains the implementation of the tests::DiagramTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      2008-03-16
 */

#include "DiagramTest.h"

#ifndef PROJECT_H_
#include "../metamodel/Project.h"
#endif

#ifndef ELEMENT_H_
#include "../metamodel/Element.h"
#endif

#ifndef DIAGRAM_H_
#include "../metamodel/Diagram.h"
#endif

using metamodel::Diagram;
using metamodel::Element;

namespace tests
{
    DiagramTest::DiagramTest()
    {
    }

    DiagramTest::~DiagramTest()
    {
    }

    void DiagramTest::testDiagramCanHaveSeveralElements()
    {
        std::string actor1Name("actor1");
        std::string diagramName("diagramName");
        std::string className("actor");
        std::string diagramClassName("usecase");

        Diagram* diagram = new Diagram(diagramClassName);
        diagram->setName(diagramName);
        CPPUNIT_ASSERT_EQUAL(diagramName, diagram->getName());
        CPPUNIT_ASSERT(!diagram->hasChildren());
        CPPUNIT_ASSERT_EQUAL(0, diagram->getChildrenCount());

        Element* actor1 = new Element(className);
        actor1->setName(actor1Name);
        CPPUNIT_ASSERT_EQUAL(actor1Name, actor1->getName());

        diagram->addChild(actor1);
        CPPUNIT_ASSERT_EQUAL(1, diagram->getChildrenCount());

        Element* element = diagram->getChild(actor1Name);
        CPPUNIT_ASSERT_EQUAL((int)element, (int)actor1);
        
        delete diagram;
    }
    
    void DiagramTest::testCanAddElementsUsingOperator()
    {
        std::string diagramClassName("usecase");
        std::string diagramName("diagramName");
        Diagram* diagram = new Diagram(diagramClassName);
        diagram->setName(diagramName);

        std::string className("actor");
        std::string actor1Name("actor1");
        Element* actor1 = new Element(className);
        actor1->setName(actor1Name);

        // The "<<" operator requires the receiving object 
        // to be treated as a reference, and not as a pointer
        (*diagram) << actor1;
        CPPUNIT_ASSERT_EQUAL(1, diagram->getChildrenCount());

        Element* element = diagram->getChild(actor1Name);
        CPPUNIT_ASSERT_EQUAL((int)element, (int)actor1);
        
        delete diagram;
    }
}
