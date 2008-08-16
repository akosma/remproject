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

//! Contains the implementation of the ui::ActorFigure class.
/*!
 * \file ActorFigure.cpp
 *
 * Contains the implementation of the ui::ActorFigure class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/17/08
 */

#include "ActorFigure.h"

namespace ui
{
    ActorFigure::ActorFigure()
    : Figure(80, 200)
    , _nameLabel(0)
    {
        _nameLabel = new Label("NameLabel", "Name");
        this->addAndMakeVisible(_nameLabel, 0);
        _nameLabel->setJustificationType(Justification::horizontallyCentred);
        _nameLabel->setTopLeftPosition(0, getInitialHeight() - 30);
        _nameLabel->setSize(getInitialWidth(), 30);
        _nameLabel->setEditable(false, true, false);
        _nameLabel->setInterceptsMouseClicks(false, false);
    }

    ActorFigure::~ActorFigure()
    {
    }
    
    void ActorFigure::mouseDoubleClick(const MouseEvent& e)
    {
        _nameLabel->showEditor();
    }
    
    void ActorFigure::drawFigure(Path& actor)
    {
        const int currentWidth = getWidth();
        const int currentHeight = getHeight();
        
        const int initWidth = getInitialWidth();
        const int initHeight = getInitialHeight();
        const float margin = getInitialMargin();
        const float strokeWidth = getStrokeWidth();
        
        const int horizMargin = currentWidth * (int)margin / initWidth;
        const int vertMargin = currentHeight * (int)margin / initHeight;
        
        const float headWidth = currentWidth * 35.0f / initWidth;
        const float headHeight = currentHeight * 35.0f / initHeight;
        const float bodyLength = currentHeight * 80.0f / initHeight;
        const float legHeight = currentHeight * 50.0f / initHeight;
        const float armHeight = currentHeight * 30.0f / initHeight;
        const float extremityWidth = currentWidth * 30.0f / initWidth;
        const float neckLength = currentHeight * 10.0f / initHeight;

        const float bodyX = horizMargin + extremityWidth;
        const float bodyStartY = vertMargin + headHeight;
        const float bodyEndY = bodyStartY + bodyLength;

        const float headStartX = bodyX - (headWidth / 2);
        const float headStartY = (float)vertMargin;
        
        const float shoulderY = vertMargin + headHeight + neckLength;
        const float leftHandX = (float)horizMargin;
        const float leftHandY = shoulderY + armHeight;
        const float leftFootX = (float)horizMargin;
        const float leftFootY = bodyEndY + legHeight;
        const float rightFootX = horizMargin + (2 * extremityWidth);
        const float rightFootY = leftFootY;
        const float rightHandX = rightFootX;
        const float rightHandY = leftHandY;
        
        _nameLabel->setTopLeftPosition(0, currentHeight - 30);
        _nameLabel->setSize(currentWidth, 30);
        
        actor.addEllipse(headStartX, headStartY, headWidth, headHeight);
        actor.addLineSegment(bodyX, bodyStartY, bodyX, bodyEndY, strokeWidth);       // body

        actor.addLineSegment(leftHandX, leftHandY, bodyX, shoulderY, strokeWidth);   // left arm
        actor.addLineSegment(rightHandX, rightHandY, bodyX, shoulderY, strokeWidth); // right arm

        actor.addLineSegment(leftFootX, leftFootY, bodyX, bodyEndY, strokeWidth);    // left leg
        actor.addLineSegment(rightFootX, rightFootY, bodyX, bodyEndY, strokeWidth);  // right leg
    }
}
