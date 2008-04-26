/*!
 * \file ToolboxItemFactory.h
 *
 * Contains the interface of the ui::ToolboxItemFactory class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/26/08
 */

#include "juce.h"

#ifndef TOOLBOXITEMFACTORY_H_
#define TOOLBOXITEMFACTORY_H_

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * \class ToolboxItemFactory
     *
     *  
     */
    class ToolboxItemFactory : public ToolbarItemFactory
    {
    public:
        
        enum ToolbarItemIds
        {
            arrow = 1,
            actor = 2,
            use_case = 3
        };

        /*!
         *  ToolboxItemFactory constructor.
         */
        ToolboxItemFactory();

        /*!
         *  ToolboxItemFactory virtual destructor.
         */
        virtual ~ToolboxItemFactory();
        
        virtual void getAllToolbarItemIds(Array<int>&);
        virtual void getDefaultItemSet(Array<int>&);
        virtual ToolbarItemComponent* createItem(const int);
    };
}

#endif /* TOOLBOXITEMFACTORY_H_ */
