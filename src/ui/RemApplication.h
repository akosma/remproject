/*!
 * \file RemApplication.h
 *
 * Contains the interface of the ui::RemApplication class.
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

#ifndef REMAPPLICATION_H_
#define REMAPPLICATION_H_

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    class RemWindow;

    /*!
     * \class RemApplication
     *
     *  
     */
    class RemApplication : public JUCEApplication
    {
    public:
        RemApplication();

        ~RemApplication();
        
        void initialise (const String&);

        void shutdown();

        const String getApplicationName();

        const String getApplicationVersion();

        bool moreThanOneInstanceAllowed();

        void anotherInstanceStarted (const String&);

    private:
        RemWindow* window;
    };
}

#endif /* REMAPPLICATION_H_ */
