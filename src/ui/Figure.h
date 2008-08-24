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

//! Contains the interface of the ui::Figure class.
/*!
 * \file Figure.h
 *
 * Contains the interface of the ui::Figure class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/19/08
 */

#include <string>
#include <Poco/AutoPtr.h>
#include <Poco/NObserver.h>

#include "PlatformDefinitions.h"

#ifndef FIGURE_H_
#define FIGURE_H_

#ifndef ARROWCANVASCLICKED_H_
#include "../notifications/ArrowCanvasClicked.h"
#endif

namespace storage
{
    class AnyPropertyMap;
}

using Poco::AutoPtr;
using Poco::NObserver;
using notifications::ArrowCanvasClicked;
using std::string;
using storage::AnyPropertyMap;

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    //! Abstract base class for diagram elements.
    /*!
     * \class Figure
     *
     * Abstract base class for elements that can be inserted, moved and deleted
     * from a UMLDiagram instance.
     */
    class Figure : public Component
    {
    public:
    
        //! Constructor.
        /*!
         * Constructor.
         * 
         * \param initWidth The initial width of this instance.
         * \param initHeight The initial height of this instance.
         * \param uniqueId The unique ID of this instance.
         */
        Figure(const int, const int, const string&);

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~Figure();

        //! Called when the component is asked to redraw itself on screen.
        /*!
         * Called when the component is asked to redraw itself on screen.
         * 
         * \param g The Graphics component where the redrawing takes place.
         */
        void paint(Graphics&);
        
        //! Called when the user clicks on the canvas.
        /*!
         * Called when the user clicks on the canvas.
         *
         * \param e The MouseEvent object passed by the runtime.
         */
        void mouseDown(const MouseEvent&);

        //! Called when the user releases the mouse button on the canvas.
        /*!
         * Called when the user releases the mouse button on the canvas.
         *
         * \param e The MouseEvent object passed by the runtime.
         */
        void mouseUp(const MouseEvent&);

        //! Called when the user drags an object on the canvas.
        /*!
         * Called when the user drags an object on the canvas.
         *
         * \param e The MouseEvent object passed by the runtime.
         */
        void mouseDrag(const MouseEvent&);

        //! Called when the mouse enters in the area of the figure.
        /*!
         * Called when the mouse enters in the area of the figure.
         *
         * \param e The MouseEvent object passed by the runtime.
         */
        void mouseEnter(const MouseEvent&);

        //! Called when the mouse leaves the area of the figure.
        /*!
         * Called when the mouse leaves the area of the figure.
         *
         * \param e The MouseEvent object passed by the runtime.
         */
        void mouseExit(const MouseEvent&);

        //! Called when the size of the figure is changed.
        /*!
         * Called when the size of the figure is changed.
         */
        void resized();

        //! Returns the point at which all lines start from this figure.
        /*!
         * Returns the point at which all lines start from this figure. This
         * point is located in the rectangle surrounding the figure, and
         * its position (top, bottom, left or right) depends on its relative
         * position in comparison to the figure passed in parameter. This is
         * used to draw lines and arrows between figures.
         *
         * \param other The figure to which a line should be drawn.
         */
        const Point* getAnchorPointRelativeTo(const Figure*) const;

        //! Sets the current figure as selected.
        /*!
         * Sets the current figure as selected.
         *
         * \param selected A boolean value.
         */
        void setSelected(bool);

        //! Informs clients whether the current instance is selected or not.
        /*!
         * Informs clients whether the current instance is selected or not.
         *
         * \return A boolean; true if this instance is selected, false otherwise.
         */
        const bool isSelected() const;

        //! Returns the unique ID of the current instance.
        /*!
         * Returns the unique ID of the current instance.
         *
         * \return A string reference.
         */
        const string& getUniqueId() const;

        //! Returns the properties of the current figure.
        /*!
         * Returns the properties of the current figure. This is used
         * to merge them with those in the controllers::FileController instance
         * and then save them.
         *
         * \return A reference to the internal storage::AnyPropertyMap instance.
         */
        AnyPropertyMap& getProperties();

        //! Sets the property map of the current instance.
        /*!
         * Sets the property map of the current instance.
         * 
         * \param props The new properties for the current instance.
         */
        void setProperties(const AnyPropertyMap&);

    protected:

        //! Draws the figure.
        /*!
         * Draws the figure. This method is called during paint() and
         * tells subclasses to perrform any additional drawing polymorphically.
         *
         * \param figure A Path object where the figure is drawn as a vector image.
         */
        virtual void drawFigure(Path&) const = 0;

        //! Gives subclasses a chance to update the AnyPropertyMap instance.
        /*!
         * Gives subclasses a chance to update the AnyPropertyMap instance 
         * with other properties than those of the base class. This information
         * is meant to be saved later in the SQLite file.
         */
        virtual void updateSpecificProperties() = 0;

        //! Tells subclasses to update their state accordingly to the AnyPropertyMap instance.
        /*!
         * Tells subclasses to update their state accordingly to the AnyPropertyMap instance.
         */
        virtual void setSpecificProperties() = 0;

        //! Gets the initial width of the figure.
        /*!
         * Gets the initial width of the figure.
         * 
         * \return An integer value.
         */
        const int getInitialWidth() const;

        //! Gets the initial height of the figure.
        /*!
         * Gets the initial height of the figure.
         * 
         * \return An integer value.
         */
        const int getInitialHeight() const;

        //! Gets the initial margin of the figure.
        /*!
         * Gets the initial margin of the figure.
         * 
         * \return An float value.
         */
        const float getInitialMargin() const;

        //! Gets the stroke width of the figure.
        /*!
         * Gets the stroke width of the figure.
         * 
         * \return An float value.
         */
        const float getStrokeWidth() const;

        //! Posts a FigureChanged notification.
        /*!
         * Posts a FigureChanged notification.
         */
        void postFigureChanged();

    private:

        //! Draws a dashed line around the figure.
        /*!
         * Draws a dashed line around the figure when the mouse hovers
         * over the figure, or selects it.
         *
         * \param g The Graphics instance where the line is drawn.
         */
        void drawDashedLineAround(Graphics&);

        //! Posts a FigureSelected notification.
        /*!
         * Posts a FigureSelected notification.
         * 
         * \param e The MouseEvent that generated the selection.
         */
        void postFigureSelected(const MouseEvent&);

        //! Handles an ArrowCanvasClicked notification.
        /*!
         * Handles an ArrowCanvasClicked notification.
         *
         * \param notification The ArrowCanvasClicked notification.
         */
        void handleArrowCanvasClicked(const AutoPtr<ArrowCanvasClicked>&);

        //! Called before posting a FigureChanged notification.
        /*!
         * Called before posting a FigureChanged notification. It calls 
         * updateSpecificProperties() so that subclasses can update their
         * state before posting the notification.
         */
        void updateProperties();

    private:
        //! States whether the current instance is selected.
        bool _selected;

        //! States whether the mouse is hovering the current instance.
        bool _hover;

        //! This component allows figures to be dragged around.
        ComponentDragger _dragger;

        //! This component allows figures to be resized.
        ResizableBorderComponent* _resizer;

        //! Stores the initial width of the figure.
        const int _initWidth;

        //! Stores the initial height of the figure.
        const int _initHeight;

        //! Stores the initial margin of the figure.
        const float _initMargin;

        //! Stores the width of the lines used to draw the figure.
        const float _strokeWidth;

        //! Stores the unique ID of the current instance.
        const string _id;

        //! Observer for ArrowCanvasClicked notifications.
        NObserver<Figure, ArrowCanvasClicked>* _arrowCanvasObserver;

        //! Stores different properties about the figure, to be later saved in file.
        AnyPropertyMap* _properties;
    };
}

#endif /* FIGURE_H_ */
