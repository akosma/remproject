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

#include "juce.h"

#include <vector>

#ifndef ARROWCANVAS_H_
#define ARROWCANVAS_H_

using std::vector;

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    class ContentComponent;
    class Figure;
    
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
        ArrowCanvas(ContentComponent*);

        /*!
         *  ArrowCanvas virtual destructor.
         */
        virtual ~ArrowCanvas();

        void mouseDown(const MouseEvent&);
        void paint(Graphics&);
        void setNoCurrentArrow();
        
        void addArrow(Figure*, Figure*);

    private:
        class Arrow
        {
        public:
            Arrow(Figure*, Figure*);
            Arrow(const Arrow&);
            Arrow& operator=(const Arrow&);
            virtual ~Arrow();
            const Figure* getStartFigure() const;
            const Figure* getEndFigure() const;
            const bool intercepts(const MouseEvent&);

        private:
            Figure* _start;
            Figure* _end;
        };

    private:
        ContentComponent* _parent;
        const float _strokeWidth;
        vector<Arrow*> _arrows;
        Arrow* _currentArrow;
    };
}

#endif /* ARROWCANVAS_H_ */
