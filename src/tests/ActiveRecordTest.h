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

        void testCanSaveIndividualInstance();        
        void testCanRetrieveAllInstances();
        void testCanRetrieveOneInstance();
        void testCanUseConditionsToFindAnItem();
        void testSearchingForInstancesNotExistingInDatabaseReturnsNull();
        void testDestroyingObjectsRemovesThemFromTheDatabase();
        void testCanUseCopyConstructorSafely();
        void testCanUseAssignmentOperatorSafely();
        void testObjectCanSaveItsChildren();
        void testSavedObjectsHaveCreationAndUpdateTime();
    };
}

CPPUNIT_TEST_SUITE_REGISTRATION(tests::ActiveRecordTest);

#endif /* ACTIVERECORDTEST_H_ */
