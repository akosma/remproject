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

//! Contains the interface of the controllers::FileController class.
/*!
 * \file FileController.h
 *
 * Contains the interface of the controllers::FileController class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      5/25/08
 */

#ifndef FILECONTROLLER_H_
#define FILECONTROLLER_H_

#include <Poco/AutoPtr.h>
#include <Poco/NObserver.h>

#ifndef SINGLETON_H_
#include "../utility/Singleton.h"
#endif

#ifndef NEWDIAGRAMADDED_H_
#include "../notifications/NewDiagramAdded.h"
#endif

#ifndef NEWFIGUREADDED_H_
#include "../notifications/NewFigureAdded.h"
#endif

#ifndef FIGURECHANGED_H_
#include "../notifications/FigureChanged.h"
#endif

#ifndef PROJECTTABBEDCOMPONENTCHANGEDTAB_H_
#include "../notifications/ProjectTabbedComponentChangedTab.h"
#endif

#ifndef NEWPROJECTCREATED_H_
#include "../notifications/NewProjectCreated.h"
#endif

#ifndef NEWLINEADDED_H_
#include "../notifications/NewLineAdded.h"
#endif

#ifndef DIAGRAMTOGGLEGRID_H_
#include "../notifications/DiagramToggleGrid.h"
#endif

using utility::Singleton;
using std::string;
using Poco::AutoPtr;
using Poco::NObserver;
using notifications::NewDiagramAdded;
using notifications::NewFigureAdded;
using notifications::FigureChanged;
using notifications::ProjectTabbedComponentChangedTab;
using notifications::NewProjectCreated;
using notifications::NewLineAdded;
using notifications::DiagramToggleGrid;

// Forward declaration
namespace metamodel
{
    class Project;
    class Diagram;
    class Element;
}

using metamodel::Project;
using metamodel::Diagram;
using metamodel::Element;

//! Contains the controller classes of the application.
/*!
 * \namespace controller
 * Contains the controller classes of the application, following
 * the naming conventions of the MVC design pattern.
 */
namespace controllers
{
    //! Controller grouping file-based operations.
    /*!
     * \class FileController
     *
     * Controller grouping file-based operations.
     * Provides an isolation interface between the classes in the 
     * "ui" or "commandline" namespaces (the "View"), and those 
     * in the "metamodel" namespace (the "Model"), following the MVC
     * design pattern.
     */
    class FileController : public Singleton<FileController>
    {
    public:

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~FileController();
        
        //! Loads the project whose path is passed as parameter.
        /*!
         * Loads the project whose path is passed as parameter.
         * 
         * \param path The path of the project file to load.
         * 
         * \return A boolean value; "true" if the file could be opened,
         * "false" otherwise.
         */
        const bool openProject(const string&);
        
        //! Creates a new project in memory.
        /*!
         * Creates a new project in memory. Use the "saveProject(const string&)"
         * method to save it on disk.
         */
        void newProject();
        
        //! Saves the current project in disk.
        /*!
         * Saves the current project in disk.
         */
        void saveProject();

        //! Saves the current project in disk with the specified name.
        /*!
         * Saves the current project in disk with the specified name.
         * 
         * \param path The path of the new project file.
         */
        void saveProjectAs(const string&);

        //! Closes the current project.
        /*!
         * Closes the current project.
         */
        void closeProject();

        //! Adds a diagram to the current project.
        /*!
         * Adds a diagram to the current project and sets it as current.
         * 
         * \param className The type of diagram to create (use-case, class, etc).
         */
        void addDiagram(const string&, const string&);

        //! Adds a figure to the current diagram.
        /*!
         * Adds a figure to the current diagram.
         * 
         * \param className The type of figure to create (actor, class, etc).
         * \param uniqueId The unique ID of the figure, as generated by the notification.
         */
        void addFigure(const string&, const string&);
        
