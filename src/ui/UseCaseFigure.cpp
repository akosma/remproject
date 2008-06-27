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
 * \file UseCaseFigure.cpp
 *
 * Contains the implementation of the ui::UseCaseFigure class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/19/08
 */

#include "UseCaseFigure.h"

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * UseCaseFigure Constructor.
     */
    UseCaseFigure::UseCaseFigure()
    : Figure(200, 150)
    , _nameLabel(0)
    {
        const float margin = getInitialMargin();

        _nameLabel = new Label("NameLabel", "Name");
        _nameLabel->setJustificationType(Justification::horizontallyCentred);
        _nameLabel->setTopLeftPosition(20 + (int)margin, getInitialHeight() - 30);
        _nameLabel->setSize(getInitialWidth() - 40, 30);
        _nameLabel->setEditable(false, true, false);
        _nameLabel->setInterceptsMouseClicks(false, false);
        this->addAndMakeVisible(_nameLabel, 0);
    }
    
    void UseCaseFigure::mouseDoubleClick(const MouseEvent& e)
    {
        _nameLabel->showEditor();
    }
    
    /*!
     * UseCaseFigure Virtual destructor.
     */
    UseCaseFigure::~UseCaseFigure()
    {
    }

    void UseCaseFigure::drawFigure(Path& usecase)
    {
        const int currentWidth = getWidth();
        const int currentHeight = getHeight();

        const int initWidth = getInitialWidth();
        const int initHeight = getInitialHeight();
        const float margin = getInitialMargin();

        const int horizMargin = currentWidth * (int)margin / initWidth;
        const int vertMargin = currentHeight * (int)margin / initHeight;

        const float width = currentWidth * 180.0f / initWidth;
        const float height = currentHeight * 130.0f / initHeight;

        const float startX = horizMargin;
        const float startY = vertMargin;

        _nameLabel->setTopLeftPosition(20 + horizMargin, currentHeight / 2 - 15);
        _nameLabel->setSize(currentWidth - 40 - 2 * horizMargin, 30);

        usecase.addEllipse(startX, startY, width, height);
    }
}
