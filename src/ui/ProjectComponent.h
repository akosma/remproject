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

//! Contains the interface of the ui::ProjectComponent class.
/*!
 * \file ProjectComponent.h
 *
 * Contains the interface of the ui::ProjectComponent class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/21/08
 */

#include <Poco/AutoPtr.h>
#include <Poco/NObserver.h>

#include "PlatformDefinitions.h"

#ifndef PROJECTCOMPONENT_H_
#define PROJECTCOMPONENT_H_

#ifndef NEWDIAGRAMADDED_H_
#include "../notifications/NewDiagramAdded.h"
#endif

#ifndef PROJECTFILEOPENED_H_
#include "../notifications/ProjectFileOpened.h"
#endif

using Poco::AutoPtr;
using Poco::NObserver;
using notifications::NewDiagramAdded;
using notifications::ProjectFileOpened;

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    class ProjectTabbedComponent;
    class UseCaseDiagram;

    //! Core UI element of the application window.
    /*!
     * \class ProjectComponent
     *
     * This class is the core UI element inside the application window
     * holding the whole set of visible elements. One instance of
     * this class is created by the Window class constructor, and
     * added as the "content component" of the window.
     */
    class ProjectComponent : public Component
    {
    public:

        //! Constructor.
        /*!
         * Constructor.
         */
        ProjectComponent();

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~ProjectComponent();
        
        //! Called when the window is resized.
        /*!
         * Called when the window is resized. In turn, this
         * resizes the tabbed component inside.
         */
        void resized();
        
        //! Adds a new Use Case diagram to the project.
        /*!
         * Adds a new Use Case diagram to the project, and returns
         * a pointer to this new component.
         * 
         * \return A pointer to the UseCaseDiagram instance created.
         */
        UseCaseDiagram* addUseCaseDiagram();
    
    private:
        //! Handles the NewDiagramAdded notification.
        /*!
         * Handles the NewDiagramAdded notification.
         * 
         * \param notification The notification passed by the Poco::NotificationCenter.
         */
        void handleNewDiagramAdded(const AutoPtr<NewDiagramAdded>&);
        
        //! Handles the ProjectFileOpened notification.
        /*!
         * Handles the ProjectFileOpened notification.
         *
         * \param notification The notification passed by the Poco::NotificationCenter.
         */
        void handleProjectFileOpened(const AutoPtr<ProjectFileOpened>&);
    
    private:
        //! A tabbed component holding one tab per diagram.
        ProjectTabbedComponent* _tabs;
        
        NObserver<ProjectComponent, NewDiagramAdded>* _newDiagramObserver;
        NObserver<ProjectComponent, ProjectFileOpened>* _projectOpenedObserver;
    };
}

#endif /* PROJECTCOMPONENT_H_ */
