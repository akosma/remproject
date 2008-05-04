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
 * \file UseCaseBubble.h
 *
 * Contains the interface of the ui::UseCaseBubble class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/19/08
 */

#ifndef USECASEBUBBLE_H_
#define USECASEBUBBLE_H_

#ifndef FIGURE_H_
#include "Figure.h"
#endif

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * \class UseCaseBubble
     *
     *  
     */
    class UseCaseBubble : public Figure
    {
    public:

        /*!
         *  UseCaseBubble constructor.
         */
        UseCaseBubble(ContentComponent*);

        /*!
         *  UseCaseBubble virtual destructor.
         */
        virtual ~UseCaseBubble();

        void mouseDoubleClick(const MouseEvent& e);
    
    protected:
        virtual void drawFigure(Path&);

    private:
        Label* _nameLabel;
    };
}

#endif /* USECASEBUBBLE_H_ */
