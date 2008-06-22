/*!
 * \file FigureMovedNotification.h
 *
 * Contains the interface of the ui::FigureMovedNotification class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/22/08
 */

#ifndef FIGUREMOVEDNOTIFICATION_H_
#define FIGUREMOVEDNOTIFICATION_H_

#include <Poco/Notification.h>

using Poco::Notification;

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    class Figure;

    /*!
     * \class FigureMovedNotification
     *
     *  
     */
    class FigureMovedNotification : public Notification
    {
    public:

        /*!
         *  FigureMovedNotification constructor.
         */
        FigureMovedNotification(Figure*);

        /*!
         *  FigureMovedNotification virtual destructor.
         */
        virtual ~FigureMovedNotification();
        
        Figure* getMovedFigure() const;

    private:
        Figure* _figure;
    };
}

#endif /* FIGUREMOVEDNOTIFICATION_H_ */
