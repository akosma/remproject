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

#ifndef SINGLETON_H_
#include "../utility/Singleton.h"
#endif

#ifndef PROJECT_H_
#include "../metamodel/Project.h"
#endif

#ifndef ELEMENT_H_
#include "../metamodel/Element.h"
#endif

#ifndef DIAGRAM_H_
#include "../metamodel/Diagram.h"
#endif

#ifndef SaveFile_H_
#include "../notifications/SaveFile.h"
#endif

using utility::Singleton;
using metamodel::Project;
using metamodel::Diagram;
using std::string;
using Poco::AutoPtr;
using notifications::SaveFile;

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
        void addDiagram(const string&);
        
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

    private:

        //! Private constructor.
        /*!
         * Private constructor.
         */
        FileController();

        //! Allow the Singleton template class to access the private constructor.
        friend FileController& Singleton<FileController>::get();

        void handleSaveFile(const AutoPtr<SaveFile>&);
        
    private:
        //! Instance of the Project class "controlled" by this FileController.
        Project* _project;
        
        //! Diagram where all operations are sent by default.
        Diagram* _currentDiagram;
        
        //! Counter used for the file names of new projects.
        int _counter;
    };
}

#endif /* FILECONTROLLER_H_ */
