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
    Actor::Actor()
    : _dragger()
    {
        setBounds (0, 0, 80, 175);
    }

    Actor::~Actor()
    {
    }
    
    void Actor::mouseDown(const MouseEvent& e)
    {
        _dragger.startDraggingComponent(this, 0);
    }

    void Actor::mouseDrag(const MouseEvent& e)
    {
        _dragger.dragComponent(this, e);
    }
    
    void Actor::paint (Graphics& g)
    {
        g.setColour (Colours::black);
        
        const float topMargin = 10.0f;
        const float leftMargin = 10.0f;
        const float strokeWidth = 1.0f;
        
        const float headWidth = 35.0f;
        const float bodyLength = 80.0f;
        const float legHeight = 50.0f;
        const float armHeight = 30.0f;
        const float extremityWidth = 30.0f;
        const float neckLength = 10.0f;

        const float bodyX = leftMargin + extremityWidth;
        const float bodyStartY = topMargin + headWidth;
        const float bodyEndY = bodyStartY + bodyLength;

        const float headStartX = bodyX - (headWidth / 2);
        const float headStartY = topMargin;
        
        const float shoulderY = topMargin + headWidth + neckLength;
        const float leftHandX = leftMargin;
        const float leftHandY = shoulderY + armHeight;
        const float leftFootX = leftMargin;
        const float leftFootY = bodyEndY + legHeight;
        const float rightFootX = leftMargin + (2 * extremityWidth);
        const float rightFootY = leftFootY;
        const float rightHandX = rightFootX;
        const float rightHandY = leftHandY;
        
        Path myPath;

        // add an ellipse as well, which will form a second sub-path within the path..
        myPath.addEllipse(headStartX, headStartY, headWidth, headWidth);
        myPath.addLineSegment(bodyX, bodyStartY, bodyX, bodyEndY, strokeWidth);       // body

        myPath.addLineSegment(leftHandX, leftHandY, bodyX, shoulderY, strokeWidth);   // left arm
        myPath.addLineSegment(rightHandX, rightHandY, bodyX, shoulderY, strokeWidth); // right arm

        myPath.addLineSegment(leftFootX, leftFootY, bodyX, bodyEndY, strokeWidth);    // left leg
        myPath.addLineSegment(rightFootX, rightFootY, bodyX, bodyEndY, strokeWidth);  // right leg

        // and draw it to a graphics context with a 5-pixel thick outline.
        g.strokePath (myPath, PathStrokeType (4.0f));
    }
}
