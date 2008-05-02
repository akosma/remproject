/*!
 * \file Figure.cpp
 *
 * Contains the implementation of the ui::Figure class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/19/08
 */

#include "Figure.h"

#ifndef CONTENTCOMPONENT_H_
#include "ContentComponent.h"
#endif

#ifndef ARROWCANVAS_H_
#include "ArrowCanvas.h"
#endif

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * Figure Constructor.
     */
    Figure::Figure(ContentComponent* parent, const int initWidth, const int initHeight)
    : _current(false)
    , _hover(false)
    , _dragger()
    , _resizer(0)
    , _parent(parent)
    , _initWidth(initWidth)
    , _initHeight(initHeight)
    , _initMargin(10.0f)
    , _strokeWidth(1.0f)
    {
        setSize(_initWidth, _initHeight);
        setBounds(0, 0, _initWidth, _initHeight);
        setRepaintsOnMouseActivity(true);
        setBroughtToFrontOnMouseClick(true);
        setBufferedToImage(true);

        _resizer = new ResizableBorderComponent(this, 0);
        this->addChildComponent(_resizer, -1);
        _resizer->setSize(getWidth(),getHeight());
        _resizer->setBounds(0, 0, getWidth(), getHeight());
    }
    
    /*!
     * Figure Virtual destructor.
     */
    Figure::~Figure()
    {
        this->deleteAllChildren();
    }

    void Figure::mouseDown(const MouseEvent& e)
    {
        this->toFront(true);
        _parent->setCurrent(this);
        _dragger.startDraggingComponent(this, 0);
        setMouseCursor(MouseCursor(MouseCursor::DraggingHandCursor));
    }
    
    void Figure::mouseUp(const MouseEvent& e)
    {
        setMouseCursor(MouseCursor(MouseCursor::NormalCursor));
    }

    void Figure::mouseDrag(const MouseEvent& e)
    {
        _dragger.dragComponent(this, e);
        _parent->getArrowCanvas().repaint();
    }
    
    void Figure::mouseEnter(const MouseEvent& e)
    {
        _hover = true;
    }
    
    void Figure::mouseExit(const MouseEvent& e)
    {
        _hover = false;
    }
    
    void Figure::resized()
    {
        // Somehow resized() is called before _resizer is constructed!
        if (_parent && _resizer)
        {
            this->toFront(true);
            _parent->setCurrent(this);
            _resizer->setBounds (0,0,getWidth(),getHeight());
        }
    }
    
    const int Figure::getInitialWidth()
    {
        return _initWidth;
    }
    
    const int Figure::getInitialHeight()
    {
        return _initHeight;
    }
    
    const float Figure::getInitialMargin()
    {
        return _initMargin;
    }
    
    const float Figure::getStrokeWidth()
    {
        return _strokeWidth;
    }

    void Figure::setCurrent(bool current)
    {
        _resizer->setVisible(current);
        _current = current;
        repaint();
    }
    
    const Point* Figure::getAnchorPointRelativeTo(const Figure* other) const
    {
        const bool isBelow = (other->getY() + other->getHeight()) < this->getY();
        const bool isAbove = (this->getY() + this->getHeight()) < other->getY();
        const bool isRightOf = (other->getX() + other->getWidth()) < this->getX();
        const bool isLeftOf = (this->getX() + this->getWidth()) < other->getX();
        
        Point* point;
        
        if (isBelow)
        {
            point = new Point(getX() + getWidth() / 2, getY());
        }
        
        if (isAbove)
        {
            point = new Point(getX() + getWidth() / 2, getY() + getHeight());
        }
        
        if (isRightOf)
        {
            point = new Point(getX(), getY() + getHeight() / 2);
        }

        if (isLeftOf)
        {
            point = new Point(getX() + getWidth(), getY() + getHeight() / 2);
        }
        return point;
    }
    
    void Figure::paint(Graphics& g)
    {
        Colour transparentWhite = Colours::white.withAlpha(0.9f);
        Path figure;
        this->drawFigure(figure);
        if (_current)
        {
            g.fillAll(transparentWhite);

            // This will create a dashed rectangle around the selected element
            drawDashedLineAround(g);
        }
        else
        {
            if (_hover)
            {
                setMouseCursor(MouseCursor(MouseCursor::PointingHandCursor));
                g.setColour(Colours::lightgrey);
                drawDashedLineAround(g);
            }
        }
        g.setColour(Colours::black);
        g.strokePath (figure, PathStrokeType (4.0f));
    }

    void Figure::drawDashedLineAround(Graphics& g)
    {
        const float dashLengths[] = { 5.0F, 5.0F };
        g.drawDashedLine(0, 0, 0, getHeight(), dashLengths, 2, 2.0f);
        g.drawDashedLine(0, 0, getWidth(), 0, dashLengths, 2, 2.0f);
        g.drawDashedLine(getWidth(), 0, getWidth(), getHeight(), dashLengths, 2, 2.0f);
        g.drawDashedLine(0, getHeight(), getWidth(), getHeight(), dashLengths, 2, 2.0f);
    }
}
