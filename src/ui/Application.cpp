/*!
 * \file Application.cpp
 *
 * Contains the implementation of the ui::Application class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/11/08
 */

#include "Application.h"

#ifndef WINDOW_H_
#include "Window.h"
#endif

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    Application::Application()
    : window(0)
    {
    }

    Application::~Application()
    {
    }

    void Application::initialise (const String& commandLine)
    {
        window = new Window();
    }

    void Application::shutdown()
    {
        delete window;
    }

    const String Application::getApplicationName()
    {
        return T("Rem Application");
    }

    const String Application::getApplicationVersion()
    {
        return T("1.0");
    }

    bool Application::moreThanOneInstanceAllowed()
    {
        return true;
    }

    void Application::anotherInstanceStarted (const String& commandLine)
    {
    }
}
