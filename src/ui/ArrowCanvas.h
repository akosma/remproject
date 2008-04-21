/*!
 * \file ArrowCanvas.h
 *
 * Contains the interface of the ui::ArrowCanvas class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/21/08
 */

#include "juce.h"

#ifndef ARROWCANVAS_H_
#define ARROWCANVAS_H_

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    class ContentComponent;
    
    /*!
     * \class ArrowCanvas
     *
     *  
     */
    class ArrowCanvas : public Component
    {
    public:
        /*!
         *  ArrowCanvas constructor.
         */
        ArrowCanvas(ContentComponent*);

        /*!
         *  ArrowCanvas virtual destructor.
         */
        virtual ~ArrowCanvas();

        void paint(Graphics&);

    private:
        ContentComponent* _parent;
        const float _strokeWidth;
    };
}

#endif /* ARROWCANVAS_H_ */
