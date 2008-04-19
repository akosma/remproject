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

#ifndef FIGURE_H_
#include "Figure.h"
#endif

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
    class Actor : public Figure
    {
    public:
        Actor(ContentComponent*);
        ~Actor();

    protected:
        virtual void drawFigure(Graphics&);

    private:
        const int _initWidth;
        const int _initHeight;
        const float _margin;
        const float _strokeWidth;
        Label* _nameLabel;
    };
}

#endif /* ACTOR_H_ */
