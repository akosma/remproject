/*!
 * \file FigureSelectedNotification.h
 *
 * Contains the interface of the ui::FigureSelectedNotification class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/22/08
 */

#ifndef FIGURESELECTEDNOTIFICATION_H_
#define FIGURESELECTEDNOTIFICATION_H_

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
     * \class FigureSelectedNotification
     *
     *  
     */
    class FigureSelectedNotification : public Notification
    {
    public:

        /*!
         *  FigureSelectedNotification constructor.
         */
        FigureSelectedNotification(Figure*);

        /*!
         *  FigureSelectedNotification virtual destructor.
         */
        virtual ~FigureSelectedNotification();
        
        Figure* getSelectedFigure() const;
        
    private:
        Figure* _figure;
    };
}

#endif /* FIGURESELECTEDNOTIFICATION_H_ */
