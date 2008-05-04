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

/*!
 * \file ToolboxItemFactory.cpp
 *
 * Contains the implementation of the ui::ToolboxItemFactory class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/26/08
 */

#include "ToolboxItemFactory.h"

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * ToolboxItemFactory Constructor.
     */
    ToolboxItemFactory::ToolboxItemFactory()
    {
    }
    
    /*!
     * ToolboxItemFactory Virtual destructor.
     */
    ToolboxItemFactory::~ToolboxItemFactory()
    {
    }

    void ToolboxItemFactory::getAllToolbarItemIds(Array<int>& ids)
    {
        ids.add(arrow);
        ids.add(actor);
        ids.add(use_case);
    }
    
    void ToolboxItemFactory::getDefaultItemSet(Array<int>& ids)
    {
        ids.add(arrow);
        ids.add(actor);
        ids.add(use_case);
    }
    
    ToolbarItemComponent* ToolboxItemFactory::createItem(const int itemId)
    {
        Font font("Helvetica", 12.0, 0);
        ToolbarItemComponent* component = NULL;
        // The brackets for the 'case' statements are required as explained here:
        // http://theory.uwinnipeg.ca/gnu/libg++/g++FAQ_42.html
        switch (itemId)
        {
        case arrow:
        {
            DrawableText* text1 = new DrawableText();
            text1->setColour(Colours::black);
            text1->setText("arrow", font);
            component = new ToolbarButton(arrow, "arrow", text1, text1);
            component->setBounds(0, 0, 50, 50);
        }
        case actor:
        {
            DrawableText* text2 = new DrawableText();
            text2->setColour(Colours::black);
            text2->setText("actor", font);
            component = new ToolbarButton(actor, "actor", text2, text2);
            component->setBounds(0, 50, 50, 50);
        }
        case use_case:
        {
            DrawableText* text3 = new DrawableText();
            text3->setColour(Colours::black);
            text3->setText("use case", font);
            component = new ToolbarButton(use_case, "use case", text3, text3);
            component->setBounds(0, 100, 50, 50);
        }
        default:
            break;
        }
        return component;
    }
}
