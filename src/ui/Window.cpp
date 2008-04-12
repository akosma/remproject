/*!
 * \file Window.cpp
 *
 * Contains the implementation of the ui::Window class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/11/08
 */

#include "Window.h"

#ifndef REMCONTENTCOMPONENT_H_
#include "ContentComponent.h"
#endif

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * Window Constructor.
     */
    Window::Window()
    : DocumentWindow (T("Rem"),
                      Colours::lightgrey, 
                      DocumentWindow::allButtons, 
                      true)
    {
        setContentComponent (new ContentComponent());
        setVisible (true);
        centreWithSize (400, 200);
    }

    Window::~Window()
    {
    }

    void Window::closeButtonPressed()
    {
        JUCEApplication::quit();
    }
}
