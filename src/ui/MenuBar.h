/*!
 * \file MenuBar.h
 *
 * Contains the interface of the ui::MenuBar class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      7/3/08
 */

#include "PlatformDefinitions.h"

#ifndef MENUBAR_H_
#define MENUBAR_H_

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    class Window;
    /*!
     * \class MenuBar
     *
     *  
     */
    class MenuBar : public MenuBarModel
    {
    public:

        /*!
         *  MenuBar constructor.
         */
        MenuBar(Window*);

        /*!
         *  MenuBar virtual destructor.
         */
        virtual ~MenuBar();
        
        virtual const StringArray getMenuBarNames();
        
        virtual void menuItemSelected(int, int);
        
        virtual const PopupMenu getMenuForIndex(int, const String&);

    private:
        ApplicationCommandManager* _manager;
        Window* _owner;

    };
}

#endif /* MENUBAR_H_ */
