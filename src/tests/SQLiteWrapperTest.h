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

//! Contains the interface of the tests::SQLiteWrapperTest class.
/*!
 * \file SQLiteWrapperTest.h
 *
 * Contains the interface of the tests::SQLiteWrapperTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/23/08
 */

#ifndef SQLITEWRAPPERTEST_H_
#define SQLITEWRAPPERTEST_H_

#include <cppunit/extensions/HelperMacros.h>

//! Contains the test classes of the application.
/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    /*!
     * \class SQLiteWrapperTest
     * This class is adapted from the one used in the "BirthdayCard"
     * project by Adrian Kosmaczewski
     * http://kosmaczewski.net/projects/birthdaycard/
     */
    class SQLiteWrapperTest : public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(tests::SQLiteWrapperTest);
        CPPUNIT_TEST(testCreateDatabase);
        CPPUNIT_TEST(testCreateTable);
        CPPUNIT_TEST(testInsertion);
        CPPUNIT_TEST(testSelect);
        CPPUNIT_TEST_SUITE_END();

    public:

        /*!
         * Constructor.
         */
        SQLiteWrapperTest();

        /*!
         * Virtual destructor.
         */
        virtual ~SQLiteWrapperTest();

        /*!
         * Tests the automatic creation of a database file.
         */
        void testCreateDatabase();

        /*!
         * Tests the creation of tables.
         */
        void testCreateTable();

        /*!
         * Tests the insertion of values in the table created previously.
         */
        void testInsertion();

        /*!
         * Tests the reading of values stored previously.
         */
        void testSelect();

    private:
        const std::string _filename;
    };
}

CPPUNIT_TEST_SUITE_REGISTRATION(tests::SQLiteWrapperTest);

#endif /* SQLITEWRAPPERTEST_H_ */
