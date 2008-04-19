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
    : Figure(parent)
    , _initWidth(80)
    , _initHeight(200)
    , _margin(10.0f)
    , _strokeWidth(1.0f)
    , _nameLabel(0)
    {
        setSize(_initWidth, _initHeight);
        setBounds(0, 0, _initWidth, _initHeight);

        _nameLabel = new Label("NameLabel", "test");
        this->addAndMakeVisible(_nameLabel, 0);
        _nameLabel->setJustificationType(Justification::horizontallyCentred);
        _nameLabel->setTopLeftPosition(0, _initHeight - 30);
        _nameLabel->setSize(_initWidth, 30);
        _nameLabel->setEditable	(false, true, false);
    }

    Actor::~Actor()
    {
    }
    
    void Actor::drawFigure(Graphics& g)
    {
		Colour transparentWhite = Colours::white.withAlpha(0.9f);
		g.fillAll(transparentWhite);
        g.setColour(Colours::black);
        
        const int currentWidth = getWidth();
        const int currentHeight = getHeight();
        
        const int horizMargin = currentWidth * _margin / _initWidth;
        const int vertMargin = currentHeight * _margin / _initHeight;
        
        const float headWidth = currentWidth * 35.0f / _initWidth;
		const float headHeight = currentHeight * 35.0f / _initHeight;
        const float bodyLength = currentHeight * 80.0f / _initHeight;
        const float legHeight = currentHeight * 50.0f / _initHeight;
        const float armHeight = currentHeight * 30.0f / _initHeight;
        const float extremityWidth = currentWidth * 30.0f / _initWidth;
        const float neckLength = currentHeight * 10.0f / _initHeight;

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
        
        Path actor;

        // add an ellipse as well, which will form a second sub-path within the path..
        actor.addEllipse(headStartX, headStartY, headWidth, headHeight);
        actor.addLineSegment(bodyX, bodyStartY, bodyX, bodyEndY, _strokeWidth);       // body

        actor.addLineSegment(leftHandX, leftHandY, bodyX, shoulderY, _strokeWidth);   // left arm
        actor.addLineSegment(rightHandX, rightHandY, bodyX, shoulderY, _strokeWidth); // right arm

        actor.addLineSegment(leftFootX, leftFootY, bodyX, bodyEndY, _strokeWidth);    // left leg
        actor.addLineSegment(rightFootX, rightFootY, bodyX, bodyEndY, _strokeWidth);  // right leg

        // and draw it to a graphics context with a 5-pixel thick outline.
        g.strokePath (actor, PathStrokeType (4.0f));
    }
}
