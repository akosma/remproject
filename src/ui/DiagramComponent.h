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
 * \file DiagramComponent.cpp
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
    class DiagramToolbar;
    class UMLDiagram;

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
        DiagramComponent(UMLDiagram*, const int);
        virtual ~DiagramComponent();

        void paint (Graphics& g);
        void resized();
        bool exportAsPNG();
        void toggleGrid();
        void addFigure(const AutoPtr<NewFigureAdded>&);
        const string& getUniqueId() const;
        void deleteSelectedFigures();

    private:
        void handleProjectTabbedComponentChangedTab(const AutoPtr<ProjectTabbedComponentChangedTab>&);
        void handleActiveWindowStatusChanged(const AutoPtr<ActiveWindowStatusChanged>&);

    private:
        bool _isActive;
        const int _index;
        Viewport* _viewport;
        DiagramToolbar* _toolbar;
        UMLDiagram* _diagram;
        NObserver<DiagramComponent, ProjectTabbedComponentChangedTab>* _tabObserver;
        NObserver<DiagramComponent, ActiveWindowStatusChanged>* _windowStatusObserver;

        // (prevent copy constructor and operator= from being generated..)
        DiagramComponent (const DiagramComponent&);
        const DiagramComponent& operator= (const DiagramComponent&);
    };
}

#endif   // DIAGRAMCOMPONENT_H_
