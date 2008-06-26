/*!
 * \file ProjectTabbedComponentChangedTabNotification.cpp
 *
 * Contains the implementation of the ui::ProjectTabbedComponentChangedTabNotification class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/26/08
 */

#include "ProjectTabbedComponentChangedTabNotification.h"

namespace ui
{
    ProjectTabbedComponentChangedTabNotification::ProjectTabbedComponentChangedTabNotification(const int newCurrentTabIndex, const String& newCurrentTabName)
    : Notification()
    , _newCurrentTabIndex(newCurrentTabIndex)
    , _newCurrentTabName(newCurrentTabName)
    {
    }
    
    ProjectTabbedComponentChangedTabNotification::~ProjectTabbedComponentChangedTabNotification()
    {
    }
    
    const int ProjectTabbedComponentChangedTabNotification::getNewCurrentTabIndex() const
    {
        return _newCurrentTabIndex;
    }

    const String ProjectTabbedComponentChangedTabNotification::getNewCurrentTabName() const
    {
        return _newCurrentTabName;
    }
}
