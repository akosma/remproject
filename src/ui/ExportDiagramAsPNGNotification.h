/*!
 * \file ExportDiagramAsPNGNotification.h
 *
 * Contains the interface of the ui::ExportDiagramAsPNGNotification class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      7/6/08
 */

#ifndef EXPORTDIAGRAMASPNGNOTIFICATION_H_
#define EXPORTDIAGRAMASPNGNOTIFICATION_H_

#include <Poco/Notification.h>

using Poco::Notification;

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * \class ExportDiagramAsPNGNotification
     *
     *  
     */
    class ExportDiagramAsPNGNotification : public Notification
    {
    public:

        /*!
         *  ExportDiagramAsPNGNotification constructor.
         */
        ExportDiagramAsPNGNotification();

        /*!
         *  ExportDiagramAsPNGNotification virtual destructor.
         */
        virtual ~ExportDiagramAsPNGNotification();
    };
}

#endif /* EXPORTDIAGRAMASPNGNOTIFICATION_H_ */
