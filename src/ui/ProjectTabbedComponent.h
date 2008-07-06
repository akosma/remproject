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

#ifndef PROJECTTABBEDCOMPONENT_H_
#define PROJECTTABBEDCOMPONENT_H_

#include "PlatformDefinitions.h"

#ifndef EXPORTDIAGRAMASPNGNOTIFICATION_H_
#include "ExportDiagramAsPNGNotification.h"
#endif

using Poco::AutoPtr;

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * \class ProjectTabbedComponent
     *
     *  
     */
    class ProjectTabbedComponent : public TabbedComponent
    {
    public:

        /*!
         *  ProjectTabbedComponent constructor.
         */
        ProjectTabbedComponent();

        /*!
         *  ProjectTabbedComponent virtual destructor.
         */
        virtual ~ProjectTabbedComponent();
        
        virtual void currentTabChanged(const int, const String&);
        
        void postProjectTabbedComponentChangedTabNotification(const int, const String&);
        
        void ProjectTabbedComponent::handleExportDiagramAsPNGNotification(const AutoPtr<ExportDiagramAsPNGNotification>&);
    };
}

#endif /* PROJECTTABBEDCOMPONENT_H_ */
