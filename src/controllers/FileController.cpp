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

#include <Poco/NotificationCenter.h>

#ifndef SQLITEWRAPPER_H_
#include "../storage/SQLiteWrapper.h"
#endif

#ifndef FIGURE_H_
#include "../ui/Figure.h"
#endif

#ifndef UMLDIAGRAM_H_
#include "../ui/UMLDiagram.h"
#endif

#ifndef LINEFIGURE_H_
#include "../ui/LineFigure.h"
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
using notifications::FigureChanged;
using notifications::NewProjectCreated;
using ui::Figure;
using ui::LineFigure;

namespace controllers
{
    FileController::FileController()
    : Singleton<FileController>()
    , _project(NULL)
    , _counter(0)
    , _currentDiagramName("")
    , _newDiagramObserver(new NObserver<FileController, NewDiagramAdded>(*this, &FileController::handleNewDiagramAdded))
    , _newFigureObserver(new NObserver<FileController, NewFigureAdded>(*this, &FileController::handleNewFigureAdded))
    , _newLineObserver(new NObserver<FileController, NewLineAdded>(*this, &FileController::handleNewLineAdded))
    , _movementObserver(new NObserver<FileController, FigureChanged>(*this, &FileController::handleFigureChanged))
    , _tabObserver(new NObserver<FileController, ProjectTabbedComponentChangedTab>(*this, &FileController::handleProjectTabbedComponentChangedTab))
    , _newProjectCreatedObserver(new NObserver<FileController, NewProjectCreated>(*this, &FileController::handleNewProjectCreated))
    , _gridObserver(new NObserver<FileController, DiagramToggleGrid>(*this, &FileController::handleDiagramToggleGrid))
    {
        NotificationCenter::defaultCenter().addObserver(*_newDiagramObserver);
        NotificationCenter::defaultCenter().addObserver(*_newFigureObserver);
        NotificationCenter::defaultCenter().addObserver(*_newLineObserver);
        NotificationCenter::defaultCenter().addObserver(*_movementObserver);
        NotificationCenter::defaultCenter().addObserver(*_tabObserver);
        NotificationCenter::defaultCenter().addObserver(*_newProjectCreatedObserver);
        NotificationCenter::defaultCenter().addObserver(*_gridObserver);
    }

    FileController::~FileController()
    {
        NotificationCenter::defaultCenter().removeObserver(*_newDiagramObserver);
        NotificationCenter::defaultCenter().removeObserver(*_newFigureObserver);
        NotificationCenter::defaultCenter().removeObserver(*_newLineObserver);
        NotificationCenter::defaultCenter().removeObserver(*_movementObserver);
        NotificationCenter::defaultCenter().removeObserver(*_tabObserver);
        NotificationCenter::defaultCenter().removeObserver(*_newProjectCreatedObserver);
        NotificationCenter::defaultCenter().removeObserver(*_gridObserver);
        deleteAndZero(_newDiagramObserver);
        deleteAndZero(_newFigureObserver);
        deleteAndZero(_newLineObserver);
        deleteAndZero(_movementObserver);
        deleteAndZero (_tabObserver);
        deleteAndZero(_newProjectCreatedObserver);
        deleteAndZero(_gridObserver);
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
        _project = NULL;
    }
    
    void FileController::addDiagram(const string& className, const string& uniqueId)
    {
        if (_project)
        {
            _currentDiagramName = uniqueId;
            Diagram* diagram = new Diagram(className);
            diagram->setName(uniqueId);
            _project->addChild(diagram);
            _project->setDirty();
        }
    }
    
    void FileController::addFigure(const string& className, const string& uniqueId)
    {
        Diagram* diagram = _project->getChild(_currentDiagramName);
        if (diagram)
        {
            Element* element = new Element(className);
            element->setName(uniqueId);
            element->set<int>("x", 10);
            element->set<int>("y", 10);
            diagram->addChild(element);
            _project->setDirty();
        }
    }
    
    void FileController::removeFigure(const string& uniqueId)
    {
        Diagram* diagram = _project->getChild(_currentDiagramName);
        if (diagram)
        {
            Element* element = diagram->getChild(uniqueId);
            if (element)
            {
                diagram->removeChild(uniqueId);
                _project->setDirty();
            }
        }
    }

    void FileController::addLine(const string& className, const string& uniqueId, const string& start, const string& end)
    {
        Diagram* diagram = _project->getChild(_currentDiagramName);
        if (diagram)
        {
            Element* element = new Element(className);
            element->setName(uniqueId);
            element->set<string>("start", start);
            element->set<string>("end", end);
            diagram->addChild(element);
            _project->setDirty();
        }
    }
    
    const bool FileController::hasCurrentProject() const
    {
        return (_project != NULL);
    }
    
    const bool FileController::hasCurrentDiagram() const
    {
        bool result = false;
        if (_project)
        {
            if (_currentDiagramName != "")
            {
                Diagram* diagram = _project->getChild(_currentDiagramName);
                result = (diagram != NULL);
            }
        }
        return result;
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
                break;
            
            case NewFigureAdded::Line:
                break;
            
            default:
                break;
        }
    }

    void FileController::handleNewLineAdded(const AutoPtr<NewLineAdded>& notification)
    {
        const string& uniqueId = notification->getUniqueId();
        LineFigure* line = notification->getLineFigure();
        const string start = line->getStartFigure()->getUniqueId();
        const string end = line->getEndFigure()->getUniqueId();
        switch(notification->getLineType())
        {
            case NewFigureAdded::Arrow:
            {
                addLine("arrow", uniqueId, start, end);
                break;
            }
            
            case NewFigureAdded::Line:
            {
                addLine("line", uniqueId, start, end);
                break;
            }
            
            default:
                break;
        }
    }

    void FileController::handleFigureChanged(const AutoPtr<FigureChanged>& notification)
    {
        Figure* figure = notification->getChangedFigure();
        const string& uniqueId = figure->getUniqueId();
        Diagram* diagram = _project->getChild(_currentDiagramName);
        if (diagram)
        {
            Element* elem = diagram->getChild(uniqueId);
            if (elem)
            {
                elem->setProperties(figure->getProperties());
                _project->setDirty();
            }
        }
    }

    void FileController::handleProjectTabbedComponentChangedTab(const AutoPtr<ProjectTabbedComponentChangedTab>& notification)
    {
        _currentDiagramName = notification->getNewCurrentDiagramName();
    }

    void FileController::handleNewProjectCreated(const AutoPtr<NewProjectCreated>& notification)
    {
        newProject();
        const string& uniqueId = notification->getUniqueId();
        _project->set<string>("name", uniqueId);
    }

    void FileController::handleDiagramToggleGrid(const AutoPtr<DiagramToggleGrid>& notification)
    {
        Diagram* diagram = _project->getChild(_currentDiagramName);
        if (diagram)
        {
            bool old = diagram->get<bool>("showgrid");
            diagram->set<bool>("showgrid", !old);
            _project->setDirty();
        }
    }
}
