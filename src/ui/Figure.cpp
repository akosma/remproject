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

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * Figure Constructor.
     */
    Figure::Figure(ContentComponent* parent)
    : _current(false)
    , _dragger()
    , _resizer(0)
    , _parent(parent)
    {
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
    }

    void Figure::mouseDrag(const MouseEvent& e)
    {
        _dragger.dragComponent(this, e);
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
    
    void Figure::setCurrent(bool current)
    {
        _resizer->setVisible(current);
        _current = current;
		repaint();
    }
    
    void Figure::paint(Graphics& g)
    {
        this->drawFigure(g);

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
