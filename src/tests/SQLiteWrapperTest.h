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
         * Called by CppUnit before each test.
         */
        void setUp();

        /*!
         * Called by CppUnit after each test.
         */
        void tearDown();

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
