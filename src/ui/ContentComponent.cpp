/*!
 * \file ContentComponent.cpp
 *
 * Contains the implementation of the ui::ContentComponent class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/11/08
 */

#include "ContentComponent.h"

#ifndef ACTOR_H_
#include "Actor.h"
#endif

#ifndef USECASEBUBBLE_H_
#include "UseCaseBubble.h"
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
    ContentComponent::ContentComponent()
	: _current(0)
    {
        ArrowCanvas* ac = new ArrowCanvas(this);
        ac->setSize(800, 600);
        ac->setBounds(0, 0, 800, 600);
        addAndMakeVisible(ac, -1);
        
        Actor* a = new Actor(this);
        a->setTopLeftPosition(10, 10);
        addAndMakeVisible(a, -1);

        Actor* b = new Actor(this);
        b->setTopLeftPosition(100, 100);
        addAndMakeVisible(b, -1);
		
        UseCaseBubble* c = new UseCaseBubble(this);
        c->setTopLeftPosition(200, 200);
        addAndMakeVisible(c, -1);
    }

    ContentComponent::~ContentComponent()
    {
        deleteAllChildren();
    }

    void ContentComponent::mouseDown(const MouseEvent& e)
    {
        setCurrent(NULL);
    }
    
    void ContentComponent::paint (Graphics& g)
    {
        g.fillAll(Colours::white);
    }

    bool ContentComponent::isInterestedInDragSource (const String& sourceDescription)
    {
        // normally you'd check the sourceDescription value to see if it's the
        // sort of object that you're interested in before returning true, but for
        // the demo, we'll say yes to anything..
        return true;
    }

    void ContentComponent::itemDropped (const String& sourceDescription,
                          Component* sourceComponent,
                          int x, int y)
    {
        repaint();
    }
    
    void ContentComponent::setCurrent(Figure* current)
    {
        if (_current)
        {
            _current->setCurrent(false);
        }
        _current = current;
        if (_current)
        {
            _current->setCurrent(true);            
        }
    }
}
