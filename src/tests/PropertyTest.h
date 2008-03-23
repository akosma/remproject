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
         void testCanCreatePropertiesOfDifferentTypes();
         void testDefaultPropertiesAcceptAnyValue();

    };
}

CPPUNIT_TEST_SUITE_REGISTRATION(tests::PropertyTest);

#endif /* PROPERTYTEST_H_ */
