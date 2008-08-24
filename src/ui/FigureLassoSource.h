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

//! Contains the interface of the ui::FigureLassoSource class.
/*!
 * \file FigureLassoSource.h
 *
 * Contains the interface of the ui::FigureLassoSource class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/19/08
 */

#include "PlatformDefinitions.h"

#ifndef FIGURELASSOSOURCE_H_
#define FIGURELASSOSOURCE_H_

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    // Forward declarations to avoid inclusions.
    class Figure;
    class UMLDiagram;
    class ArrowCanvas;

    //! Used to catch figures while the user drags the mouse on the canvas.
    /*!
     * \class FigureLassoSource
     *
     * Represents an object used to "catch" items while the user drags
     * the mouse on the canvas.
     */
    class FigureLassoSource : public LassoSource<Figure*>
    {
    public:

        //! Constructor.
        /*!
         * Constructor.
         * 
         * \param items A set of Figures.
         * \param diagram A pointer to a UMLDiagram instance.
         * \param canvas A pointer to an ArrowCanvas instance.
         */
        FigureLassoSource(SelectedItemSet<Figure*>&, UMLDiagram*, ArrowCanvas*);

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~FigureLassoSource();

        //! Returns the set of items that lie within a given region.
        /*!
         * Returns the set of items that lie within a given region. 
         * 
         * \param itemsFound An array of items to be filled with the items found.
         * \param x The x coordinate of the lasso rectangle.
         * \param y The y coordinate of the lasso rectangle.
         * \param width The width of the lasso rectangle.
         * \param height The height of the lasso rectangle.
         */
        virtual void findLassoItemsInArea(Array<Figure*>&, int, int, int, int);

        //! Returns the SelectedItemSet that the lasso should update.
        /*!
         * Returns the SelectedItemSet that the lasso should update.
         * 
         * \return A set of selected items.
         */
        virtual SelectedItemSet<Figure*>& getLassoSelection();
        
    private:
        //! The set of selected items.
        SelectedItemSet<Figure*>& _itemSet;
        
        //! The diagram in which the selection is performed.
        UMLDiagram* _diagram;
        
        //! The canvas in which the selection is performed.
        ArrowCanvas* _canvas;
    };
}

#endif /* FIGURELASSOSOURCE_H_ */
