/*!
 * \file ArrowCanvasClickedNotification.cpp
 *
 * Contains the implementation of the ui::ArrowCanvasClickedNotification class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/22/08
 */

#include "ArrowCanvasClickedNotification.h"

#ifndef ARROWCANVAS_H_
#include "ArrowCanvas.h"
#endif

namespace ui
{
    ArrowCanvasClickedNotification::ArrowCanvasClickedNotification(ArrowCanvas* canvas)
    : Notification()
    , _arrowCanvas(canvas)
    {
    }
    
    ArrowCanvasClickedNotification::~ArrowCanvasClickedNotification()
    {
    }
    
    ArrowCanvas* ArrowCanvasClickedNotification::getClickedArrowCanvas() const
    {
        return _arrowCanvas;
    }
}
