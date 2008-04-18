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

#ifndef CONTENTCOMPONENT_H_
#include "ContentComponent.h"
#endif

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    Actor::Actor(ContentComponent* parent)
    : _current(false)
    , _dragger()
    , _resizer(0)
    , _parent(parent)
    , _initWidth(80)
    , _initHeight(185)
    , _margin(10.0f)
    , _strokeWidth(1.0f)
    {
        setBounds(0, 0, _initWidth, _initHeight);
        _resizer = new ResizableBorderComponent(this, 0);
        _resizer->setSize(getWidth(),getHeight());
        _resizer->setBounds(0, 0, getWidth(), getHeight());
        this->addAndMakeVisible(_resizer, -1);
        setRepaintsOnMouseActivity(true);
        setBroughtToFrontOnMouseClick(true);
        setBufferedToImage(true);
    }

    Actor::~Actor()
    {
        delete _resizer;
    }
    
    void Actor::mouseDown(const MouseEvent& e)
    {
		this->toFront(true);
		_parent->setCurrent(this);
        _dragger.startDraggingComponent(this, 0);
    }

    void Actor::mouseDrag(const MouseEvent& e)
    {
        _dragger.dragComponent(this, e);
    }
    
    void Actor::resized()
    {
        if (_resizer)
        {
			this->toFront(true);
			_parent->setCurrent(this);
            _resizer->setBounds (0,0,getWidth(),getHeight());
        }
    }
    
    void Actor::setCurrent(bool current)
    {
        _current = current;
		repaint();
    }
    
    void Actor::paint (Graphics& g)
    {
		Colour transparentWhite = Colours::white.withAlpha(0.9f);
		g.fillAll(transparentWhite);
        g.setColour(Colours::black);
        
        const int currentWidth = getWidth();
        const int currentHeight = getHeight();
        
        const float headWidth = currentWidth * 35.0f / _initWidth;
		const float headHeight = currentHeight * 35.0f / _initHeight;
        const float bodyLength = currentHeight * 80.0f / _initHeight;
        const float legHeight = currentHeight * 50.0f / _initHeight;
        const float armHeight = currentHeight * 30.0f / _initHeight;
        const float extremityWidth = currentWidth * 30.0f / _initWidth;
        const float neckLength = currentHeight * 10.0f / _initHeight;

        const float bodyX = _margin + extremityWidth;
        const float bodyStartY = _margin + headHeight;
        const float bodyEndY = bodyStartY + bodyLength;

        const float headStartX = bodyX - (headWidth / 2);
        const float headStartY = _margin;
        
        const float shoulderY = _margin + headHeight + neckLength;
        const float leftHandX = _margin;
        const float leftHandY = shoulderY + armHeight;
        const float leftFootX = _margin;
        const float leftFootY = bodyEndY + legHeight;
        const float rightFootX = _margin + (2 * extremityWidth);
        const float rightFootY = leftFootY;
        const float rightHandX = rightFootX;
        const float rightHandY = leftHandY;
        
        Path myPath;

        // add an ellipse as well, which will form a second sub-path within the path..
        myPath.addEllipse(headStartX, headStartY, headWidth, headHeight);
        myPath.addLineSegment(bodyX, bodyStartY, bodyX, bodyEndY, _strokeWidth);       // body

        myPath.addLineSegment(leftHandX, leftHandY, bodyX, shoulderY, _strokeWidth);   // left arm
        myPath.addLineSegment(rightHandX, rightHandY, bodyX, shoulderY, _strokeWidth); // right arm

        myPath.addLineSegment(leftFootX, leftFootY, bodyX, bodyEndY, _strokeWidth);    // left leg
        myPath.addLineSegment(rightFootX, rightFootY, bodyX, bodyEndY, _strokeWidth);  // right leg

        // and draw it to a graphics context with a 5-pixel thick outline.
        g.strokePath (myPath, PathStrokeType (4.0f));

        if (_current)
        {
            // This will create a dashed rectangle around the selected element
			const float dashLengths[] = { 5.0F, 5.0F };
			g.drawDashedLine(0, 0, 0, getHeight(), dashLengths, 2, 2.0f);
			g.drawDashedLine(0, 0, getWidth(), 0, dashLengths, 2, 2.0f);
			g.drawDashedLine(getWidth(), 0, getWidth(), getHeight(), dashLengths, 2, 2.0f);
			g.drawDashedLine(0, getHeight(), getWidth(), getHeight(), dashLengths, 2, 2.0f);
        }
    }
}
