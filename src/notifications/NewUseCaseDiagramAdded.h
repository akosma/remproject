/*!
 * \file NewUseCaseDiagramAdded.h
 *
 * Contains the interface of the notifications::NewUseCaseDiagramAdded class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      7/6/08
 */

#ifndef NEWUSECASEDIAGRAMADDED_H_
#define NEWUSECASEDIAGRAMADDED_H_

#include <Poco/Notification.h>

using Poco::Notification;

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace notifications
{
    /*!
     * \class NewUseCaseDiagramAdded
     *
     *  
     */
    class NewUseCaseDiagramAdded : public Notification
    {
    public:

        /*!
         *  NewUseCaseDiagramAdded constructor.
         */
        NewUseCaseDiagramAdded();

        /*!
         *  NewUseCaseDiagramAdded virtual destructor.
         */
        virtual ~NewUseCaseDiagramAdded();
    };
}

#endif /* NEWUSECASEDIAGRAMADDED_H_ */
