/*!
 * \file ControllerTest.cpp
 *
 * Contains the implementation of the tests::ControllerTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      5/25/08
 */

#include "ControllerTest.h"

#include <fstream>

#ifndef CONTROLLER_H_
#include "../controller/Controller.h"
#endif

#ifndef SQLITEWRAPPER_H_
#include "../storage/SQLiteWrapper.h"
#endif

using controller::Controller;
using storage::SQLiteWrapper;

/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    ControllerTest::ControllerTest()
    {
    }
    
    ControllerTest::~ControllerTest()
    {
    }

    void ControllerTest::testControllerIsSingleton()
    {
        Controller& controller1 = Controller::get();
        Controller& controller2 = Controller::get();
        
        // Both references point to the same instance
        CPPUNIT_ASSERT_EQUAL((int)&controller1, (int)&controller2);
    }
    
    void ControllerTest::testCanCreateNewProject()
    {
        Controller& controller = Controller::get();
        CPPUNIT_ASSERT(!controller.hasCurrentProject());
        
        controller.newProject();
        CPPUNIT_ASSERT(controller.hasCurrentProject());

        const std::string filename1 = SQLiteWrapper::getFileName();

        controller.closeProject();
        CPPUNIT_ASSERT(!controller.hasCurrentProject());

        controller.newProject();
        CPPUNIT_ASSERT(controller.hasCurrentProject());
        
        const std::string filename2 = SQLiteWrapper::getFileName();
        
        CPPUNIT_ASSERT(filename1 != filename2);
    }

    void ControllerTest::testCanSaveOpenAndCloseProject()
    {
        Controller& controller = Controller::get();
        controller.newProject();
        
        const std::string chosenFileName("whatever.rem");
        controller.saveProjectAs(chosenFileName);
        
        const std::string& filename = SQLiteWrapper::getFileName();
        
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
    
    void ControllerTest::testCanAddDiagram()
    {
        Controller& controller = Controller::get();
        controller.newProject();
        controller.saveProject();
        
        CPPUNIT_ASSERT(!controller.hasCurrentDiagram());
        const std::string diagramClassName("usecase");
        controller.addDiagram(diagramClassName);
        CPPUNIT_ASSERT(controller.hasCurrentDiagram());
    }
}
