/*!
 * \file ControllerTest.h
 *
 * Contains the interface of the tests::ControllerTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      5/25/08
 */

#ifndef tests_ControllerTest
#define tests_ControllerTest

#include <cppunit/extensions/HelperMacros.h>

/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    /*!
     * \class ControllerTest
     *
     *  
     */
    class ControllerTest : public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(tests::ControllerTest);
        CPPUNIT_TEST(testControllerIsSingleton);
        CPPUNIT_TEST(testCanCreateNewProject);
        CPPUNIT_TEST(testCanSaveOpenAndCloseProject);
        CPPUNIT_TEST(testCanAddDiagram);
        CPPUNIT_TEST_SUITE_END();

    public:

        /*!
         *  ControllerTest constructor.
         */
        ControllerTest();

        /*!
         *  ControllerTest virtual destructor.
         */
        virtual ~ControllerTest();

        void testControllerIsSingleton();
        void testCanCreateNewProject();
        void testCanSaveOpenAndCloseProject();
        void testCanAddDiagram();
    };
}

CPPUNIT_TEST_SUITE_REGISTRATION(tests::ControllerTest);

#endif /* rem_ControllerTest */
