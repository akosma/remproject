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

//! Contains the interface of the ui::ArrowCanvas class.
/*!
 * \file ArrowCanvas.h
 *
 * Contains the interface of the ui::ArrowCanvas class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/21/08
 */

#include <vector>
#include <Poco/AutoPtr.h>
#include "PlatformDefinitions.h"

#ifndef ARROWCANVAS_H_
#define ARROWCANVAS_H_

#ifndef FIGURESELECTED_H_
#include "../notifications/FigureSelected.h"
#endif

using Poco::AutoPtr;
using std::vector;
using notifications::FigureSelected;
using juce::Rectangle;

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    // Forward declarations
    class Figure;
    class FigureLassoSource;
    class UMLDiagram;
    class ArrowFigure;
    class LineFigure;
    
    //! Used by UMLDiagram instances to draw lines and arrows.
    /*!
     * \class ArrowCanvas
     *
     * Used by every ui::UMLDiagram subclass instance to draw the lines
     * and arrows required between elements.
     */
    class ArrowCanvas : public Component
    {
    public:
    
        //! Constructor.
        /*!
         * Constructor.
         */
        ArrowCanvas();

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~ArrowCanvas();

        //! Called when the user clicks on the canvas.
        /*!
         * Called when the user clicks on the canvas.
         *
         * \param e The MouseEvent object passed by the runtime.
         */
        virtual void mouseDown(const MouseEvent&);

        //! Called when the user moves the mouse on the canvas.
        /*!
         * Called when the user clicks on the canvas.
         *
         * \param e The MouseEvent object passed by the runtime.
         */
        virtual void mouseMove(const MouseEvent&);

        //! Called when the user releases the mouse button on the canvas.
        /*!
         * Called when the user releases the mouse button on the canvas.
         *
         * \param e The MouseEvent object passed by the runtime.
         */
        virtual void mouseUp(const MouseEvent&);

        //! Called when the user drags an object on the canvas.
        /*!
         * Called when the user drags an object on the canvas.
         *
         * \param e The MouseEvent object passed by the runtime.
         */
        virtual void mouseDrag(const MouseEvent&);

        //! Redraws the component on the screen.
        /*!
         * Redraws the component on the screen. Called every time that the 
         * component changes, or when the repaint() method is called.
         * 
         * \param g The Graphics component where the drawing operations are performed.
         */
        void paint(Graphics&);

        //! Sets the selection set component to that of the enclosing UMLDiagram.
        /*!
         * Sets the selection set component to that of the enclosing UMLDiagram.
         * 
         * \param itemSet The SelectedItemSet to set.
         * \param diagram The enclosing UMLDiagram instance.
         */
        void setSelectedItemSet(SelectedItemSet<Figure*>&, UMLDiagram*);

        //! Adds a line to the current diagram.
        /*!
         * Adds a line to the current diagram.
         * 
         * \param lineFigure The LineFigure to add to the current diagram.
         */
        void addLine(LineFigure*);

        //! Sets as selected the line passed as parameter.
        /*!
         * Sets as selected the line passed as parameter.
         * 
         * \param lineFigure The line figure to set as selected.
         */
        void setLineSelected(LineFigure*);

        //! States whether the line and rectangle passed as parameters intersect.
        /*!
         * States whether the line and rectangle passed as parameters intersect.
         * 
         * \param lineFigure A LineFigure pointer.
         * \param rect A rectangle.
         *
         * \return True if the line and the rectangle intersect, false otherwise.
         */
        const bool lineIntersects(LineFigure*, const juce::Rectangle&);

        //! Sets all the arrows in the canvas as deselected.
        /*!
         * Sets all the arrows in the canvas as deselected.
         */
        void deselectAllArrows();

        //! Alternatively shows and hides the diagram grid.
        /*!
         * Alternatively shows and hides the diagram grid.
         */
        void toggleGrid();

        //! Sets the grid visible or not.
        /*!
         * Sets the grid visible or not.
         * 
         * \param visible True to make the grid visible, false otherwise.
         */
        void setGridVisible(const bool);

    private:

        //! Posts an ArrowCanvasClicked notification.
        /*!
         * Posts an ArrowCanvasClicked notification.
         */
        void postArrowCanvasClicked();

        //! Posts a FigureSelected notification.
        /*!
         * Posts a FigureSelected notification.
         * 
         * \param arrowFigure The line that has been selected.
         * \param e The MouseEvent object generated during the event.
         */
        void postFigureSelected(Figure*, const MouseEvent&);

        //! Draws the grid during the call to the "paint()" method.
        /*!
         * Draws the grid during the call to the "paint()" method.
         * 
         * \param g The Graphics object where to draw the grid.
         */
        void drawGrid(Graphics&);

    private:


        //! Private class used by the ArrowCanvas to draw lines.
        /*!
         * Private class used by the ArrowCanvas. Every line in the ArrowCanvas
         * corresponds to an instance of this class.
         */
        class DrawableLine
        {
        public:

            //! Constructor.
            /*!
             * Constructor.
             *
             * \param lineFigure The LineFigure instance to which the
             * new instance is attached.
             */
            DrawableLine(LineFigure*);

            //! Copy constructor.
            /*!
             * Copy constructor.
             * 
             * \param rhs A DrawableLine to copy the state from.
             */
            DrawableLine(const DrawableLine&);

            //! Assignment operator.
            /*!
             * Assignment operator.
             * 
             * \param rhs A DrawableLine to copy the state from.
             */
            DrawableLine& operator=(const DrawableLine&);

            //! Virtual destructor.
            /*!
             * Virtual destructor.
             */
            virtual ~DrawableLine();

            //! Gets the LineFigure to which this instance is attached.
            /*!
             * Gets the LineFigure to which this instance is attached.
             * 
             * \return A pointer to a LineFigure instance.
             */
            LineFigure* getLineFigure() const;

            //! 
            /*!
             * 
             */
            const bool isSelected() const;

            //! 
            /*!
             * 
             */
            void setSelected(const bool);

            //! 
            /*!
             * 
             */
            const bool intersects(const MouseEvent&);

            //! 
            /*!
             * 
             */
            const juce::Rectangle* getEnclosingRectangle() const;

            //! 
            /*!
             * 
             */
            const bool intersects(const juce::Rectangle&) const;

        private:
            //! Stores a pointer to the originating LineFigure element.
            LineFigure* _lineFigure;
            
            //! States whether the current instance is selected or not.
            bool _selected;
        };

    private:
        //! Width of the lines drawn in the canvas.
        const float _strokeWidth;
        
        //! Vector of lines redrawn at every draw cycle.
        vector<DrawableLine*> _lines;
        
        //! States whether the grid should be drawn at the next cycle.
        bool _drawGrid;
        
        //! Used to select lines when the user is selecting elements with the mouse.
        LassoComponent<Figure*>* _lassoComponent;
        
        //! Used to catch elements when the user selects them with the mouse.
        FigureLassoSource* _lassoSource;
    };
}

#endif /* ARROWCANVAS_H_ */
