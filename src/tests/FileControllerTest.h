/*!
 * \file FileControllerTest.h
 *
 * Contains the interface of the tests::FileControllerTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      5/25/08
 */

#ifndef FILECONTROLLERTEST_H_
#define FILECONTROLLERTEST_H_

#include <cppunit/extensions/HelperMacros.h>

/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    /*!
     * \class FileControllerTest
     *
     *  
     */
    class FileControllerTest : public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(tests::FileControllerTest);
        CPPUNIT_TEST(testFileControllerIsSingleton);
        CPPUNIT_TEST(testCanCreateNewProject);
        CPPUNIT_TEST(testCanSaveOpenAndCloseProject);
        CPPUNIT_TEST(testCanAddDiagram);
        CPPUNIT_TEST_SUITE_END();

    public:

        /*!
         *  FileControllerTest constructor.
         */
        FileControllerTest();

        /*!
         *  FileControllerTest virtual destructor.
         */
        virtual ~FileControllerTest();

        void testFileControllerIsSingleton();
        void testCanCreateNewProject();
        void testCanSaveOpenAndCloseProject();
        void testCanAddDiagram();
    };
}

CPPUNIT_TEST_SUITE_REGISTRATION(tests::FileControllerTest);

#endif /* FILECONTROLLERTEST_H_ */
