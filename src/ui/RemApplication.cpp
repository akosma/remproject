/*!
 * \file RemApplication.cpp
 *
 * Contains the implementation of the ui::RemApplication class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/11/08
 */

#include "RemApplication.h"

#ifndef REMWINDOW_H_
#include "RemWindow.h"
#endif

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    RemApplication::RemApplication()
    : window(0)
    {
    }

    RemApplication::~RemApplication()
    {
    }

    void RemApplication::initialise (const String& commandLine)
    {
        window = new RemWindow();
    }

    void RemApplication::shutdown()
    {
        // clear up..

        if (window != 0)
            delete window;
    }

    const String RemApplication::getApplicationName()
    {
        return T("Rem Application");
    }

    const String RemApplication::getApplicationVersion()
    {
        return T("1.0");
    }

    bool RemApplication::moreThanOneInstanceAllowed()
    {
        return true;
    }

    void RemApplication::anotherInstanceStarted (const String& commandLine)
    {
    }
}
