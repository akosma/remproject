/*!
 * \file Window.h
 *
 * Contains the interface of the ui::Window class.
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

#ifndef WINDOW_H_
#define WINDOW_H_

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * \class Window
     *
     *  
     */
    class Window  : public DocumentWindow
    {
    public:
        Window();
        ~Window();

        void closeButtonPressed();
    };
}

#endif /* WINDOW_H_ */
