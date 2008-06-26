/*!
 * \file ProjectTabbedComponent.cpp
 *
 * Contains the implementation of the ui::ProjectTabbedComponent class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/26/08
 */

#include <Poco/NotificationCenter.h>

#include "ProjectTabbedComponent.h"

#ifndef PROJECTTABBEDCOMPONENTCHANGEDTABNOTIFICATION_H_
#include "ProjectTabbedComponentChangedTabNotification.h"
#endif

using Poco::NotificationCenter;

namespace ui
{
    ProjectTabbedComponent::ProjectTabbedComponent()
    : TabbedComponent(TabbedButtonBar::TabsAtTop)
    {
    }
    
    ProjectTabbedComponent::~ProjectTabbedComponent()
    {
    }
    
    void ProjectTabbedComponent::currentTabChanged(const int newCurrentTabIndex, const String& newCurrentTabName)
    {
        postProjectTabbedComponentChangedTabNotification(newCurrentTabIndex, newCurrentTabName);
    }
    
    void ProjectTabbedComponent::postProjectTabbedComponentChangedTabNotification(const int newCurrentTabIndex, const String& newCurrentTabName)
    {
        ProjectTabbedComponentChangedTabNotification* notification = new ProjectTabbedComponentChangedTabNotification(newCurrentTabIndex, newCurrentTabName);
        NotificationCenter::defaultCenter().postNotification(notification);
    }
}
