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

#ifndef DIAGRAM_H_
#include "../metamodel/Diagram.h"
#endif

#ifndef ELEMENT_H_
#include "../metamodel/Element.h"
#endif

using namespace metamodel;

/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    /*!
     * DiagramTest Constructor.
     */
    DiagramTest::DiagramTest()
    {
    }
    
    /*!
     * DiagramTest Virtual destructor.
     */
    DiagramTest::~DiagramTest()
    {
    }

    /*!
     * Called by CppUnit before each test.
     */
    void DiagramTest::setUp()
    {
    }
    
    /*!
     * Called by CppUnit after each test.
     */
    void DiagramTest::tearDown()
    {
    }

    /*!
     * Tests something.
     */
    void DiagramTest::testDiagramCanHaveSeveralElements()
    {
        std::string actor1Name("actor1");
        std::string diagramName("diagramName");
        std::string className("actor");
        std::string diagramClassName("usecase");

        Diagram* diagram = new Diagram(diagramClassName);
        diagram->setName(diagramName);
        CPPUNIT_ASSERT_EQUAL(diagramName, diagram->getName());
        CPPUNIT_ASSERT(diagram->isEmpty());
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
}
