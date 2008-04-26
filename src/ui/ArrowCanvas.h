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

#include <vector>

#ifndef ARROWCANVAS_H_
#define ARROWCANVAS_H_

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    class ContentComponent;
    class Figure;
    
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

        void mouseDown(const MouseEvent&);
        void paint(Graphics&);
        void setNoCurrentArrow();
        
        void addArrow(Figure*, Figure*);

    private:
        class Arrow
        {
        public:
            Arrow(Figure*, Figure*);
            Arrow(const Arrow&);
            Arrow& operator=(const Arrow&);
            virtual ~Arrow();
            const Figure* getStartFigure() const;
            const Figure* getEndFigure() const;
            const bool intercepts(const MouseEvent&);

        private:
            Figure* _start;
            Figure* _end;
        };

    private:
        ContentComponent* _parent;
        const float _strokeWidth;
        std::vector<Arrow*> _arrows;
        Arrow* _currentArrow;
    };
}

#endif /* ARROWCANVAS_H_ */
