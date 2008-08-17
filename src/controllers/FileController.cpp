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

#ifndef PROJECT_H_
#include "../metamodel/Project.h"
#endif

#ifndef ELEMENT_H_
#include "../metamodel/Element.h"
#endif

#ifndef DIAGRAM_H_
#include "../metamodel/Diagram.h"
#endif

#include "../ui/PlatformDefinitions.h"
#include "FileController.h"

#include <sstream>
#include <string>
#include <iostream>

#include <Poco/NotificationCenter.h>

#ifndef SQLITEWRAPPER_H_
#include "../storage/SQLiteWrapper.h"
#endif

#ifndef FIGURE_H_
#include "../ui/Figure.h"
#endif

using storage::SQLiteWrapper;
using std::string;
using std::stringstream;
using metamodel::Project;
using metamodel::Diagram;
using metamodel::Element;
using Poco::NotificationCenter;
using Poco::NObserver;
using Poco::AutoPtr;
using notifications::NewDiagramAdded;
using notifications::NewFigureAdded;
using notifications::FigureMoved;
using ui::Figure;

namespace controllers
{
    FileController::FileController()
    : Singleton<FileController>()
    , _project(NULL)
    , _currentDiagram(NULL)
    , _counter(0)
    , _newDiagramObserver(new NObserver<FileController, NewDiagramAdded>(*this, &FileController::handleNewDiagramAdded))
    , _newFigureObserver(new NObserver<FileController, NewFigureAdded>(*this, &FileController::handleNewFigureAdded))
    , _movementObserver(new NObserver<FileController, FigureMoved>(*this, &FileController::handleFigureMoved))
    {
        NotificationCenter::defaultCenter().addObserver(*_newDiagramObserver);
        NotificationCenter::defaultCenter().addObserver(*_newFigureObserver);
        NotificationCenter::defaultCenter().addObserver(*_movementObserver);
    }

    FileController::~FileController()
    {
        NotificationCenter::defaultCenter().removeObserver(*_newDiagramObserver);
        NotificationCenter::defaultCenter().removeObserver(*_newFigureObserver);
        NotificationCenter::defaultCenter().removeObserver(*_movementObserver);
        deleteAndZero(_newDiagramObserver);
        deleteAndZero(_newFigureObserver);
        deleteAndZero(_movementObserver);
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
        return (_project != NULL);
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
    
    void FileController::addDiagram(const string& className, const string& uniqueId)
    {
        if (_project)
        {
            Diagram* diagram = new Diagram(className);
            diagram->setName(uniqueId);
            _project->addChild(diagram);
            _currentDiagram = diagram;
        }
    }
    
    void FileController::addFigure(const string& className, const string& uniqueId)
    {
        if (_currentDiagram)
        {
            Element* element = new Element(className);
            element->setName(uniqueId);
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
    
    Project* FileController::getProject() const
    {
        return _project;
    }

    void FileController::handleNewDiagramAdded(const AutoPtr<NewDiagramAdded>& notification)
    {
        const string& uniqueId = notification->getUniqueId();
        switch(notification->getDiagramType())
        {
            case NewDiagramAdded::UseCase:
                addDiagram("usecase", uniqueId);
                break;
            
            default:
                break;
        }
    }

    void FileController::handleNewFigureAdded(const AutoPtr<NewFigureAdded>& notification)
    {
        const string& uniqueId = notification->getUniqueId();
        switch(notification->getFigureType())
        {
            case NewFigureAdded::Actor:
                addFigure("actor", uniqueId);
                break;
                
            case NewFigureAdded::UseCase:
                addFigure("usecase", uniqueId);
                break;
                
            case NewFigureAdded::Arrow:
                addFigure("arrow", uniqueId);
                break;
            
            case NewFigureAdded::Line:
                addFigure("line", uniqueId);
                break;
            
            default:
                break;
        }
    }
    
    void FileController::handleFigureMoved(const AutoPtr<FigureMoved>& notification)
    {
        if (_currentDiagram)
        {
            Figure* figure = notification->getMovedFigure();
            const string& uniqueId = figure->getUniqueId();
            Element* elem = _currentDiagram->getChild(uniqueId);
            elem->set<int>("x", figure->getX());
            elem->set<int>("y", figure->getY());
            elem->set<int>("width", figure->getWidth());
            elem->set<int>("height", figure->getHeight());
        }
    }
}
