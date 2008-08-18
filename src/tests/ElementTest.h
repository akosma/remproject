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

//! Contains the interface of the tests::ElementTest class.
/*!  
 * \file ElementTest.h
 * 
 * Contains the interface of the tests::ElementTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      2008-03-16
 */

#ifndef ELEMENTTEST_H_
#define ELEMENTTEST_H_

#include <cppunit/extensions/HelperMacros.h>

//! Contains the test classes of the application.
/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    //! Tests several features of the metamodel::Element class.
    /*!
     * \class ElementTest
     *
     * Tests several features of the metamodel::Element class.
     */
    class ElementTest : public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(tests::ElementTest);
        CPPUNIT_TEST(testElementHasManyMembers);
        CPPUNIT_TEST(testCanRemoveAllMembersFromElement);
        CPPUNIT_TEST(testCanAddMembersUsingOperator);
        CPPUNIT_TEST(testCanRetrieveMembersUsingOperator);
        CPPUNIT_TEST(testCanRetrieveMembersUsingIterator);
        CPPUNIT_TEST_SUITE_END();

    public:

        //! Constructor.
        /*!
         * Constructor.
         */
        ElementTest();

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~ElementTest();

        //! Tests that an Element instance can have many Member instances.
        /*!
         * Tests that an Element instance can have many Member instances.
         */
        void testElementHasManyMembers();
        
        //! Tests that a client can remove all the Member instances of an Element.
        /*!
         * Tests that a client can remove all the Member instances of an Element.
         */
        void testCanRemoveAllMembersFromElement();
        
        //! Tests that clients can add Member instances using the << operator.
        /*!
         * Tests that clients can add Member instances using the << operator.
         */
        void testCanAddMembersUsingOperator();
        
        //! Tests that clients can retrieve Member instances using the [] operator.
        /*!
         * Tests that clients can retrieve Member instances using the [] operator.
         */
        void testCanRetrieveMembersUsingOperator();
        
        //! Tests that members can be accessed using an iterator.
        /*!
         * Tests that members can be accessed using an iterator.
         */
        void testCanRetrieveMembersUsingIterator();
    };
}

CPPUNIT_TEST_SUITE_REGISTRATION(tests::ElementTest);

#endif /* ELEMENTTEST_H_ */
