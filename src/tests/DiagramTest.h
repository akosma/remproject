/*!  
 * \file DiagramTest.h
 * 
 * Contains the interface of the tests::DiagramTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      2008-03-16
 */

#ifndef DIAGRAMTEST_H_
#define DIAGRAMTEST_H_

#include <cppunit/extensions/HelperMacros.h>

/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    /*!
     * \class DiagramTest "$URL$"
     *
     *  
     */
    class DiagramTest : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(tests::DiagramTest);
        CPPUNIT_TEST(testWhatever);
        CPPUNIT_TEST_SUITE_END();

    public:

        /*!
         * DiagramTest constructor.
         */
        DiagramTest();

        /*!
         * DiagramTest virtual destructor.
         */
        virtual ~DiagramTest();

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
        void testWhatever();
    };
}

CPPUNIT_TEST_SUITE_REGISTRATION(tests::DiagramTest);

#endif /* DIAGRAMTEST_H_ */
