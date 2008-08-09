/*!
 * \file SaveFile.h
 *
 * Contains the interface of the notifications::SaveFile class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      7/6/08
 */

#ifndef SAVEFILE_H_
#define SAVEFILE_H_

#include <Poco/Notification.h>

using Poco::Notification;

/*!
 * \namespace notifications
 * Insert a description for the namespace here
 */
namespace notifications
{
    /*!
     * \class SaveFile
     *
     *  
     */
    class SaveFile : public Notification
    {
    public:

        /*!
         *  SaveFile constructor.
         */
        SaveFile();

        /*!
         *  SaveFile virtual destructor.
         */
        virtual ~SaveFile();
    };
}

#endif /* SAVEFILE_H_ */
