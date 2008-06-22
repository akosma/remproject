/*!
 * \file ArrowCanvasClickedNotification.h
 *
 * Contains the interface of the ui::ArrowCanvasClickedNotification class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/22/08
 */

#ifndef ARROWCANVASCLICKEDNOTIFICATION_H_
#define ARROWCANVASCLICKEDNOTIFICATION_H_

#include <Poco/Notification.h>

using Poco::Notification;

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    class ArrowCanvas;
    
    /*!
     * \class ArrowCanvasClickedNotification
     *
     *  
     */
    class ArrowCanvasClickedNotification : public Notification
    {
    public:

        /*!
         *  ArrowCanvasClickedNotification constructor.
         */
        ArrowCanvasClickedNotification(ArrowCanvas*);

        /*!
         *  ArrowCanvasClickedNotification virtual destructor.
         */
        virtual ~ArrowCanvasClickedNotification();
        
        ArrowCanvas* getClickedArrowCanvas() const;
    
    private:
        ArrowCanvas* _arrowCanvas;
    };
}

#endif /* ARROWCANVASCLICKEDNOTIFICATION_H_ */
