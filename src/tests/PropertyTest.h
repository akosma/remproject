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

//! Contains the interface of the tests::PropertyTest class.
/*!
 * \file PropertyTest.h
 *
 * Contains the interface of the tests::PropertyTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/23/08
 */

#ifndef PROPERTYTEST_H_
#define PROPERTYTEST_H_

#include <cppunit/extensions/HelperMacros.h>

/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    /*!
     * \class PropertyTest
     *
     *  
     */
    class PropertyTest : public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(tests::PropertyTest);
        CPPUNIT_TEST(testCanCreatePropertiesOfDifferentTypes);
        CPPUNIT_TEST(testDefaultPropertiesAcceptAnyValue);
        CPPUNIT_TEST(testCanUseCopyConstructorSafely);
        CPPUNIT_TEST(testCanUseAssignmentOperatorSafely);
        CPPUNIT_TEST_SUITE_END();

    public:

        /*!
         *  PropertyTest constructor.
         */
        PropertyTest();

        /*!
         *  PropertyTest virtual destructor.
         */
        virtual ~PropertyTest();

        void testCanCreatePropertiesOfDifferentTypes();
        void testDefaultPropertiesAcceptAnyValue();
        void testCanUseCopyConstructorSafely();
        void testCanUseAssignmentOperatorSafely();

    };
}

CPPUNIT_TEST_SUITE_REGISTRATION(tests::PropertyTest);

#endif /* PROPERTYTEST_H_ */
