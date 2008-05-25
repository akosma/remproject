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

//! Contains the interface of the controller::Controller class.
/*!
 * \file Controller.h
 *
 * Contains the interface of the controller::Controller class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      5/25/08
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

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

using utility::Singleton;
using metamodel::Project;
using metamodel::Diagram;
using metamodel::Element;

//! Contains the Controller class of the application.
/*!
 * \namespace controller
 * Contains the Controller class of the application, following
 * the naming conventions of the MVC design pattern.
 */
namespace controller
{
    //! Inteface between the View and Model of the MVC architecture.
    /*!
     * \class Controller
     *
     * Provides an isolation interface between the classes in the 
     * "ui" or "commandline" namespaces (the "View"), and those 
     * in the "metamodel" namespace (the "Model"), following the MVC
     * design pattern.
     */
    class Controller : public Singleton<Controller>
    {
    public:

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~Controller();

    private:

        //! Private constructor.
        /*!
         * Private constructor.
         */
        Controller();

        //! Allow the Singleton template class to access the private constructor.
        friend Controller& Singleton<Controller>::get();
        
    private:
        //! Instance of the Project class controlled by this Controller.
        Project _project;
    };
}

#endif /* CONTROLLER_H_ */
