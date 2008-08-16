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

//! Contains the interface of the tests::ProjectTest class.
/*!  
 * \file ProjectTest.h
 * 
 * Contains the interface of the tests::ProjectTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      2008-03-16
 */

#ifndef PROJECTTEST_H_
#define PROJECTTEST_H_

#include <cppunit/extensions/HelperMacros.h>

//! Contains the test classes of the application.
/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    //! Tests several features of the metamodel::Project class.
    /*!
     * \class ProjectTest
     *
     * Tests several features of the metamodel::Project class.
     */
    class ProjectTest : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(tests::ProjectTest);
        CPPUNIT_TEST(testProjectHasManyDiagrams);
        CPPUNIT_TEST(testCanRemoveAllDiagramsFromProject);
        CPPUNIT_TEST(testCanAddElementsUsingOperator);
        CPPUNIT_TEST(testCanRetrieveElementsUsingOperator);
        CPPUNIT_TEST_SUITE_END();

    public:

        //! Constructor.
        /*!
         * Constructor.
         */
        ProjectTest();

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~ProjectTest();

        //! Tests that a project can have one or many diagrams.
        /*!
         * Tests that a project can have one or many diagrams.
         */
        void testProjectHasManyDiagrams();

        //! Tests that all the diagrams can be removed at once.
        /*!
         * Tests that all the diagrams can be removed at once.
         */
        void testCanRemoveAllDiagramsFromProject();

        //! Tests that diagrams can be added using the [] operator.
        /*!
         * Tests that diagrams can be added using the [] operator.
         */
        void testCanAddElementsUsingOperator();
        
        //! Tests that diagrams can be retrieved using the [] operator.
        /*!
         * Tests that diagrams can be retrieved using the [] operator.
         */
        void testCanRetrieveElementsUsingOperator();
    };
}

CPPUNIT_TEST_SUITE_REGISTRATION(tests::ProjectTest);

#endif /* PROJECTTEST_H_ */
