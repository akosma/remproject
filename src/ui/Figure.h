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

using Poco::AutoPtr;
using Poco::NObserver;
using notifications::ArrowCanvasClicked;
using std::string;

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    /*!
     * \class Figure
     *
     *  
     */
    class Figure : public Component
    {
    public:
        /*!
         *  Figure constructor.
         */
        Figure(const int, const int, const string&);

        /*!
         *  Figure virtual destructor.
         */
        virtual ~Figure();

        void paint(Graphics&);
        
        void mouseDown(const MouseEvent&);
        void mouseUp(const MouseEvent&);
        void mouseDrag(const MouseEvent&);
        void mouseEnter(const MouseEvent&);
        void mouseExit(const MouseEvent&);
        void resized();
        
        const Point* getAnchorPointRelativeTo(const Figure*) const;
        
        void setSelected(bool);
        const bool isSelected();
        const string& getUniqueId() const;

    protected:
        virtual void drawFigure(Path&) = 0;
        
        const int getInitialWidth();
        const int getInitialHeight();
        const float getInitialMargin();
        const float getStrokeWidth();
        
    private:
        void drawDashedLineAround(Graphics&);
        void postFigureSelected(const MouseEvent&);
        void postFigureMoved();
        void handleArrowCanvasClicked(const AutoPtr<ArrowCanvasClicked>&);

    private:
        bool _selected;
        bool _hover;
        ComponentDragger _dragger;
        ResizableBorderComponent* _resizer;
        const int _initWidth;
        const int _initHeight;
        const float _initMargin;
        const float _strokeWidth;
        const string _id;
        NObserver<Figure, ArrowCanvasClicked>* _arrowCanvasObserver;
    };
}

#endif /* FIGURE_H_ */
