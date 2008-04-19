/*!
 * \file Figure.h
 *
 * Contains the interface of the ui::Figure class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/19/08
 */

#include "juce.h"

#ifndef FIGURE_H_
#define FIGURE_H_

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    class ContentComponent;
    
    /*!
     * \class Figure
     *
     *  
     */
    class Figure : public Component
    {
    public:
        /*!
         *  Figure constructor.
         */
        Figure(ContentComponent*, const int, const int);

        /*!
         *  Figure virtual destructor.
         */
        virtual ~Figure();

        void paint(Graphics&);
        
        void mouseDown(const MouseEvent& e);
        void mouseDrag(const MouseEvent& e);
        void resized();
        
        void setCurrent(bool);

    protected:
        virtual void drawFigure(Path&) = 0;
        
        const int getInitialWidth();
        const int getInitialHeight();
        const float getInitialMargin();
        const float getStrokeWidth();

    private:
        bool _current;
        ComponentDragger _dragger;
        ResizableBorderComponent* _resizer;
        ContentComponent* _parent;
        const int _initWidth;
        const int _initHeight;
        const float _initMargin;
        const float _strokeWidth;
    };
}

#endif /* FIGURE_H_ */
