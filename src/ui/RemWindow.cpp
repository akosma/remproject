/*!
 * \file RemWindow.cpp
 *
 * Contains the implementation of the ui::RemWindow class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/11/08
 */

#include "RemWindow.h"

#ifndef REMCONTENTCOMPONENT_H_
#include "RemContentComponent.h"
#endif

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * RemWindow Constructor.
     */
    RemWindow::RemWindow()
    : DocumentWindow (T("Rem"),
                      Colours::lightgrey, 
                      DocumentWindow::allButtons, 
                      true)
    {
        setContentComponent (new RemContentComponent());
        setVisible (true);
        centreWithSize (400, 200);
    }

    RemWindow::~RemWindow()
    {
    }

    void RemWindow::closeButtonPressed()
    {
        JUCEApplication::quit();
    }
}
