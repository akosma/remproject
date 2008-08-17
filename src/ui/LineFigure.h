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
    /*!
     * \class LineFigure
     *
     *  
     */
    class LineFigure : public Figure
    {
    public:
        LineFigure(const string&);
        virtual ~LineFigure();
        
    protected:
        virtual void drawFigure(Path&);
    };
}

#endif /* LINEFIGURE_H_ */
