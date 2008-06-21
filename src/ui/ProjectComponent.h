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

#include "juce.h"

#ifndef PROJECTCOMPONENT_H_
#define PROJECTCOMPONENT_H_

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * \class ProjectComponent
     *
     *  
     */
    class ProjectComponent : public Component
    {
    public:

        /*!
         *  ProjectComponent constructor.
         */
        ProjectComponent();

        /*!
         *  ProjectComponent virtual destructor.
         */
        virtual ~ProjectComponent();
        
        void resized();
        
    private:
        TabbedComponent* _tabs;
    };
}

#endif /* PROJECTCOMPONENT_H_ */
