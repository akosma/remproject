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
 * \file FigureLassoSource.cpp
 *
 * Contains the implementation of the ui::FigureLassoSource class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/19/08
 */

#include "FigureLassoSource.h"

#ifndef UMLDIAGRAM_H_
#include "UMLDiagram.h"
#endif

#ifndef ARROWCANVAS_H_
#include "ArrowCanvas.h"
#endif

#ifndef ARROWFIGURE_H_
#include "ArrowFigure.h"
#endif

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * FigureLassoSource Constructor.
     */
    FigureLassoSource::FigureLassoSource(SelectedItemSet<Figure*>& items, UMLDiagram* diagram, ArrowCanvas* canvas)
    : LassoSource<Figure*>()
    , _itemSet(items)
    , _diagram(diagram)
    , _canvas(canvas)
    {
    }
    
    /*!
     * FigureLassoSource Virtual destructor.
     */
    FigureLassoSource::~FigureLassoSource()
    {
    }

    void FigureLassoSource::findLassoItemsInArea(Array<Figure*>& itemsFound, int x, int y, int width, int height)
    {
        const juce::Rectangle lasso (x, y, width, height);
        for (int i = 0; i < _diagram->getNumChildComponents(); ++i)
        {
            Figure* figure = dynamic_cast<Figure*>(_diagram->getChildComponent(i));
            if (figure != NULL)
            {
                if (figure->getBounds().intersects(lasso))
                {
                    figure->setSelected(true);
                    itemsFound.add(figure);
                }
                else
                {
                    figure->setSelected(false);
                    if (itemsFound.contains(figure))
                    {
                        itemsFound.removeValue(figure);
                    }
                }
            }
            ArrowFigure* arrow = dynamic_cast<ArrowFigure*>(_diagram->getChildComponent(i));
            if (arrow != NULL)
            {
                if (_canvas->arrowIntersects(arrow, lasso))
                {
                    itemsFound.add(figure);
                }
                else
                {
                    itemsFound.removeValue(figure);
                }
            }
        }
    }
    
    SelectedItemSet<Figure*>& FigureLassoSource::getLassoSelection()
    {
        return _itemSet;
    }
}
