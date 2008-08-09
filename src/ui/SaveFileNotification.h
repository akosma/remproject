/*!
 * \file SaveFileNotification.h
 *
 * Contains the interface of the ui::SaveFileNotification class.
 * 
 * $LastChangedDate: 2008-07-06 15:52:13 +0200 (Sun, 06 Jul 2008) $
 * $LastChangedBy: akosma $
 * $HeadURL: https://remproject.googlecode.com/svn/trunk/src/ui/SaveFileNotification.h $
 * 
 * \version   $LastChangedRevision: 198 $
 * \author    Adrian
 * \date      7/6/08
 */

#ifndef SAVEFILENOTIFICATION_H_
#define SAVEFILENOTIFICATION_H_

#include <Poco/Notification.h>

using Poco::Notification;

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
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
