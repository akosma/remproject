/*!
 * \file ExportDiagramAsPNG.h
 *
 * Contains the interface of the notifications::ExportDiagramAsPNG class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      7/6/08
 */

#ifndef EXPORTDIAGRAMASPNG_H_
#define EXPORTDIAGRAMASPNG_H_

#include <Poco/Notification.h>

using Poco::Notification;

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace notifications
{
    /*!
     * \class ExportDiagramAsPNG
     *
     *  
     */
    class ExportDiagramAsPNG : public Notification
    {
    public:

        /*!
         *  ExportDiagramAsPNG constructor.
         */
        ExportDiagramAsPNG();

        /*!
         *  ExportDiagramAsPNG virtual destructor.
         */
        virtual ~ExportDiagramAsPNG();
    };
}

#endif /* EXPORTDIAGRAMASPNG_H_ */
