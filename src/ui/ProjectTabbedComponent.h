/*!
 * \file ProjectTabbedComponent.h
 *
 * Contains the interface of the ui::ProjectTabbedComponent class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/26/08
 */

#ifndef PROJECTTABBEDCOMPONENT_H_
#define PROJECTTABBEDCOMPONENT_H_

#if defined(_WIN32)
#include <src/juce_WithoutMacros.h>
#else
#include <juce.h>
#endif

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * \class ProjectTabbedComponent
     *
     *  
     */
    class ProjectTabbedComponent : public TabbedComponent
    {
    public:

        /*!
         *  ProjectTabbedComponent constructor.
         */
        ProjectTabbedComponent();

        /*!
         *  ProjectTabbedComponent virtual destructor.
         */
        virtual ~ProjectTabbedComponent();
        
        virtual void currentTabChanged(const int, const String&);
        
        void postProjectTabbedComponentChangedTabNotification(const int, const String&);
    };
}

#endif /* PROJECTTABBEDCOMPONENT_H_ */
