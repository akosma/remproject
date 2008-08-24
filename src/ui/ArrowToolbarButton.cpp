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

//! Contains the implementation of the ui::ArrowToolbarButton class.
/*!
 * \file ArrowToolbarButton.cpp
 *
 * Contains the implementation of the ui::ArrowToolbarButton class.
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 *
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      16 Aug 2008 5:12:18 pm
 */

#include "ArrowToolbarButton.h"

#ifndef COMMANDDELEGATE_H_
#include "CommandDelegate.h"
#endif

namespace ui
{
    ArrowToolbarButton::ArrowToolbarButton ()
    : Button (String::empty)
    {
        setSize (40, 40);
    }

    ArrowToolbarButton::~ArrowToolbarButton()
    {
    }

    const String ArrowToolbarButton::getTooltip()
    {
        return String("To create an arrow, select two actors.");
    }

    void ArrowToolbarButton::paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown)
    {
        Path internalPath2;
        Path internalPath3;
        Path internalPath5;
        Path internalPath6;

        internalPath2.clear();
        internalPath2.startNewSubPath (24.0f, 8.0f);
        internalPath2.lineTo (32.0f, 8.0f);
        internalPath2.lineTo (32.0f, 16.0f);
        internalPath2.closeSubPath();

        internalPath3.clear();
        internalPath3.startNewSubPath (32.0f, 8.0f);
        internalPath3.lineTo (8.0f, 32.0f);
        internalPath3.closeSubPath();

        internalPath5.clear();
        internalPath5.startNewSubPath (24.0f, 8.0f);
        internalPath5.lineTo (32.0f, 8.0f);
        internalPath5.lineTo (32.0f, 16.0f);
        internalPath5.closeSubPath();

        internalPath6.clear();
        internalPath6.startNewSubPath (32.0f, 8.0f);
        internalPath6.lineTo (8.0f, 32.0f);
        internalPath6.closeSubPath();

        if (isButtonDown)
        {
            GradientBrush gradient_4 (Colours::black,
                                      20.0f, 19.0f,
                                      Colours::white,
                                      20.0f, 1.0f,
                                      false);
            g.setBrush (&gradient_4);
            g.fillRoundedRectangle (1.0f, 1.0f, 38.0f, 38.0f, 6.0000f);

            g.setColour (Colours::white);
            g.drawRoundedRectangle (1.0f, 1.0f, 38.0f, 38.0f, 6.0000f, 0.6000f);

            g.setColour (Colours::white);
            g.fillPath (internalPath5);

            g.setColour (Colours::white);
            g.fillPath (internalPath6);
            g.setColour (Colours::white);
            g.strokePath (internalPath6, PathStrokeType (2.3000f));
        }
        else
        {
            GradientBrush gradient_1 (Colours::black,
                                      20.0f, 13.0f,
                                      Colours::white,
                                      20.0f, 1.0f,
                                      false);
            g.setBrush (&gradient_1);
            g.fillRoundedRectangle (1.0f, 1.0f, 38.0f, 38.0f, 6.0000f);

            g.setColour (Colours::white);
            g.drawRoundedRectangle (1.0f, 1.0f, 38.0f, 38.0f, 6.0000f, 0.6000f);

            g.setColour (Colours::white);
            g.fillPath (internalPath2);

            g.setColour (Colours::white);
            g.fillPath (internalPath3);
            g.setColour (Colours::white);
            g.strokePath (internalPath3, PathStrokeType (2.3000f));
        }
    }

    void ArrowToolbarButton::clicked()
    {
        CommandDelegate::get().invokeDirectly(CommandDelegate::diagramAddArrow, false);
    }
}
