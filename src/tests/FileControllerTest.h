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

//! Contains the interface of the tests::FileControllerTest class.
/*!
 * \file FileControllerTest.h
 *
 * Contains the interface of the tests::FileControllerTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      5/25/08
 */

#ifndef FILECONTROLLERTEST_H_
#define FILECONTROLLERTEST_H_

#include <cppunit/extensions/HelperMacros.h>

//! Contains the test classes of the application.
/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    //! Tests the functionality of the controllers::FileController class.
    /*!
     * \class FileControllerTest
     *
     * This class tests the functionality of the controllers::FileController class.
     */
    class FileControllerTest : public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(tests::FileControllerTest);
        CPPUNIT_TEST(testFileControllerIsSingleton);
        CPPUNIT_TEST(testCanCreateNewProject);
        CPPUNIT_TEST(testCanSaveOpenAndCloseProject);
        CPPUNIT_TEST(testCanAddDiagram);
        CPPUNIT_TEST_SUITE_END();

    public:

        //! Constructor.
        /*!
         * Constructor.
         */
        FileControllerTest();

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~FileControllerTest();

        //! Tests that the class is a singleton.
        /*! 
         * Tests that the class is a singleton.
         */
        void testFileControllerIsSingleton();
        
        //! Tests that the class can be used to create a new project.
        /*!
         * Tests that the class can be used to create a new project.
         */
        void testCanCreateNewProject();
        
        //! Tests that the class can save, open and close projects.
        /*!
         * Tests that the class can save, open and close projects.
         */
        void testCanSaveOpenAndCloseProject();
        
        //! Tests that the class can add new diagrams to a project.
        /*!
         * Tests that the class can add new diagrams to a project.
         */
        void testCanAddDiagram();
    };
}

CPPUNIT_TEST_SUITE_REGISTRATION(tests::FileControllerTest);

#endif /* FILECONTROLLERTEST_H_ */
