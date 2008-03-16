/*!  
 * \file ProjectTest.h
 * 
 * Contains the interface of the tests::ProjectTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      2008-03-16
 */

#ifndef PROJECTTEST_H_
#define PROJECTTEST_H_

#include <cppunit/extensions/HelperMacros.h>

/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    /*!
     * \class ProjectTest "$URL$"
     *
     *  
     */
    class ProjectTest : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(tests::ProjectTest);
        CPPUNIT_TEST(testProjectHasManyDiagrams);
        CPPUNIT_TEST_SUITE_END();

    public:

        /*!
         * ProjectTest constructor.
         */
        ProjectTest();

        /*!
         * ProjectTest virtual destructor.
         */
        virtual ~ProjectTest();

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
        void testProjectHasManyDiagrams();
    };
}

CPPUNIT_TEST_SUITE_REGISTRATION(tests::ProjectTest);

#endif /* PROJECTTEST_H_ */
