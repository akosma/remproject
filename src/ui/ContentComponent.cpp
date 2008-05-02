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

#include <iostream>

#ifndef ACTOR_H_
#include "Actor.h"
#endif

#ifndef USECASEBUBBLE_H_
#include "UseCaseBubble.h"
#endif

#ifndef ARROWCANVAS_H_
#include "ArrowCanvas.h"
#endif

#ifndef TOOLBOX_H_
#include "Toolbox.h"
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
        _canvas = new ArrowCanvas(this);
        _canvas->setSize(800, 600);
        _canvas->setBounds(0, 0, 800, 600);
        addAndMakeVisible(_canvas, 0);
        
        Actor* a = new Actor(this);
        a->setTopLeftPosition(100, 300);
        addAndMakeVisible(a, -1);

        Actor* b = new Actor(this);
        b->setTopLeftPosition(100, 10);
        addAndMakeVisible(b, -1);
        
        UseCaseBubble* c = new UseCaseBubble(this);
        c->setTopLeftPosition(400, 300);
        addAndMakeVisible(c, -1);
        
        Toolbox* t = new Toolbox(this);
        addAndMakeVisible(t, -1);
        
        _canvas->addArrow(a, c);
        _canvas->addArrow(a, b);
    }

    ContentComponent::~ContentComponent()
    {
        deleteAllChildren();
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
            _canvas->setNoCurrentArrow();
        }
    }
    
    ArrowCanvas& ContentComponent::getArrowCanvas()
    {
        return *_canvas;
    }
}
