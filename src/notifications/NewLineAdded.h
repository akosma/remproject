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

//! Contains the interface of the notifications::NewLineAdded class.
/*!
 * \file NewLineAdded.h
 *
 * Contains the interface of the notifications::NewLineAdded class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      8/23/08
 */

#include <string>

#ifndef NEWLINEADDED_H_
#define NEWLINEADDED_H_

#ifndef NEWOBJECTADDED_H_
#include "NewObjectAdded.h"
#endif

#ifndef NEWFIGUREADDED_H_
#include "NewFigureAdded.h"
#endif

namespace ui
{
    class LineFigure;
}

using std::string;
using ui::LineFigure;

//! Notifications passed between application layers to signal events.
/*!
 * \namespace notifications
 * Contains notifications passed between application layers to signal events.
 */
namespace notifications
{
    //! Triggers the adding of a new line to a project.
    /*!
     * \class NewLineAdded
     *
     * Raised by the ui::CommandDelegate class when the user selects
     * to add a new line (arrow or simple line) to a diagram.
     */
    class NewLineAdded : public NewObjectAdded
    {
    public:

        //! Constructor.
        /*!
         * Constructor.
         */
        NewLineAdded(NewFigureAdded::FigureType, LineFigure*);

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~NewLineAdded();
        
        //! Returns a pointer to the line that was added to the diagram.
        /*!
         * Returns a pointer to the line that was added to the diagram.
         *
         * \return A pointer to a LineFigure.
         */
        LineFigure* getLineFigure() const;
        
        //! Returns the unique ID assigned to the newly created instance.
        /*!
         * Returns the unique ID assigned to the newly created instance. 
         * Overrides the NewObjectAdded::getUniqueId() method.
         *
         * \return A string.
         */
        virtual const string& getUniqueId() const;
        
        //! Returns the type of line announced by the current instance.
        /*!
         * Returns the type of line announced by the current instance.
         * 
         * \return The type of line.
         */
        const NewFigureAdded::FigureType getLineType() const;
        
    private:
        //! Stores a pointer to the line added to the diagram.
        LineFigure* _line;
        
        //! Stores a value indicating the type of Figure
        NewFigureAdded::FigureType _type;
        
        //! Stores the unique ID generated for this instance.
        const string _uniqueId;
    };
}

#endif /* NEWLINEADDED_H_ */
