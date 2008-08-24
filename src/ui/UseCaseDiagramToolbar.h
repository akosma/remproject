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

//! Contains the interface of the ui::UseCaseDiagramToolbar class.
/*!
 * \file Toolbar.cpp
 *
 * Contains the interface of the ui::UseCaseDiagramToolbar class.
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 *
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      21 Jun 2008 4:48:24 pm
 */

#ifndef USECASEDIAGRAMTOOLBAR_H_
#define USECASEDIAGRAMTOOLBAR_H_

#ifndef DIAGRAMTOOLBAR_H_
#include "DiagramToolbar.h"
#endif

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    //! Represents a specific toolbar taylored to Use Case diagrams.
    /*!
     * \class UseCaseDiagramToolbar
     *
     * Represents a specific toolbar taylored to Use Case diagrams.
     */
    class UseCaseDiagramToolbar  : public DiagramToolbar
    {
    public:
        //! Constructor
        /*!
         * Constructor.
         */
        UseCaseDiagramToolbar();

        //! Virtual destructor
        /*!
         * Virtual destructor.
         */
        virtual ~UseCaseDiagramToolbar();
    };
}

#endif   /* USECASEDIAGRAMTOOLBAR_H_ */
