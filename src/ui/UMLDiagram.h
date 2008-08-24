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

//! Contains the interface of the ui::UMLDiagram class.
/*!
 * \file UMLDiagram.h
 *
 * Contains the interface of the ui::UMLDiagram class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/11/08
 */

#include <Poco/AutoPtr.h>
#include <Poco/NotificationCenter.h>
#include <Poco/NObserver.h>
#include <string>

#include "PlatformDefinitions.h"

#ifndef UMLDIAGRAM_H_
#define UMLDIAGRAM_H_

#ifndef FIGURESELECTED_H_
#include "../notifications/FigureSelected.h"
#endif

#ifndef ARROWCANVASCLICKED_H_
#include "../notifications/ArrowCanvasClicked.h"
#endif

#ifndef FIGURECHANGED_H_
#include "../notifications/FigureChanged.h"
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
using Poco::NotificationCenter;
using Poco::NObserver;
using notifications::FigureSelected;
using notifications::ArrowCanvasClicked;
using notifications::FigureChanged;
using notifications::NewFigureAdded;
using metamodel::Diagram;
using std::string;

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    // Forward declarations to avoid includes
    class Figure;
    class ArrowCanvas;
    class FigureLassoSource;
    class DiagramToolbar;
    class LineFigure;
    
    //! Base class for all visible diagram components.
    /*!
     * \class UMLDiagram
     *
     * Abstract base class for all visible diagram components. Instances of 
     * the subclasses of this class are created by the ProjectComponent class,
     * which wraps them around DiagramComponent classes, and are later added
     * as individual tabs of the ProjectTabbedComponent class.
     */
    class UMLDiagram : public Component
    {
    public:
        //! Constructor.
        /*!
         * Constructor.
         * 
         * \param uniqueId The unique ID of the current instance.
         */
        UMLDiagram(const string&);

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~UMLDiagram();

        //! Repaints the current diagram and all its children.
        /*!
         * Repaints the current diagram and all its children.
         * 
         * \param g The Graphics component where the drawing takes place.
         */
        void paint (Graphics&);

        //! Toggles the visibility of the grid on and off.
        /*!
         * Toggles the visibility of the grid on and off. This method
         * calls the ArrowCanvas::toggleGrid() method in turn.
         */
        void toggleGrid();
        
        //! Returns the unique ID of the current instance.
        /*!
         * Returns the unique ID of the current instance.
         * 
         * \return A reference to a string.
         */
        const string& getUniqueId() const;
        
        //! Deletes the figures selected by the user.
        /*!
         * Deletes the figures selected by the user.
         */
        void deleteSelectedFigures();
        
        //! Adds a new figure to the current diagram.
        /*!
         * Adds a new figure to the current diagram. Subclasses implement this
         * method to handle the subclasses of Figure that interest them.
         * 
         * \param notification A reference to the NewFigureAdded notification 
         * received by the parent ProjectTabbedComponent instance.
         */
        virtual void addFigure(const AutoPtr<NewFigureAdded>&) = 0;
        
        //! Populates this instance with the contents of a metamodel::Diagram.
        /*!
         * Populates this instance with the contents of a metamodel::Diagram.
         *
         * \param diagram An instance of the metamodel::Diagram class, retrieved from file.
         */
        virtual void populateFrom(Diagram*) = 0;

        //! Returns the DiagramToolbar instance that belongs to this class.
        /*!
         * Returns the DiagramToolbar instance that belongs to this class.
         * Subclasses implement this method to return an object that corresponds
         * to their specific needs, and which is displayed as the diagram toolbar.
         * Clients calling this method are responsible for disposing of the instance.
         * 
         * \return A pointer to a DiagramToolbar instance.
         */
        virtual DiagramToolbar* createToolbar() = 0;

    protected:
        
        //! Informs subclasses of the number of selected items.
        /*!
         * Informs subclasses of the number of selected items.
         * 
         * \return An integer.
         */
        const int getSelectedItemsCount() const;
        
        //! Returns an array of figures which have been selected.
        /*!
         * Returns an array of figures which have been selected.
         *
         * \return An array of Figure instances.
         */
        const Array<Figure*>& getSelectedItems();
        
        //! Returns a figure contained in this diagram, identified by its unique ID.
        /*!
         * Returns a figure contained in this diagram, identified by its unique ID.
         * 
         * \return A pointer to a Figure instance, or NULL.
         */
        Figure* getFigureByUniqueId(const string& uniqueId);

        //! Sets the grid visible or not.
        /*!
         * Sets the grid visible or not.
         * 
         * \param visible True to make the grid visible, false otherwise.
         */
        void setGridVisible(const bool);
        
    protected:
        //! Handles the FigureSelected notification.
        /*!
         * Handles the FigureSelected notification.
         *
         * \param notification The notification passed by the Poco::NotificationCenter.
         */
        void handleFigureSelected(const AutoPtr<FigureSelected>&);

        //! Handles the ArrowCanvasClicked notification.
        /*!
         * Handles the ArrowCanvasClicked notification.
         *
         * \param notification The notification passed by the Poco::NotificationCenter.
         */
        void handleArrowCanvasClicked(const AutoPtr<ArrowCanvasClicked>&);

        //! Handles the FigureChanged notification.
        /*!
         * Handles the FigureChanged notification.
         *
         * \param notification The notification passed by the Poco::NotificationCenter.
         */
        void handleFigureChanged(const AutoPtr<FigureChanged>&);
        
        //! Adds the line passed as parameter to the canvas.
        /*!
         * Adds the line passed as parameter to the canvas.
         * 
         * \param lineFigure The line to add to the canvas.
         */
        void addLineToCanvas(LineFigure*);
        
    private:
        //! A canvas to draw arrows in.
        ArrowCanvas* _canvas;
        
        //! A set of selected items.
        SelectedItemSet<Figure*> _selection;

        //! Observer of FigureSelected notifications.
        NObserver<UMLDiagram, FigureSelected>* _figureObserver;

        //! Observer of ArrowCanvasClicked notifications.
        NObserver<UMLDiagram, ArrowCanvasClicked>* _arrowObserver;

        //! Observer of FigureChanged notifications.
        NObserver<UMLDiagram, FigureChanged>* _changeObserver;

        //! The unique identifier of the current instance. This ID is used
        //! to match this instance to the metamodel::Diagram corresponding instance.
        const string _id;
    };
}

#endif /* UMLDIAGRAM_H_ */
