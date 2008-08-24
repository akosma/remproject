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
    // Forward declarations to avoid includes
    class ActorFigure;
    class UseCaseFigure;
    class LineFigure;

    //! Represents a diagram holding Actors, Use Case bubbles and their relationships.
    /*!
     * \class UseCaseDiagram
     *
     * Represents a diagram holding Actors, Use Case bubbles and their relationships.
     */
    class UseCaseDiagram : public UMLDiagram
    {
    public:
        //! Constructor.
        /*!
         * Constructor.
         * 
         * \param uniqueId The unique ID of the current instance.
         */
        UseCaseDiagram(const string&);

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~UseCaseDiagram();

        //! Adds an ActorFigure to the current diagram.
        /*!
         * Adds an ActorFigure to the current diagram.
         * 
         * \param uniqueId The unique ID of the figure to be added.
         * 
         * \return A pointer to the newly created instance.
         */
        ActorFigure* addActorFigure(const string&);

        //! Adds an UseCaseFigure to the current diagram.
        /*!
         * Adds an UseCaseFigure to the current diagram.
         * 
         * \param uniqueId The unique ID of the figure to be added.
         * 
         * \return A pointer to the newly created instance.
         */
        UseCaseFigure* addUseCaseFigure(const string&);

        //! Adds a new figure to the current diagram.
        /*!
         * Adds a new figure to the current diagram. Subclasses implement this
         * method to handle the subclasses of Figure that interest them.
         * 
         * \param notification A reference to the NewFigureAdded notification 
         * received by the parent ProjectTabbedComponent instance.
         */
        virtual void addFigure(const AutoPtr<NewFigureAdded>&);

        //! Populates this instance with the contents of a metamodel::Diagram.
        /*!
         * Populates this instance with the contents of a metamodel::Diagram.
         *
         * \param diagram An instance of the metamodel::Diagram class, retrieved from file.
         */
        virtual void populateFrom(Diagram*);

        //! Returns the DiagramToolbar instance that belongs to this class.
        /*!
         * Returns the DiagramToolbar instance that belongs to this class.
         * Subclasses implement this method to return an object that corresponds
         * to their specific needs, and which is displayed as the diagram toolbar.
         * 
         * \return A pointer to a DiagramToolbar instance.
         */
        virtual DiagramToolbar* createToolbar();
        
    private:
        //! Posts a NewLineAdded notification.
        /*!
         * Posts a NewLineAdded notification.
         * 
         * \param type The type of line that has been added.
         * \param lineFigure The line that has been added.
         */
        void postNewLineAddedNotification(NewFigureAdded::FigureType, LineFigure*);
    };
}

#endif /* USECASEDIAGRAM_H_ */
