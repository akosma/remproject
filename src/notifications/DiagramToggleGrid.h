/*!
 * \file DiagramToggleGrid.h
 *
 * Contains the interface of the notifications::DiagramToggleGrid class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      7/6/08
 */

#ifndef DIAGRAMTOGGLEGRID_H_
#define DIAGRAMTOGGLEGRID_H_

#include <Poco/Notification.h>

using Poco::Notification;

/*!
 * \namespace notifications
 * Insert a description for the namespace here
 */
namespace notifications
{
    /*!
     * \class DiagramToggleGrid
     *
     *  
     */
    class DiagramToggleGrid : public Notification
    {
    public:

        /*!
         *  DiagramToggleGrid constructor.
         */
        DiagramToggleGrid();

        /*!
         *  DiagramToggleGrid virtual destructor.
         */
        virtual ~DiagramToggleGrid();
    };
}

#endif /* DIAGRAMTOGGLEGRID_H_ */
