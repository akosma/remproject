/*!
 * \file MenuBar.cpp
 *
 * Contains the implementation of the ui::MenuBar class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      7/3/08
 */

#include "MenuBar.h"

#ifndef COMMANDDELEGATE_H_
#include "CommandDelegate.h"
#endif

#ifndef WINDOW_H_
#include "Window.h"
#endif

namespace ui
{
    MenuBar::MenuBar(Window* owner)
    : MenuBarModel()
    , _manager(NULL)
    , _owner(owner)
    {
    }
    
    MenuBar::~MenuBar()
    {
        // Do not "delete _manager" or "window" here, since this instance does not own them.
    }
    
    const StringArray MenuBar::getMenuBarNames()
    {
        const char* const names[] = {"File", "Edit", "Project", "Diagram", "Element", "Window", "Help", 0};
        return StringArray((const char**)names);
    }
    
    void MenuBar::menuItemSelected(int menuItemID, int topLevelMenuIndex)
    {
        // Here we are invoking menus as commands, so we leave this method alone 
        // (however, it must be present for the application to compile, since this
        // is a pure virtual method on the abstract base class)
    }
    
    const PopupMenu MenuBar::getMenuForIndex(int index, const String &menuName)
    {
        PopupMenu menu;
        ApplicationCommandManager* manager = _owner->getCommandManager();
        
        switch (index)
        {
            case 0:
            {
                // "File" menu items
                menu.addCommandItem(manager, CommandDelegate::fileNewProject);

                PopupMenu diagramSubMenu;
                diagramSubMenu.addCommandItem(manager, CommandDelegate::fileNewUseCaseDiagram);
                diagramSubMenu.addCommandItem(manager, CommandDelegate::fileNewClassDiagram);
                diagramSubMenu.addCommandItem(manager, CommandDelegate::fileNewSequenceDiagram);
                menu.addSubMenu("Add New Diagram", diagramSubMenu, true, NULL);

                menu.addCommandItem(manager, CommandDelegate::fileOpen);

                menu.addSeparator();
                menu.addCommandItem(manager, CommandDelegate::fileClose);
                menu.addCommandItem(manager, CommandDelegate::fileSave);
                menu.addCommandItem(manager, CommandDelegate::fileSaveAs);
#if JUCE_WIN32 || JUCE_LINUX
                menu.addSeparator();
                menu.addCommandItem(manager, CommandDelegate::fileQuit);
#endif
                break;
            }
            
            case 1:
            {
                // "Edit" menu items
                menu.addItem (10, "Undo");
                menu.addSeparator();
                menu.addItem (11, "Cut");
                menu.addItem (12, "Copy");
                menu.addItem (13, "Paste");
                menu.addSeparator();
                menu.addItem (14, "Delete");
                break;
            }
            
            case 2:
            {
                // "Project" menu items
                menu.addItem (20, "Item 1");
                menu.addItem (21, "Item 2");
                menu.addSeparator();
                menu.addItem (22, "Item 3");
                menu.addItem (23, "Item 4");
                menu.addItem (24, "Item 5");
                break;
            }

            case 3:
            {
                // "Diagram" menu items
                menu.addItem (30, "Item 1");
                menu.addItem (31, "Item 2");
                menu.addItem (32, "Item 3");
                menu.addItem (33, "Item 4");
                break;
            }

            case 4:
            {
                // "Element" menu items
                menu.addItem (40, "Item 1");
                menu.addSeparator();
                menu.addItem (41, "Item 2");
                menu.addItem (42, "Item 3");
                break;
            }

            case 5:
            {
                // "Window" menu items
                menu.addItem (50, "Minimize");
                break;
            }

            case 6:
            {
                // "Help" menu items
                menu.addItem (60, "About");
                break;
            }
        }
        return menu;
    }
}