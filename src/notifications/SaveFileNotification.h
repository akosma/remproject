/*!
 * \file SaveFileNotification.h
 *
 * Contains the interface of the notifications::SaveFileNotification class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      7/6/08
 */

#ifndef SAVEFILENOTIFICATION_H_
#define SAVEFILENOTIFICATION_H_

#include <Poco/Notification.h>

using Poco::Notification;

/*!
 * \namespace notifications
 * Insert a description for the namespace here
 */
namespace notifications
{
    /*!
     * \class SaveFileNotification
     *
     *  
     */
    class SaveFileNotification : public Notification
    {
    public:

        /*!
         *  SaveFileNotification constructor.
         */
        SaveFileNotification();

        /*!
         *  SaveFileNotification virtual destructor.
         */
        virtual ~SaveFileNotification();
    };
}

#endif /* SAVEFILENOTIFICATION_H_ */
