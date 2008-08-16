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

//! Contains the implementation of the controllers::FileController class.
/*!
 * \file FileController.cpp
 *
 * Contains the implementation of the controllers::FileController class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      5/25/08
 */

#include "FileController.h"

#include <sstream>
#include <string>
#include <iostream>

#if defined(__APPLE__) && defined(__MACH__)
// The Mac OS X compiler requires this line, because "nil" is a reserved
// word in the Objective-C language, and without it this file won't compile.
// (The Poco/UUID.h file has definitions of a "nil()" method!)
#undef nil
#endif

#if defined(_WIN32)
#include <cstdio>
#else
#include <Poco/UUIDGenerator.h>
#include <Poco/UUID.h>
using Poco::UUIDGenerator;
using Poco::UUID;
#endif

#include <Poco/NotificationCenter.h>
#include <Poco/NObserver.h>

#ifndef SQLITEWRAPPER_H_
#include "../storage/SQLiteWrapper.h"
#endif

using storage::SQLiteWrapper;
using std::string;
using std::stringstream;
using Poco::NotificationCenter;
using Poco::NObserver;
using Poco::AutoPtr;
using notifications::NewDiagramAdded;

namespace controllers
{
    FileController::FileController()
    : Singleton<FileController>()
    , _project(NULL)
    , _currentDiagram(NULL)
    , _counter(0)
    {
        NObserver<FileController, NewDiagramAdded> newDiagramObserver(*this, &FileController::handleNewDiagramAdded);
        NotificationCenter::defaultCenter().addObserver(newDiagramObserver);

        NObserver<FileController, NewFigureAdded> newFigureObserver(*this, &FileController::handleNewFigureAdded);
        NotificationCenter::defaultCenter().addObserver(newFigureObserver);
    }

    FileController::~FileController()
    {
        closeProject();
    }
    
    const bool FileController::openProject(const string& path)
    {
        if (_project)
        {
            closeProject();
        }
        SQLiteWrapper& wrapper = SQLiteWrapper::get();
        wrapper.setFileName(path);
        const bool ok = wrapper.open();
        if (ok)
        {
            _project = Project::findById(0);
        }
        return ok;
    }
    
    void FileController::newProject()
    {
        if (_project)
        {
            closeProject();
        }
        _counter++;
        stringstream path;
        path << "untitled ";
        path << _counter;
        path << ".rem";
        SQLiteWrapper::get().setFileName(path.str());
        delete _project;
        _project = new Project();
    }
    
    void FileController::saveProject()
    {
        if (_project)
        {
            _project->save();
        }
    }
    
    void FileController::saveProjectAs(const string& path)
    {
        if (_project && _project->isNew())
        {
            SQLiteWrapper::get().setFileName(path);
            saveProject();
        }
    }
    
    void FileController::closeProject()
    {
        SQLiteWrapper& wrapper = SQLiteWrapper::get();
        wrapper.close();
        delete _project;
        delete _currentDiagram;
        _project = NULL;
        _currentDiagram = NULL;
    }
    
    void FileController::addDiagram(const string& className)
    {
        if (_project)
        {
            Diagram* diagram = new Diagram(className);
#if defined(_WIN32)
            string name(tmpnam(NULL));
#else
            UUIDGenerator& generator = UUIDGenerator::defaultGenerator();
            UUID uuid = generator.createRandom();
            string name = uuid.toString();
#endif
            diagram->setName(name);
            _project->addChild(diagram);
            _currentDiagram = diagram;
        }
    }
    
    void FileController::addFigure(const string& className)
    {
        if (_currentDiagram)
        {
            Element* element = new Element(className);
#if defined(_WIN32)
            string name(tmpnam(NULL));
#else
            UUIDGenerator& generator = UUIDGenerator::defaultGenerator();
            UUID uuid = generator.createRandom();
            string name = uuid.toString();
#endif
            element->setName(name);
            element->set<int>("x", 10);
            element->set<int>("y", 10);
            _currentDiagram->addChild(element);
        }
    }
    
    const bool FileController::hasCurrentProject() const
    {
        return (_project != NULL);
    }

    const bool FileController::hasCurrentDiagram() const
    {
        return (_currentDiagram != NULL);
    }
    
    const bool FileController::isProjectNew() const
    {
        if (_project)
        {
            return _project->isNew();
        }
        return true;
    }
    
    const bool FileController::isProjectDirty() const
    {
        if (_project)
        {
            return _project->isDirty();
        }
        return false;
    }

    void FileController::handleNewDiagramAdded(const AutoPtr<NewDiagramAdded>& notification)
    {
        switch(notification->getDiagramType())
        {
            case NewDiagramAdded::UseCase:
                addDiagram("usecase");
                break;
            
            default:
                break;
        }
    }

    void FileController::handleNewFigureAdded(const AutoPtr<NewFigureAdded>& notification)
    {
        switch(notification->getFigureType())
        {
            case NewFigureAdded::Actor:
                addFigure("actor");
                break;
                
            case NewFigureAdded::UseCase:
                addFigure("usecase");
                break;
                
            case NewFigureAdded::Arrow:
                addFigure("arrow");
                break;
            
            default:
                break;
        }
    }
}
