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

//! Contains the interface of the tests::DiagramTest class.
/*!  
 * \file DiagramTest.h
 * 
 * Contains the interface of the tests::DiagramTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      2008-03-16
 */

#ifndef DIAGRAMTEST_H_
#define DIAGRAMTEST_H_

#include <cppunit/extensions/HelperMacros.h>

//! Contains the test classes of the application.
/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    //! Tests several features of the metamodel::Diagram class.
    /*!
     * \class DiagramTest
     *
     * Tests several features of the metamodel::Diagram class.
     */
    class DiagramTest : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(tests::DiagramTest);
        CPPUNIT_TEST(testDiagramCanHaveSeveralElements);
        CPPUNIT_TEST(testCanAddElementsUsingOperator);
        CPPUNIT_TEST(testCanGetIteratorForChildren);
        CPPUNIT_TEST_SUITE_END();

    public:

        //! Constructor.
        /*!
         * Constructor.
         */
        DiagramTest();

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~DiagramTest();

        //! Tests that a diagram can have one or many elements.
        /*!
         * Tests that a diagram can have one or many elements.
         */
        void testDiagramCanHaveSeveralElements();

        //! Tests that an element can be added using the << operator.
        /*!
         * Tests that an element can be added using the << operator.
         */
        void testCanAddElementsUsingOperator();
        
        //! Tests that elements can be accessed using an iterator.
        /*!
         * Tests that elements can be accessed using an iterator.
         */
        void testCanGetIteratorForChildren();
    };
}

CPPUNIT_TEST_SUITE_REGISTRATION(tests::DiagramTest);

#endif /* DIAGRAMTEST_H_ */
