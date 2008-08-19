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

//! Contains the interface of the ui::UseCaseDiagram class.
/*!
 * \file UseCaseDiagram.h
 *
 * Contains the interface of the ui::UseCaseDiagram class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/11/08
 */

#include <string>
#include <Poco/AutoPtr.h>

#ifndef USECASEDIAGRAM_H_
#define USECASEDIAGRAM_H_

#ifndef UMLDIAGRAM_H_
#include "UMLDiagram.h"
#endif

#ifndef NEWFIGUREADDED_H_
#include "../notifications/NewFigureAdded.h"
#endif

// Forward declaration to avoid includes
namespace metamodel
{
    class Diagram;
}

using Poco::AutoPtr;
using notifications::NewFigureAdded;
using std::string;
using metamodel::Diagram;

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    class ActorFigure;
    class UseCaseFigure;

    /*!
     * \class UseCaseDiagram
     *
     *  
     */
    class UseCaseDiagram : public UMLDiagram
    {
    public:
        UseCaseDiagram();
        virtual ~UseCaseDiagram();
        
        ActorFigure* addActorFigure(const string&);
        UseCaseFigure* addUseCaseFigure(const string&);

        virtual void addFigure(const AutoPtr<NewFigureAdded>&);
        virtual void populateFrom(Diagram*);

    protected:
        virtual DiagramToolbar* createToolbar();
    };
}

#endif /* USECASEDIAGRAM_H_ */
