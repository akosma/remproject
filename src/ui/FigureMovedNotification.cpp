/*!
 * \file FigureMovedNotification.cpp
 *
 * Contains the implementation of the ui::FigureMovedNotification class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/22/08
 */

#include "FigureMovedNotification.h"

#ifndef FIGURE_H_
#include "Figure.h"
#endif

using Poco::Notification;

namespace ui
{
    FigureMovedNotification::FigureMovedNotification(Figure* figure)
    : Notification()
    , _figure(figure)
    {
    }
    
    FigureMovedNotification::~FigureMovedNotification()
    {
    }

    Figure* FigureMovedNotification::getMovedFigure() const
    {
        return _figure;
    }
}
