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

//! Contains the interface of the ui::LineToolbarButton class.
/*!
 * \file LineToolbarButton.cpp
 *
 * Contains the interface of the ui::LineToolbarButton class.
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 *
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      16 Aug 2008 5:12:21 pm
 */

#ifndef __JUCER_HEADER_LINEFIGUREBUTTON_LINEFIGUREBUTTON_8E1BB03A__
#define __JUCER_HEADER_LINEFIGUREBUTTON_LINEFIGUREBUTTON_8E1BB03A__

#include "PlatformDefinitions.h"

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    /*!
     * \class LineToolbarButton
     *
     */
    class LineToolbarButton  : public Button
    {
    public:
        LineToolbarButton ();
        ~LineToolbarButton();

        void resized();
        void paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown);
        void clicked();

    private:
        Path internalPath2;
        Path internalPath4;

        LineToolbarButton (const LineToolbarButton&);
        const LineToolbarButton& operator= (const LineToolbarButton&);
    };
}

#endif   // __JUCER_HEADER_LINEFIGUREBUTTON_LINEFIGUREBUTTON_8E1BB03A__
