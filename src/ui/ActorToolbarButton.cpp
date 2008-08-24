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

//! Contains the implementation of the ui::ActorToolbarButton class.
/*!
 * \file ActorToolbarButton.cpp
 *
 * Contains the implementation of the ui::ActorToolbarButton class.
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 *
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      16 Aug 2008 3:51:59 pm
 */

#include "ActorToolbarButton.h"

#ifndef COMMANDDELEGATE_H_
#include "CommandDelegate.h"
#endif

namespace ui
{
    ActorToolbarButton::ActorToolbarButton ()
    :Button (String::empty)
    {
        setSize (40, 40);
    }

    const String ActorToolbarButton::getTooltip()
    {
        return String("Click to add an actor to the diagram.");
    }

    ActorToolbarButton::~ActorToolbarButton()
    {
    }

    void ActorToolbarButton::paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown)
    {
        Path internalPath2;
        Path internalPath3;
        Path internalPath5;
        Path internalPath6;
        
        internalPath2.clear();
        internalPath2.startNewSubPath (11.0f, 36.0f);
        internalPath2.lineTo (19.0f, 26.0f);
        internalPath2.lineTo (29.0f, 36.0f);

        internalPath3.clear();
        internalPath3.startNewSubPath (11.0f, 26.0f);
        internalPath3.lineTo (19.0f, 16.0f);
        internalPath3.lineTo (29.0f, 26.0f);

        internalPath5.clear();
        internalPath5.startNewSubPath (11.0f, 36.0f);
        internalPath5.lineTo (19.0f, 26.0f);
        internalPath5.lineTo (29.0f, 36.0f);

        internalPath6.clear();
        internalPath6.startNewSubPath (11.0f, 26.0f);
        internalPath6.lineTo (19.0f, 16.0f);
        internalPath6.lineTo (29.0f, 26.0f);

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
            g.fillRect (18, 13, 3, 15);

            g.setColour (Colours::white);
            g.strokePath (internalPath5, PathStrokeType (2.9000f));

            g.setColour (Colours::white);
            g.drawEllipse (13.0f, 3.0f, 13.0f, 11.0f, 2.5000f);

            g.setColour (Colours::white);
            g.strokePath (internalPath6, PathStrokeType (2.9000f));
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
            g.fillRect (18, 13, 3, 15);

            g.setColour (Colours::white);
            g.strokePath (internalPath2, PathStrokeType (2.9000f));

            g.setColour (Colours::white);
            g.drawEllipse (13.0f, 3.0f, 13.0f, 11.0f, 2.5000f);

            g.setColour (Colours::white);
            g.strokePath (internalPath3, PathStrokeType (2.9000f));
        }
    }

    void ActorToolbarButton::clicked()
    {
        CommandDelegate::get().invokeDirectly(CommandDelegate::diagramAddActor, false);
    }
}
