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

//! Contains the interface of the ui::UseCaseFigure class.
/*!
 * \file UseCaseFigure.h
 *
 * Contains the interface of the ui::UseCaseFigure class.
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

#ifndef FIGURE_H_
#include "Figure.h"
#endif

#ifndef USECASEFIGURE_H_
#define USECASEFIGURE_H_

using std::string;

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    //! Represents a use-case bubble in a Use Case diagram.
    /*!
     * \class UseCaseFigure
     *
     * Represents a use-case bubble in a Use Case diagram.
     */
    class UseCaseFigure : public Figure, public LabelListener, public TooltipClient
    {
    public:

        //! Constructor.
        /*!
         * Constructor.
         * 
         * \param uniqueId The unique ID of this instance.
         */
        UseCaseFigure(const string&);

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~UseCaseFigure();

        //! Called when the user double-clicks on the canvas.
        /*!
         * Called when the user double-clicks on the canvas.
         *
         * \param e The MouseEvent object passed by the runtime.
         */
        void mouseDoubleClick(const MouseEvent& e);
        
        //! Called when the text of the label changes.
        /*!
         * Called when the text of the label changes.
         * 
         * \param label The label which triggered this callback.
         */
        virtual void labelTextChanged(Label*);

        //! Returns a string to be shown as tooltip.
        /*!
         * Returns a string to be shown as tooltip when the 
         * user hovers over the figure.
         * 
         * \return A String value.
         */
        virtual const String getTooltip();

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
        //! A label holding a title for the current instance.
        Label* _nameLabel;
    };
}

#endif /* USECASEFIGURE_H_ */
