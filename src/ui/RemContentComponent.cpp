/*!
 * \file RemContentComponent.cpp
 *
 * Contains the implementation of the ui::RemContentComponent class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/11/08
 */

#include "RemContentComponent.h"

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    RemContentComponent::RemContentComponent()
    {
    }

    RemContentComponent::~RemContentComponent()
    {
    }

    void RemContentComponent::paint (Graphics& g)
    {
        g.fillAll (Colours::white);
        g.setColour (Colours::black);
        g.setFont (20.0f, Font::bold);
        g.drawText (T("Rem"),
                    0, 0, getWidth(), getHeight(),
                    Justification::centred, false);
    }
}
