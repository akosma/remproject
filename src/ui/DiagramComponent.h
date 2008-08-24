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

//! Contains the interface of the ui::DiagramComponent class.
/*!
 * \file DiagramComponent.h
 *
 * Contains the interface of the ui::DiagramComponent class.
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 *
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      21 Jun 2008 3:27:04 pm
 */

#include <string>
#include <Poco/AutoPtr.h>
#include <Poco/NObserver.h>

#include "PlatformDefinitions.h"

#ifndef DIAGRAMCOMPONENT_H_
#define DIAGRAMCOMPONENT_H_

#ifndef PROJECTTABBEDCOMPONENTCHANGEDTAB_H_
#include "../notifications/ProjectTabbedComponentChangedTab.h"
#endif

#ifndef ACTIVEWINDOWSTATUSCHANGED_H_
#include "../notifications/ActiveWindowStatusChanged.h"
#endif

#ifndef NEWFIGUREADDED_H_
#include "../notifications/NewFigureAdded.h"
#endif

using Poco::AutoPtr;
using Poco::NObserver;
using notifications::ProjectTabbedComponentChangedTab;
using notifications::ActiveWindowStatusChanged;
using notifications::NewFigureAdded;
using std::string;

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    // Forward declarations to avoid includes
    class DiagramToolbar;
    class UMLDiagram;

    //! Wrapper around a Viewport instance holding a UMLDiagram instance inside.
    /*!
     * \class DiagramComponent
     *
     * This class is basically a wrapper around a juce::Viewport instance
     * which provides scrolling capabilities to a ui::UMLDiagram instance.
     * Instances of this class are created by the ProjectComponent class, and
     * passed to the ProjectTabbedComponent as new tabs.
     */
    class DiagramComponent  : public Component
    {
    public:
        //! Constructor.
        /*!
         * Constructor.
         * 
         * \param diagram The diagram to wrap.
         * \param index The index of this diagram in the parent tabbed component.
         */
        DiagramComponent(UMLDiagram*, const int);
        
        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~DiagramComponent();

        //! Called when the component must redraw itself.
        /*!
         * Called when the component must redraw itself.
         *
         * \param g The Graphics instance where the instance is drawn.
         */
        void paint(Graphics&);
        
        //! Called when the component is resized.
        /*!
         * Called when the component is resized.
         */
        void resized();
        
        //! Exports the wrapped diagram as a PNG file.
        /*!
         * Exports the wrapped diagram as a PNG file.
         */
        void exportAsPNG();

        //! Tells the wrapped diagram to show or hide the grid.
        /*!
         * Tells the wrapped diagram to show or hide the grid.
         */
        void toggleGrid();
        
        //! Forwards a notification to the wrapped diagram.
        /*!
         * Forwards a notification to the wrapped diagram.
         * 
         * \param notification A NewFigureAdded notification.
         */
        void addFigure(const AutoPtr<NewFigureAdded>&);
        
        //! Returns the unique ID of the wrapped diagram.
        /*!
         * Returns the unique ID of the wrapped diagram.
         * 
         * \return A string.
         */
        const string& getUniqueId() const;
        
        //! Tells the wrapped diagram to delete the figures selected by the user.
        /*!
         * Tells the wrapped diagram to delete the figures selected by the user.
         */
        void deleteSelectedFigures();

    private:
        //! Handles the ProjectTabbedComponentChangedTab notification.
        /*!
         * Handles the ProjectTabbedComponentChangedTab notification.
         *
         * \param notification The notification passed by the Poco::NotificationCenter.
         */
        void handleProjectTabbedComponentChangedTab(const AutoPtr<ProjectTabbedComponentChangedTab>&);

        //! Handles the ActiveWindowStatusChanged notification.
        /*!
         * Handles the ActiveWindowStatusChanged notification.
         *
         * \param notification The notification passed by the Poco::NotificationCenter.
         */
        void handleActiveWindowStatusChanged(const AutoPtr<ActiveWindowStatusChanged>&);

    private:
        //! States whether the current instance is visible in the parent tabbed component.
        bool _isActive;
        
        //! Stores the index of the current instance in the parent tabbed component.
        const int _index;
        
        //! Provides scrolling capabilities to the internal UMLDiagram instance.
        Viewport* _viewport;
        
        //! Pointer to the toolbar of the diagram wrapped by the current instance.
        DiagramToolbar* _toolbar;
        
        //! The UMLDiagram instance wrapped by the current object.
        UMLDiagram* _diagram;

        //! Observer for ProjectTabbedComponentChangedTab notifications.
        NObserver<DiagramComponent, ProjectTabbedComponentChangedTab>* _tabObserver;

        //! Observer for ActiveWindowStatusChanged notifications.
        NObserver<DiagramComponent, ActiveWindowStatusChanged>* _windowStatusObserver;
    };
}

#endif   /* DIAGRAMCOMPONENT_H_ */
