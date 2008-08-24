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

//! Contains the implementation of the ui::UseCaseToolbarButton class.
/*!
 * \file UseCaseToolbarButton.cpp
 *
 * Contains the implementation of the ui::UseCaseToolbarButton class.
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 *
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      21 Jun 2008 4:46:22 pm
 */

#include "UseCaseToolbarButton.h"

#ifndef COMMANDDELEGATE_H_
#include "CommandDelegate.h"
#endif

namespace ui
{
    UseCaseToolbarButton::UseCaseToolbarButton ()
    : Button (String::empty)
    {
        setSize (40, 40);
    }

    UseCaseToolbarButton::~UseCaseToolbarButton()
    {
    }

    const String UseCaseToolbarButton::getTooltip()
    {
        return String("Click to add an use case bubble to the diagram.");
    }

    void UseCaseToolbarButton::paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown)
    {
        if (isButtonDown)
        {
            GradientBrush gradient_2 (Colours::black,
                                      20.0f, 19.0f,
                                      Colours::white,
                                      20.0f, 1.0f,
                                      false);
            g.setBrush (&gradient_2);
            g.fillRoundedRectangle (1.0f, 1.0f, 38.0f, 38.0f, 6.0000f);

            g.setColour (Colours::white);
            g.drawRoundedRectangle (1.0f, 1.0f, 38.0f, 38.0f, 6.0000f, 0.6000f);

            g.setColour (Colours::black);
            g.fillEllipse (10.0f, 12.0f, 21.0f, 15.0f);

            g.setColour (Colours::white);
            g.drawEllipse (10.0f, 12.0f, 21.0f, 15.0f, 2.0000f);
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

            g.setColour (Colours::black);
            g.fillEllipse (10.0f, 12.0f, 21.0f, 15.0f);

            g.setColour (Colours::white);
            g.drawEllipse (10.0f, 12.0f, 21.0f, 15.0f, 2.0000f);
        }
    }

    void UseCaseToolbarButton::clicked()
    {
        CommandDelegate::get().invokeDirectly(CommandDelegate::diagramAddUseCase, false);
    }

}
