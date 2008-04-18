/*!
 * \file Actor.h
 *
 * Contains the interface of the ui::Actor class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/17/08
 */

#include "juce.h"

#ifndef ACTOR_H_
#define ACTOR_H_

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    class ContentComponent;

    /*!
     * \class Actor
     *
     *  
     */
    class Actor : public Component
    {
    public:
        Actor(ContentComponent*);
        ~Actor();

        void paint (Graphics&);
        
        void mouseDown(const MouseEvent& e);
        void mouseDrag(const MouseEvent& e);
        virtual void resized();
        
        void setCurrent(bool);

    private:
        bool _current;
        ComponentDragger _dragger;
        ResizableBorderComponent* _resizer;
        ContentComponent* _parent;
        const int _initWidth;
        const int _initHeight;
        const float _margin;
        const float _strokeWidth;
    };
}

#endif /* ACTOR_H_ */
