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
    class ContentComponent : public Component
    {
    public:
        ContentComponent();
        ~ContentComponent();

        void paint (Graphics&);
    };
}

#endif /* CONTENTCOMPONENT_H_ */
