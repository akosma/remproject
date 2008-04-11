/*!
 * \file RemContentComponent.h
 *
 * Contains the interface of the ui::RemContentComponent class.
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

#ifndef REMCONTENTCOMPONENT_H_
#define REMCONTENTCOMPONENT_H_

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * \class RemContentComponent
     *
     *  
     */
    class RemContentComponent : public Component
    {
    public:
        RemContentComponent();
        ~RemContentComponent();

        void paint (Graphics&);
    };
}

#endif /* REMCONTENTCOMPONENT_H_ */
