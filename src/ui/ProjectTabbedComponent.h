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

//! Contains the interface of the ui::ProjectTabbedComponent class.
/*!
 * \file ProjectTabbedComponent.h
 *
 * Contains the interface of the ui::ProjectTabbedComponent class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/26/08
 */

#include <Poco/AutoPtr.h>
#include <Poco/NObserver.h>

#ifndef PROJECTTABBEDCOMPONENT_H_
#define PROJECTTABBEDCOMPONENT_H_

#include "PlatformDefinitions.h"

#ifndef EXPORTDIAGRAMASPNG_H_
#include "../notifications/ExportDiagramAsPNG.h"
#endif

#ifndef DIAGRAMTOGGLEGRID_H_
#include "../notifications/DiagramToggleGrid.h"
#endif

#ifndef NEWFIGUREADDED_H_
#include "../notifications/NewFigureAdded.h"
#endif

using Poco::AutoPtr;
using Poco::NObserver;
using notifications::ExportDiagramAsPNG;
using notifications::DiagramToggleGrid;
using notifications::NewFigureAdded;

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    //! This component holds tabs, each with a diagram inside.
    /*!
     * \class ProjectTabbedComponent
     *
     * This component holds tabs, each with a diagram inside. There is only
     * one instance of this class in the application, created by the 
     * ProjectComponent class on startup. 
     * 
     * This class is also in charge of exporting the currently displayed 
     * diagram as a PNG file, and also toggles the visibility of the grid
     * on and off. These two tasks are handled here, so that only the 
     * currently visible diagram is affected by the operation. 
     */
    class ProjectTabbedComponent : public TabbedComponent
    {
    public:

        /*!
         * Constructor.
         */
        ProjectTabbedComponent();

        /*!
         * Virtual destructor.
         */
        virtual ~ProjectTabbedComponent();
        
        //! Called when a new tab is selected.
        /*!
         * Called when a new tab is selected.
         *
         * \param newCurrentTabIndex The index of the new tab.
         * \param newCurrentTabName The name of the new tab.
         */
        virtual void currentTabChanged(const int, const String&);
        
        //! Posts a ProjectTabbedComponentChangedTab notification.
        /*!
         * Posts a ProjectTabbedComponentChangedTab notification
         * when a new tab is selected.
         *
         * \param newCurrentTabIndex The index of the new tab.
         * \param newCurrentTabName The name of the new tab.
         */
        void postProjectTabbedComponentChangedTab(const int, const String&);
        
        //! Exports the current diagram as a PNG file.
        /*!
         * Exports the current diagram as a PNG file.
         * 
         * \param notification The ExportDiagramAsPNG notification received.
         */
        void handleExportDiagramAsPNG(const AutoPtr<ExportDiagramAsPNG>&);

        //! Toggles the grid of the current diagram on and off.
        /*!
         * Toggles the grid of the current diagram on and off.
         * 
         * \param notification The DiagramToggleGrid notification received.
         */
        void handleDiagramToggleGrid(const AutoPtr<DiagramToggleGrid>&);

        //! Tells the current diagram to add a figure.
        /*!
         * Tells the current diagram to add a figure.
         * 
         * \param notification The NewFigureAdded notification received.
         */
        void handleNewFigureAdded(const AutoPtr<NewFigureAdded>&);
        
    private:
    
        NObserver<ProjectTabbedComponent, ExportDiagramAsPNG>* _exportObserver;
        NObserver<ProjectTabbedComponent, DiagramToggleGrid>* _gridObserver;
        NObserver<ProjectTabbedComponent, NewFigureAdded>* _figureObserver;

    };
}

#endif /* PROJECTTABBEDCOMPONENT_H_ */
