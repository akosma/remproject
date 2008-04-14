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

/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    /*!
     * \class ActiveRecordTest
     *
     *  
     */
    class ActiveRecordTest : public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(tests::ActiveRecordTest);
        CPPUNIT_TEST(testSaveIndividualInstance);
        CPPUNIT_TEST(testRetrieveAllInstances);
        CPPUNIT_TEST(testRetrieveOneInstance);
        CPPUNIT_TEST(testSearchingForInstancesNotExistingInDatabaseReturnsNull);
        CPPUNIT_TEST_SUITE_END();

    public:

        /*!
         *  ActiveRecordTest constructor.
         */
        ActiveRecordTest();

        /*!
         *  ActiveRecordTest virtual destructor.
         */
        virtual ~ActiveRecordTest();

        /*!
         * Called by CppUnit before each test.
         */
        void setUp();

        /*!
         * Called by CppUnit after each test.
         */
        void tearDown();

        /*!
         * Tests something.
         */
        void testSaveIndividualInstance();
        
        void testRetrieveAllInstances();

        void testRetrieveOneInstance();
        
        void testSearchingForInstancesNotExistingInDatabaseReturnsNull();

    };
}

CPPUNIT_TEST_SUITE_REGISTRATION(tests::ActiveRecordTest);

#endif /* ACTIVERECORDTEST_H_ */
