/*!
 * \file Application.h
 *
 * Contains the interface of the ui::Application class.
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

#ifndef APPLICATION_H_
#define APPLICATION_H_

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    class Window;

    /*!
     * \class Application
     *
     *  
     */
    class Application : public JUCEApplication
    {
    public:
        Application();

        ~Application();
        
        void initialise (const String&);

        void shutdown();

        const String getApplicationName();

        const String getApplicationVersion();

        bool moreThanOneInstanceAllowed();

        void anotherInstanceStarted (const String&);

    private:
        Window* window;
    };
}

#endif /* APPLICATION_H_ */
