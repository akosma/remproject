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

#include <Poco/AutoPtr.h>

#include "PlatformDefinitions.h"

#include <vector>

#ifndef ARROWCANVAS_H_
#define ARROWCANVAS_H_

#ifndef FIGURESELECTED_H_
#include "../notifications/FigureSelected.h"
#endif

using Poco::AutoPtr;
using std::vector;
using notifications::FigureSelected;

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    class Figure;
    class FigureLassoSource;
    class UMLDiagram;
    class ArrowFigure;
    
    /*!
     * \class ArrowCanvas
     *
     *  
     */
    class ArrowCanvas : public Component
    {
    public:
        /*!
         *  ArrowCanvas constructor.
         */
        ArrowCanvas();

        /*!
         *  ArrowCanvas virtual destructor.
         */
        virtual ~ArrowCanvas();

        virtual void mouseDown(const MouseEvent&);
        virtual void mouseMove(const MouseEvent&);
        virtual void mouseUp(const MouseEvent& e);
        virtual void mouseDrag(const MouseEvent& e);

        void paint(Graphics&);
        void setSelectedItemSet(SelectedItemSet<Figure*>&, UMLDiagram*);
        const int getNumArrows() const;
        
        void addArrow(Figure*, Figure*, ArrowFigure*);
        void showArrowSelected(ArrowFigure*);
        const bool arrowIntersects(ArrowFigure*, const Rectangle&);
        void deselectAllArrows();
        
        void toggleGrid();
        
    private:
        void postArrowCanvasClicked();
        void postFigureSelected(ArrowFigure*, const MouseEvent&);
        void handleFigureSelected(const AutoPtr<FigureSelected>&);
        void drawGrid(Graphics& g);

    private:
        class Arrow
        {
        public:
            Arrow(Figure*, Figure*, ArrowFigure*);
            Arrow(const Arrow&);
            Arrow& operator=(const Arrow&);
            virtual ~Arrow();
            const Figure* getStartFigure() const;
            const Figure* getEndFigure() const;
            const ArrowFigure* getArrowFigure() const;
            const bool isSelected() const;
            void setSelected(const bool);
            const bool intersects(const MouseEvent&);
            const Rectangle* getEnclosingRectangle() const;
            const bool intersects(const Rectangle&) const;

        private:
            Figure* _start;
            Figure* _end;
            ArrowFigure* _arrowFigure;
            bool _selected;
        };

    private:
        const float _strokeWidth;
        vector<Arrow*> _arrows;
        bool _drawGrid;
        LassoComponent<Figure*>* _lassoComponent;
        FigureLassoSource* _lassoSource;
    };
}

#endif /* ARROWCANVAS_H_ */
