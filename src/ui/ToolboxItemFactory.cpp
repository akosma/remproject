/*!
 * \file ToolboxItemFactory.cpp
 *
 * Contains the implementation of the rem::ToolboxItemFactory class.
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
 * \namespace rem
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
        switch (itemId)
        {
        case arrow:
            DrawableText* text1 = new DrawableText();
            text1->setColour(Colours::black);
            text1->setText("arrow", font);
            ToolbarButton* button1 = new ToolbarButton(arrow, "arrow", text1, text1);
            button1->setBounds(0, 0, 50, 50);
            return button1;

        case actor:
            DrawableText* text2 = new DrawableText();
            text2->setColour(Colours::black);
            text2->setText("actor", font);
            ToolbarButton* button2 = new ToolbarButton(actor, "actor", text2, text2);
            button2->setBounds(0, 50, 50, 50);
            return button2;

        case use_case:
            DrawableText* text3 = new DrawableText();
            text3->setColour(Colours::black);
            text3->setText("use case", font);
            ToolbarButton* button3 = new ToolbarButton(use_case, "use case", text3, text3);
            button3->setBounds(0, 100, 50, 50);
            return button3;

        default:
            break;
        }
        return NULL;
    }
}
