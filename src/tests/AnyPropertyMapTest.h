/*!
 * \file AnyPropertyMapTest.h
 *
 * Contains the interface of the tests::AnyPropertyMapTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/23/08
 */

#ifndef ANYPROPERTYMAPTEST_H_
#define ANYPROPERTYMAPTEST_H_

#include <cppunit/extensions/HelperMacros.h>

/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    /*!
     * \class AnyPropertyMapTest
     *
     *  
     */
    class AnyPropertyMapTest : public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(tests::AnyPropertyMapTest);
        CPPUNIT_TEST(testAddAndRetrieveProperties);
        CPPUNIT_TEST(testRetrievingInvalidPropertiesRaiseException);
        CPPUNIT_TEST(testCanUseCopyConstructorSafely);
        CPPUNIT_TEST(testCanUseAssignmentOperatorSafely);
        CPPUNIT_TEST_SUITE_END();

    public:

        /*!
         *  AnyPropertyMapTest constructor.
         */
        AnyPropertyMapTest();

        /*!
         *  AnyPropertyMapTest virtual destructor.
         */
        virtual ~AnyPropertyMapTest();

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
        void testAddAndRetrieveProperties();
        void testRetrievingInvalidPropertiesRaiseException();
        void testCanUseCopyConstructorSafely();
        void testCanUseAssignmentOperatorSafely();

    };
}

CPPUNIT_TEST_SUITE_REGISTRATION(tests::AnyPropertyMapTest);

#endif /* ANYPROPERTYMAPTEST_H_ */
