/*!
 * \file ActiveWindowStatusChanged.h
 *
 * Contains the interface of the notifications::ActiveWindowStatusChanged class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      7/6/08
 */

#ifndef ACTIVEWINDOWSTATUSCHANGED_H_
#define ACTIVEWINDOWSTATUSCHANGED_H_

#include <Poco/Notification.h>

using Poco::Notification;

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace notifications
{
    /*!
     * \class ActiveWindowStatusChanged
     *
     *  
     */
    class ActiveWindowStatusChanged : public Notification
    {
    public:

        /*!
         *  ActiveWindowStatusChanged constructor.
         */
        ActiveWindowStatusChanged(const bool);

        /*!
         *  ActiveWindowStatusChanged virtual destructor.
         */
        virtual ~ActiveWindowStatusChanged();
        
        const bool getStatus() const;
        
    private:
        bool _status;
    };
}

#endif /* ACTIVEWINDOWSTATUSCHANGED_H_ */
