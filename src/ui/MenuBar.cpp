/*
 * Rem - Requirements and Entity Modeler = UML + AOP + Open Source + Cross Platform
 * Copyright (C) 2008 Adrian Kosmaczewski - http://remproject.org/
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

//! Contains the implementation of the ui::MenuBar class.
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
    , _owner(owner)
    {
    }
    
    MenuBar::~MenuBar()
    {
        // Do not "delete window" here, since this instance does not own it.
    }
    
    const StringArray MenuBar::getMenuBarNames()
    {
        const char* const names[] = {"File", "Edit", "Project", "Diagram", "Help", 0};
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
                menu.addCommandItem(manager, CommandDelegate::fileOpen);

                menu.addSeparator();
                menu.addCommandItem(manager, CommandDelegate::fileSave);
                menu.addCommandItem(manager, CommandDelegate::fileSaveAs);
                menu.addSeparator();
                menu.addCommandItem(manager, CommandDelegate::fileExportPNG);
#if JUCE_WIN32 || JUCE_LINUX
                // In Mac OS X, the "Quit" menu item is located in the
                // "Rem" menu, generated automatically by Juce during build.
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
                menu.addCommandItem (manager, CommandDelegate::editDelete);
                break;
            }
            
            case 2:
            {
                // "Project" menu items
                menu.addCommandItem(manager, CommandDelegate::projectNewUseCaseDiagram);
                menu.addCommandItem(manager, CommandDelegate::projectNewClassDiagram);
                menu.addCommandItem(manager, CommandDelegate::projectNewSequenceDiagram);
                break;
            }

            case 3:
            {
                // "Diagram" menu items
                menu.addCommandItem(manager, CommandDelegate::diagramAddActor);
                menu.addCommandItem(manager, CommandDelegate::diagramAddUseCase);
                menu.addCommandItem(manager, CommandDelegate::diagramAddLine);
                menu.addCommandItem(manager, CommandDelegate::diagramAddArrow);
                menu.addSeparator();
                menu.addCommandItem(manager, CommandDelegate::diagramToggleGrid);
                break;
            }

            case 4:
            {
                // "Help" menu items
                menu.addCommandItem(manager, CommandDelegate::helpAbout);
                break;
            }
        }
        return menu;
    }
}
