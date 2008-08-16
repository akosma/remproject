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

//! Contains the interface of the tests::AnyPropertyMapTest class.
/*!
 * \file ActiveRecordTest.h
 *
 * Contains the interface of the tests::ActiveRecordTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/6/08
 */

#ifndef ACTIVERECORDTEST_H_
#define ACTIVERECORDTEST_H_

#include <cppunit/extensions/HelperMacros.h>

//! Contains the test classes of the application.
/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    //! Tests several features of the ActiveRecord family of template classes.
    /*!
     * \class ActiveRecordTest
     *
     * Tests several features of the ActiveRecord family of template classes.
     */
    class ActiveRecordTest : public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(tests::ActiveRecordTest);
        CPPUNIT_TEST(testCanSaveIndividualInstance);
        CPPUNIT_TEST(testCanRetrieveAllInstances);
        CPPUNIT_TEST(testCanRetrieveOneInstance);
        CPPUNIT_TEST(testCanUseConditionsToFindAnItem);
        CPPUNIT_TEST(testSearchingForInstancesNotExistingInDatabaseReturnsNull);
        CPPUNIT_TEST(testDestroyingObjectsRemovesThemFromTheDatabase);
        CPPUNIT_TEST(testCanUseCopyConstructorSafely);
        CPPUNIT_TEST(testCanUseAssignmentOperatorSafely);
        CPPUNIT_TEST(testObjectCanSaveItsChildren);
        CPPUNIT_TEST(testSavedObjectsHaveCreationAndUpdateTime);
        CPPUNIT_TEST(testSettingAChildDirtySetsTheParentDirtyToo);
        CPPUNIT_TEST(testObjectsCannotBeAttackedWithSqlInjection);
        CPPUNIT_TEST(testUsesLazyLoadingToRetrieveChildren);
        CPPUNIT_TEST_SUITE_END();

    public:

        /*!
         * Constructor.
         */
        ActiveRecordTest();

        /*!
         * Virtual destructor.
         */
        virtual ~ActiveRecordTest();

        //! Tests that individual instances can be saved.
        /*!
         * Tests that individual instances can be saved.
         */
        void testCanSaveIndividualInstance();
        
        //! Tests that a "SELECT *" retrieves all the instances of a type.
        /*!
         * Tests that a "SELECT *" retrieves all the instances of a type.
         */
        void testCanRetrieveAllInstances();

        //! Tests that a "SELECT * WHERE id" retrieves one instance of a type.
        /*!
         * Tests that a "SELECT * WHERE id" retrieves one instance of a type.
         */
        void testCanRetrieveOneInstance();

        //! Tests that a "SELECT * WHERE" retrieves one instance of a type.
        /*!
         * Tests that a "SELECT * WHERE" retrieves one instance of a type.
         */
        void testCanUseConditionsToFindAnItem();
        
        //! Tests that searching for a non-existent instance returns NULL
        /*!
         * Tests that searching for a non-existent instance returns NULL
         */
        void testSearchingForInstancesNotExistingInDatabaseReturnsNull();
        
        //! Tests that using the destroy() methods removes an instance from the database.
        /*! 
         * Tests that using the destroy() methods removes an instance from the database.
         */
        void testDestroyingObjectsRemovesThemFromTheDatabase();
        
        //! Tests that ActiveRecord instances can be copied safely.
        /*!
         * Tests that ActiveRecord instances can be copied safely.
         */        
        void testCanUseCopyConstructorSafely();

        //! Tests that ActiveRecord instances can be assigned safely.
        /*!
         * Tests that ActiveRecord instances can be assigned safely.
         */
        void testCanUseAssignmentOperatorSafely();

        //! Tests that objects using the HasMany interface can save their children.
        /*!
         * Tests that objects using the HasMany interface can save their children.
         */
        void testObjectCanSaveItsChildren();
        
        //! Tests that objects saved have creation and modification times.
        /*!
         * Tests that objects saved have creation and modification times.
         */
        void testSavedObjectsHaveCreationAndUpdateTime();
        
        //! Tests that objects implementing the BelongsTo interface can set their parents as 'dirty'.
        /*!
         * Tests that objects implementing the BelongsTo interface can set their parents as 'dirty'.
         */
        void testSettingAChildDirtySetsTheParentDirtyToo();
        
        //! Tests that SQLite files cannot be corrupted using SQL injection attacks.
        /*!
         * Tests that SQLite files cannot be corrupted using SQL injection attacks.
         */
        void testObjectsCannotBeAttackedWithSqlInjection();
        
        //! Tests that children are loaded using 'lazy loading'
        /*!
         * Tests that children are loaded using 'lazy loading'
         */
        void testUsesLazyLoadingToRetrieveChildren();
    };
}

CPPUNIT_TEST_SUITE_REGISTRATION(tests::ActiveRecordTest);

#endif /* ACTIVERECORDTEST_H_ */
