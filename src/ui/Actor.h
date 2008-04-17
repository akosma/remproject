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
    /*!
     * \class Actor
     *
     *  
     */
    class Actor : public Component
    {
    public:
        Actor();
        ~Actor();

        void paint (Graphics&);
        
        void mouseDown(const MouseEvent& e);
        void mouseDrag(const MouseEvent& e);
        
    private:
        ComponentDragger _dragger;
    };
}

#endif /* ACTOR_H_ */
