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
 * \file ProjectTest.h
 * 
 * Contains the implementation of the tests::ProjectTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      2008-03-16
 */

#include "ProjectTest.h"

#ifndef PROJECT_H_
#include "../metamodel/Project.h"
#endif

#ifndef DIAGRAM_H_
#include "../metamodel/Diagram.h"
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
     * ProjectTest Constructor.
     */
    ProjectTest::ProjectTest()
    {
    }
    
    /*!
     * ProjectTest Virtual destructor.
     */
    ProjectTest::~ProjectTest()
    {
    }

    /*!
     * Called by CppUnit before each test.
     */
    void ProjectTest::setUp()
    {
    }
    
    /*!
     * Called by CppUnit after each test.
     */
    void ProjectTest::tearDown()
    {
    }

    /*!
     * Tests something.
     */
    void ProjectTest::testProjectHasManyDiagrams()
    {
        std::string first("first");
        std::string second("second");
        std::string diagramClassName("usecase");

        Project project;
        CPPUNIT_ASSERT(project.isEmpty());
        
        Diagram* firstDiagram = new Diagram(diagramClassName);
        firstDiagram->setName(first);
        
        project.addChild(firstDiagram);
        CPPUNIT_ASSERT_EQUAL(1, project.getChildrenCount());
        
        Diagram* pointer = project.getChild(first);
        CPPUNIT_ASSERT_EQUAL((int)firstDiagram, (int)pointer);
        CPPUNIT_ASSERT_EQUAL(first, pointer->getName());

        Diagram* secondDiagram = new Diagram(diagramClassName);
        secondDiagram->setName(second);
        project.addChild(secondDiagram);
        CPPUNIT_ASSERT_EQUAL(2, project.getChildrenCount());

        pointer = project.getChild(second);
        CPPUNIT_ASSERT_EQUAL((int)secondDiagram, (int)pointer);
        CPPUNIT_ASSERT_EQUAL(pointer->getName(), second);
        
        project.removeChild(first);
        CPPUNIT_ASSERT_EQUAL(1, project.getChildrenCount());

        project.removeChild(second);
        CPPUNIT_ASSERT_EQUAL(0, project.getChildrenCount());
        CPPUNIT_ASSERT(project.isEmpty());

        // Do not do the following:
        // delete firstDiagram;
        // delete secondDiagram;
        // This is because "project" owns the diagrams and will delete them
        // when the stack is cleared, at the end of this method.
    }
    
    void ProjectTest::testCanRemoveAllDiagramsFromProject()
    {
        std::string first("first");
        std::string second("second");
        std::string diagramClassName("usecase");

        Project project;
        CPPUNIT_ASSERT(project.isEmpty());
        
        Diagram* firstDiagram = new Diagram(diagramClassName);
        firstDiagram->setName(first);
        
        project.addChild(firstDiagram);
        CPPUNIT_ASSERT_EQUAL(1, project.getChildrenCount());
        
        Diagram* pointer = project.getChild(first);
        CPPUNIT_ASSERT_EQUAL((int)firstDiagram, (int)pointer);
        CPPUNIT_ASSERT_EQUAL(first, pointer->getName());

        Diagram* secondDiagram = new Diagram(diagramClassName);
        secondDiagram->setName(second);
        
        project.addChild(secondDiagram);
        CPPUNIT_ASSERT_EQUAL(2, project.getChildrenCount());

        project.removeAllChildren();
        CPPUNIT_ASSERT_EQUAL(0, project.getChildrenCount());

        // Do not do the following:
        // delete firstDiagram;
        // delete secondDiagram;
        // This is because "project" owns the diagrams and will delete them
        // when the stack is cleared, at the end of this method.
    }
}
