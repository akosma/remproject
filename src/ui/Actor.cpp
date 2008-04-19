/*!
 * \file Actor.cpp
 *
 * Contains the implementation of the ui::Actor class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/17/08
 */

#include "Actor.h"

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    Actor::Actor(ContentComponent* parent)
    : Figure(parent, 80, 200)
    , _nameLabel(0)
    {
        _nameLabel = new Label("NameLabel", "Name");
        this->addAndMakeVisible(_nameLabel, 0);
        _nameLabel->setJustificationType(Justification::horizontallyCentred);
        _nameLabel->setTopLeftPosition(0, getInitialHeight() - 30);
        _nameLabel->setSize(getInitialWidth(), 30);
        _nameLabel->setEditable(false, true, false);
    }

    Actor::~Actor()
    {
    }
    
    void Actor::drawFigure(Path& actor)
    {
        const int currentWidth = getWidth();
        const int currentHeight = getHeight();
        
        const int initWidth = getInitialWidth();
        const int initHeight = getInitialHeight();
        const float margin = getInitialMargin();
        const float strokeWidth = getStrokeWidth();
        
        const int horizMargin = currentWidth * margin / initWidth;
        const int vertMargin = currentHeight * margin / initHeight;
        
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
        const float headStartY = vertMargin;
        
        const float shoulderY = vertMargin + headHeight + neckLength;
        const float leftHandX = horizMargin;
        const float leftHandY = shoulderY + armHeight;
        const float leftFootX = horizMargin;
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
