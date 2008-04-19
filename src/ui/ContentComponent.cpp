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

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    ContentComponent::ContentComponent()
	: _current(0)
    {
        Actor* a = new Actor(this);
        this->addAndMakeVisible(a, -1);
		a->setTopLeftPosition(10, 10);

        Actor* b = new Actor(this);
        this->addAndMakeVisible(b, -1);
		b->setTopLeftPosition(100, 100);
    }

    ContentComponent::~ContentComponent()
    {
        this->deleteAllChildren();
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
        _current->setCurrent(true);
    }
}
