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

#ifndef CONTENTCOMPONENT_H_
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
        centreWithSize (800, 600);
        setResizable(true, true);

        this->setUsingNativeTitleBar(true);
#if JUCE_MAC
//        MenuBarModel::setMacMainMenu(this->getContentComponent());
//        mainWindow->setMenuBar (0);
#endif
    }

    Window::~Window()
    {
    }

    void Window::closeButtonPressed()
    {
        JUCEApplication::quit();
    }
}
