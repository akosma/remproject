/*!
 * \file ContentComponent.h
 *
 * Contains the interface of the ui::ContentComponent class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/11/08
 */

#include "juce.h"

#ifndef CONTENTCOMPONENT_H_
#define CONTENTCOMPONENT_H_

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
     * \class ContentComponent
     *
     *  
     */
    class ContentComponent : public Component, public DragAndDropTarget
    {
    public:
        ContentComponent();
        ~ContentComponent();

        void paint (Graphics&);

        bool isInterestedInDragSource (const String& sourceDescription);

        void itemDropped (const String& sourceDescription,
                              Component* sourceComponent,
                              int x, int y);
                              
        void setCurrent(Figure*);
	
	private:
		Figure* _current;
    };
}

#endif /* CONTENTCOMPONENT_H_ */
