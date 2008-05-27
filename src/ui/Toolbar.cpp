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

//! Contains the implementation of the ui::Toolbar class.
/*!
 * \file Toolbar.cpp
 *
 * Contains the implementation of the ui::Toolbar class.
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 *
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      27 May 2008 10:12:55 pm
 */

//[Headers] You can add your own extra header files here...
#include "ActorToolbarButton.h"
#include "UseCaseToolbarButton.h"
//[/Headers]

#include "Toolbar.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

namespace ui
{
    Toolbar::Toolbar ()
    {

        //[UserPreSize]
        //[/UserPreSize]

        setSize (60, 220);

        //[Constructor] You can add your own custom stuff here..
    ActorToolbarButton* button = new ActorToolbarButton();
    button->setTopLeftPosition(10, 10);
    addAndMakeVisible(button, -1);

    UseCaseToolbarButton* button2 = new UseCaseToolbarButton();
    button2->setTopLeftPosition(10, 60);
    addAndMakeVisible(button2, -1);
        //[/Constructor]
    }

    Toolbar::~Toolbar()
    {
        //[Destructor_pre]. You can add your own custom destruction code here..
        //[/Destructor_pre]



        //[Destructor]. You can add your own custom destruction code here..
        //[/Destructor]
    }

    //==============================================================================
    void Toolbar::paint (Graphics& g)
    {
        //[UserPrePaint] Add your own custom painting code here..
        //[/UserPrePaint]

        g.fillAll (Colours::white);

        g.setColour (Colour (0xd2ffffff));
        g.fillRect (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));

        g.setColour (Colours::black);
        g.drawRect (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f), 2);

        //[UserPaint] Add your own custom painting code here..
        //[/UserPaint]
    }

    void Toolbar::resized()
    {
        //[UserResized] Add your own custom resize handling here..
        //[/UserResized]
    }

}
//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Toolbar" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="60" initialHeight="220">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 0 100% 100%" fill="solid: d2ffffff" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ff000000"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
