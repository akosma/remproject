/*!
 * \file ProjectTabbedComponentChangedTabNotification.h
 *
 * Contains the interface of the ui::ProjectTabbedComponentChangedTabNotification class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/26/08
 */

#ifndef PROJECTTABBEDCOMPONENTCHANGEDTABNOTIFICATION_H_
#define PROJECTTABBEDCOMPONENTCHANGEDTABNOTIFICATION_H_

#include <Poco/Notification.h>

#if defined(_WIN32)
#include <src/juce_WithoutMacros.h>
#else
#include <juce.h>
#endif

using Poco::Notification;

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * \class ProjectTabbedComponentChangedTabNotification
     *
     *  
     */
    class ProjectTabbedComponentChangedTabNotification : public Notification
    {
    public:

        /*!
         *  ProjectTabbedComponentChangedTabNotification constructor.
         */
        ProjectTabbedComponentChangedTabNotification(const int, const String&);

        /*!
         *  ProjectTabbedComponentChangedTabNotification virtual destructor.
         */
        virtual ~ProjectTabbedComponentChangedTabNotification();

        const int getNewCurrentTabIndex() const;
        const String getNewCurrentTabName() const;
        
    private:
        
        const int _newCurrentTabIndex;
        const String _newCurrentTabName;

    };
}

#endif /* PROJECTTABBEDCOMPONENTCHANGEDTABNOTIFICATION_H_ */
