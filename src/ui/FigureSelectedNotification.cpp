/*!
 * \file FigureSelectedNotification.cpp
 *
 * Contains the implementation of the ui::FigureSelectedNotification class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/22/08
 */

#include "FigureSelectedNotification.h"

#ifndef FIGURE_H_
#include "Figure.h"
#endif

using Poco::Notification;

namespace ui
{
    FigureSelectedNotification::FigureSelectedNotification(Figure* figure)
    : Notification()
    , _figure(figure)
    {
    }
    
    FigureSelectedNotification::~FigureSelectedNotification()
    {
    }
    
    Figure* FigureSelectedNotification::getSelectedFigure() const
    {
        return _figure;
    }
}
