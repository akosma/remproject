/*!
 * \file FileControllerTest.cpp
 *
 * Contains the implementation of the tests::FileControllerTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      5/25/08
 */

#include "FileControllerTest.h"

#include <fstream>

#ifndef FILECONTROLLER_H_
#include "../controllers/FileController.h"
#endif

#ifndef SQLITEWRAPPER_H_
#include "../storage/SQLiteWrapper.h"
#endif

using controllers::FileController;
using storage::SQLiteWrapper;

/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    FileControllerTest::FileControllerTest()
    {
    }
    
    FileControllerTest::~FileControllerTest()
    {
    }

    void FileControllerTest::testFileControllerIsSingleton()
    {
        FileController& controller1 = FileController::get();
        FileController& controller2 = FileController::get();
        
        // Both references point to the same instance
        CPPUNIT_ASSERT_EQUAL((int)&controller1, (int)&controller2);
    }
    
    void FileControllerTest::testCanCreateNewProject()
    {
        FileController& controller = FileController::get();
        CPPUNIT_ASSERT(!controller.hasCurrentProject());
        
        controller.newProject();
        CPPUNIT_ASSERT(controller.hasCurrentProject());

        SQLiteWrapper& wrapper = SQLiteWrapper::get();
        const std::string filename1 = wrapper.getFileName();

        controller.closeProject();
        CPPUNIT_ASSERT(!controller.hasCurrentProject());

        controller.newProject();
        CPPUNIT_ASSERT(controller.hasCurrentProject());
        
        const std::string filename2 = wrapper.getFileName();
        
        CPPUNIT_ASSERT(filename1 != filename2);
    }

    void FileControllerTest::testCanSaveOpenAndCloseProject()
    {
        FileController& controller = FileController::get();
        controller.newProject();
        
        const std::string chosenFileName("whatever.rem");
        controller.saveProjectAs(chosenFileName);
        
        SQLiteWrapper& wrapper = SQLiteWrapper::get();
        const std::string& filename = wrapper.getFileName();
        
        CPPUNIT_ASSERT_EQUAL(filename, chosenFileName);

        // Check that the file exists
        std::fstream fin;
        fin.open(filename.c_str(), std::fstream::in);
        CPPUNIT_ASSERT(fin.is_open());
        fin.close();

        controller.closeProject();
        CPPUNIT_ASSERT(!controller.hasCurrentProject());

        controller.openProject(filename);
        CPPUNIT_ASSERT(controller.hasCurrentProject());
    }
    
    void FileControllerTest::testCanAddDiagram()
    {
        FileController& controller = FileController::get();
        controller.newProject();
        controller.saveProject();
        
        CPPUNIT_ASSERT(!controller.hasCurrentDiagram());
        const std::string diagramClassName("usecase");
        controller.addDiagram(diagramClassName);
        CPPUNIT_ASSERT(controller.hasCurrentDiagram());
        
        controller.saveProject();
    }
}
