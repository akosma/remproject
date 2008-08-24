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

#ifndef ACTORTOOLBARBUTTON_H_
#include "ActorToolbarButton.h"
#endif

#ifndef USECASETOOLBARBUTTON_H_
#include "UseCaseToolbarButton.h"
#endif 

#ifndef LINETOOLBARBUTTON_H_
#include "LineToolbarButton.h"
#endif

#ifndef ARROWTOOLBARBUTTON_H_
#include "ArrowToolbarButton.h"
#endif

namespace ui
{
    UseCaseDiagramToolbar::UseCaseDiagramToolbar()
    : DiagramToolbar()
    {
        ActorToolbarButton* button = new ActorToolbarButton();
        button->setTopLeftPosition(10, 10);
        addAndMakeVisible(button, -1);

        UseCaseToolbarButton* button2 = new UseCaseToolbarButton();
        button2->setTopLeftPosition(10, 60);
        addAndMakeVisible(button2, -1);
        
        LineToolbarButton* button3 = new LineToolbarButton();
        button3->setTopLeftPosition(10, 110);
        addAndMakeVisible(button3, -1);
        
        ArrowToolbarButton* button4 = new ArrowToolbarButton();
        button4->setTopLeftPosition(10, 160);
        addAndMakeVisible(button4, -1);
    }

    UseCaseDiagramToolbar::~UseCaseDiagramToolbar()
    {
    }
}