        //! Removes a figure from the current diagram.
        /*!
         * Removes a figure from the current diagram.
         * 
         * \param uniqueId The "name" field of the figure.
         */
        void removeFigure(const string&);
        
        //! Adds a line or an arrow to the current diagram.
        /*!
         * Adds a line or an arrow to the current diagram.
         * 
         * \param className The type of figure to create (line, arrow, etc).
         * \param uniqueId The unique ID of the figure, as generated by the notification.
         * \param start The name of the figure at the start of the line.
         * \param end The name of the figure at the end of the line.
         */
        void addLine(const string&, const string&, const string&, const string&);
        
        //! States whether the controller has a current project.
        /*!
         * States whether the controller has a current project.
         * 
         * \return A boolean value.
         */
        const bool hasCurrentProject() const;

        //! States whether the controller has a current diagram.
        /*!
         * States whether the controller has a current diagram.
         * 
         * \return A boolean value.
         */
        const bool hasCurrentDiagram() const;

        //! States whether the controller has a new project.
        /*!
         * States whether the controller has a new project.
         * 
         * \return A boolean value.
         */
        const bool isProjectNew() const;
        
        //! States whether the controller has a 'dirty' (not saved) project.
        /*!
         * States whether the controller has a 'dirty' (not saved) project.
         * 
         * \return A boolean value.
         */
        const bool isProjectDirty() const;
        
        //! Returns a pointer to the current project
        /*!
         * Returns a pointer to the current project
         *
         * \return A pointer to a Project instance.
         */
        Project* getProject() const;

    private:

        //! Private constructor.
        FileController();

        //! Allow the Singleton template class to access the private constructor.
        friend FileController& Singleton<FileController>::get();
        
    private:
        //! Handles notifications of type notification::NewDiagramAdded
        void handleNewDiagramAdded(const AutoPtr<NewDiagramAdded>&);

        //! Handles notifications of type notification::NewFigureAdded
        void handleNewFigureAdded(const AutoPtr<NewFigureAdded>&);
        
        //! Handles notifications of type notification::NewLineAdded
        void handleNewLineAdded(const AutoPtr<NewLineAdded>&);
        
        //! Handles notifications of type notification::FigureChanged
        void handleFigureChanged(const AutoPtr<FigureChanged>&);

        //! Handles notifications of type notification::ProjectTabbedComponentChangedTab
        void handleProjectTabbedComponentChangedTab(const AutoPtr<ProjectTabbedComponentChangedTab>&);

        //! Handles notifications of type notification::NewProjectCreated
        void handleNewProjectCreated(const AutoPtr<NewProjectCreated>&);

        //! Handles notifications of type notification::DiagramToggleGrid
        void handleDiagramToggleGrid(const AutoPtr<DiagramToggleGrid>&);

    private:
        //! Instance of the Project class "controlled" by this FileController.
        Project* _project;
        
        //! Counter used for the file names of new projects.
        int _counter;
        
        //! Stores the name of the current diagram.
        string _currentDiagramName;

        //! Observer for NewDiagramAdded notifications.
        NObserver<FileController, NewDiagramAdded>* _newDiagramObserver;
        
        //! Observer for NewFigureAdded notifications.
        NObserver<FileController, NewFigureAdded>* _newFigureObserver;

        //! Observer for NewLineAdded notifications.
        NObserver<FileController, NewLineAdded>* _newLineObserver;
        
        //! Observer for FigureChanged notifications.
        NObserver<FileController, FigureChanged>* _movementObserver;

        //! Observer for ProjectTabbedComponentChangedTab notifications.
        NObserver<FileController, ProjectTabbedComponentChangedTab>* _tabObserver;

        //! Observer for NewProjectCreated notifications.
        NObserver<FileController, NewProjectCreated>* _newProjectCreatedObserver;

        //! Observer for DiagramToggleGrid notifications.
        NObserver<FileController, DiagramToggleGrid>* _gridObserver;
    };
}

#endif /* FILECONTROLLER_H_ */
