/*!
 * \file RemWindow.h
 *
 * Contains the interface of the rem::RemWindow class.
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

#ifndef REMWINDOW_H_
#define REMWINDOW_H_

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * \class RemWindow
     *
     *  
     */
    class RemWindow  : public DocumentWindow
    {
    public:
        RemWindow();
        ~RemWindow();

        void closeButtonPressed();
    };
}

#endif /* REMWINDOW_H_ */
