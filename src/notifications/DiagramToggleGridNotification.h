/*!
 * \file DiagramToggleGridNotification.h
 *
 * Contains the interface of the notifications::DiagramToggleGridNotification class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      7/6/08
 */

#ifndef DIAGRAMTOGGLEGRIDNOTIFICATION_H_
#define DIAGRAMTOGGLEGRIDNOTIFICATION_H_

#include <Poco/Notification.h>

using Poco::Notification;

/*!
 * \namespace notifications
 * Insert a description for the namespace here
 */
namespace notifications
{
    /*!
     * \class DiagramToggleGridNotification
     *
     *  
     */
    class DiagramToggleGridNotification : public Notification
    {
    public:

        /*!
         *  DiagramToggleGridNotification constructor.
         */
        DiagramToggleGridNotification();

        /*!
         *  DiagramToggleGridNotification virtual destructor.
         */
        virtual ~DiagramToggleGridNotification();
    };
}

#endif /* rem_DiagramToggleGridNotification */
