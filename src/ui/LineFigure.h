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

//! Contains the interface of the ui::LineFigure class.
/*!
 * \file LineFigure.h
 *
 * Contains the interface of the ui::LineFigure class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      8/16/08
 */

#include <string>
#include "PlatformDefinitions.h"

#ifndef LINEFIGURE_H_
#define LINEFIGURE_H_

#ifndef FIGURE_H_
#include "Figure.h"
#endif

using std::string;

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    //! Represents a straight, solid line between two figures.
    /*!
     * \class LineFigure
     *
     * Represents a straight, solid line between two figures. Works as a
     * base class for any type of lines used in the application, like arrows.
     */
    class LineFigure : public Figure
    {
    public:
        //! Constructor.
        /*!
         * Constructor.
         * 
         * \param uniqueId The unique ID of this instance.
         * \param a The figure from which the line starts.
         * \param b The figure where the line ends.
         */
        LineFigure(const string&, Figure*, Figure*);

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~LineFigure();
        
        //! Gets the figure where the line starts.
        /*!
         * Gets the figure where the line starts.
         * 
         * \return A pointer to a Figure.
         */
        Figure* getStartFigure() const;

        //! Gets the figure where the line ends.
        /*!
         * Gets the figure where the line ends.
         * 
         * \return A pointer to a Figure.
         */
        Figure* getEndFigure() const;

        //! Draws the line on the ArrowCanvas of the diagram.
        /*!
         * Draws the line on the ArrowCanvas of the diagram. This
         * method can be overridden by child classes, to provide custom
         * arrow or line effects.
         * 
         * \param g The Graphics context where the drawing takes place.
         */
        virtual void drawLine(Graphics&) const;
        
    protected:
        //! Draws the figure.
        /*!
         * Draws the figure. This method is called during paint() and
         * tells subclasses to perrform any additional drawing polymorphically.
         *
         * \param figure A Path object where the figure is drawn as a vector image.
         */
        virtual void drawFigure(Path&) const;

        //! Gives subclasses a chance to update the AnyPropertyMap instance.
        /*!
         * Gives subclasses a chance to update the AnyPropertyMap instance 
         * with other properties than those of the base class. This information
         * is meant to be saved later in the SQLite file.
         */
        virtual void updateSpecificProperties();

        //! Tells subclasses to update their state accordingly to the AnyPropertyMap instance.
        /*!
         * Tells subclasses to update their state accordingly to the AnyPropertyMap instance.
         */
        virtual void setSpecificProperties();
        
    private:
        //! Pointer to the Figure instance where this line starts.
        Figure* _start;
        
        //! Pointer to the Figure instance where this line ends.
        Figure* _end;
    };
}

#endif /* LINEFIGURE_H_ */
