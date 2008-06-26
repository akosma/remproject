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

//! Contains the implementation of the ui::UseCaseDiagramToolbar class.
/*!
 * \file Toolbar.cpp
 *
 * Contains the implementation of the ui::UseCaseDiagramToolbar class.
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 *
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      21 Jun 2008 4:48:24 pm
 */

#include "UseCaseDiagramToolbar.h"

#include "ActorToolbarButton.h"
#include "UseCaseToolbarButton.h"

namespace ui
{
    UseCaseDiagramToolbar::UseCaseDiagramToolbar ()
    : Component()
    , _dragger()
    {
        setSize (60, 220);

        ActorToolbarButton* button = new ActorToolbarButton();
        button->setTopLeftPosition(10, 10);
        addAndMakeVisible(button, -1);

        UseCaseToolbarButton* button2 = new UseCaseToolbarButton();
        button2->setTopLeftPosition(10, 60);
        addAndMakeVisible(button2, -1);
    }

    UseCaseDiagramToolbar::~UseCaseDiagramToolbar()
    {
    }

    void UseCaseDiagramToolbar::mouseDown(const MouseEvent& e)
    {
        _dragger.startDraggingComponent(this, 0);
        setMouseCursor(MouseCursor(MouseCursor::DraggingHandCursor));
    }

    void UseCaseDiagramToolbar::mouseDrag(const MouseEvent& e)
    {
        _dragger.dragComponent(this, e);
    }

    void UseCaseDiagramToolbar::paint (Graphics& g)
    {
        g.setColour (Colour (0xffe2e2e2));
        g.fillRoundedRectangle (0.0f, 0.0f, (float) (getWidth() - 0), (float) (getHeight() - 0), 6.0000f);
    }

    void UseCaseDiagramToolbar::resized()
    {
    }

}
