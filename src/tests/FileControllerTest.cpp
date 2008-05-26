/*
 * Rem - Requirements and Entity Modeler = UML + AOP + Open Source + Cross Platform
 * Copyright (C) 2008 Adrian Kosmaczewski - http://remproject.org/
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

//! Contains the implementation of the tests::FileControllerTest class.
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
//        controller.addDiagram(diagramClassName);
//        CPPUNIT_ASSERT(controller.hasCurrentDiagram());
        
        controller.saveProject();
    }
}
