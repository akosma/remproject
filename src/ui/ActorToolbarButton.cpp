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

//! Contains the implementation of the ui::ActorToolbarButton class.
/*!
 * \file ActorToolbarButton.cpp
 *
 * Contains the implementation of the ui::ActorToolbarButton class.
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 *
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      27 May 2008 10:26:34 pm
 */

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "ActorToolbarButton.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

namespace ui
{
    ActorToolbarButton::ActorToolbarButton ()
        : Button (String::empty)
    {

        //[UserPreSize]
        //[/UserPreSize]

        setSize (40, 40);

        //[Constructor] You can add your own custom stuff here..
        //[/Constructor]
    }

    ActorToolbarButton::~ActorToolbarButton()
    {
        //[Destructor_pre]. You can add your own custom destruction code here..
        //[/Destructor_pre]



        //[Destructor]. You can add your own custom destruction code here..
        //[/Destructor]
    }

    void ActorToolbarButton::resized()
    {
        internalPath1.clear();
        internalPath1.startNewSubPath (11.0f, 35.0f);
        internalPath1.lineTo (19.0f, 25.0f);
        internalPath1.lineTo (29.0f, 35.0f);

        internalPath2.clear();
        internalPath2.startNewSubPath (11.0f, 35.0f);
        internalPath2.lineTo (19.0f, 25.0f);
        internalPath2.lineTo (29.0f, 35.0f);

        //[UserResized] Add your own custom resize handling here..
        //[/UserResized]
    }

    void ActorToolbarButton::paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown)
    {
        if (isButtonDown || isMouseOverButton)
        {
            g.setColour (Colours::white);
            g.fillRoundedRectangle (1.0f, 1.0f, 38.0f, 38.0f, 10.0000f);

            g.setColour (Colour (0xff2a6ba5));
            g.drawRoundedRectangle (1.0f, 1.0f, 38.0f, 38.0f, 10.0000f, 1.0000f);

            g.setColour (Colour (0xff2a6ba5));
            g.fillEllipse (13.0f, 3.0f, 13.0f, 11.0f);

            g.setColour (Colour (0xff2a6ba5));
            g.fillRect (18, 9, 3, 18);

            g.setColour (Colour (0xff2a6ba5));
            g.strokePath (internalPath2, PathStrokeType (2.9000f));

            g.setColour (Colour (0xff2a6ba5));
            g.fillRect (8, 17, 24, 3);
        }
        else
        {
            g.setColour (Colours::white);
            g.fillRoundedRectangle (1.0f, 1.0f, 38.0f, 38.0f, 10.0000f);

            g.setColour (Colours::black);
            g.drawRoundedRectangle (1.0f, 1.0f, 38.0f, 38.0f, 10.0000f, 1.0000f);

            g.setColour (Colours::black);
            g.fillEllipse (13.0f, 3.0f, 13.0f, 11.0f);

            g.setColour (Colours::black);
            g.fillRect (18, 9, 3, 18);

            g.setColour (Colours::black);
            g.strokePath (internalPath1, PathStrokeType (2.9000f));

            g.setColour (Colours::black);
            g.fillRect (8, 17, 24, 3);
        }
    }

}
//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Button" className="ActorToolbarButton" componentName=""
                 parentClasses="public Button" constructorParams="" variableInitialisers=""
                 snapPixels="4" snapActive="0" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="40" initialHeight="40">
  <BACKGROUND backgroundColour="0" buttonState="normal" enabled="1">
    <ROUNDRECT pos="1 1 38 38" cornerSize="10" fill="solid: ffffffff" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ff000000"/>
    <ELLIPSE pos="13 3 13 11" fill="solid: ff000000" hasStroke="0"/>
    <RECT pos="18 9 3 18" fill="solid: ff000000" hasStroke="0"/>
    <PATH pos="0 0 100 100" fill="solid: ffffff" hasStroke="1" stroke="2.9000001, mitered, butt"
          strokeColour="solid: ff000000" nonZeroWinding="1">s 11 35 l 19 25 l 29 35</PATH>
    <RECT pos="8 17 24 3" fill="solid: ff000000" hasStroke="0"/>
  </BACKGROUND>
  <BACKGROUND backgroundColour="0" buttonState="over" enabled="1">
    <ROUNDRECT pos="1 1 38 38" cornerSize="10" fill="solid: ffffffff" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ff2a6ba5"/>
    <ELLIPSE pos="13 3 13 11" fill="solid: ff2a6ba5" hasStroke="0"/>
    <RECT pos="18 9 3 18" fill="solid: ff2a6ba5" hasStroke="0"/>
    <PATH pos="0 0 100 100" fill="solid: ffffff" hasStroke="1" stroke="2.9000001, mitered, butt"
          strokeColour="solid: ff2a6ba5" nonZeroWinding="1">s 11 35 l 19 25 l 29 35</PATH>
    <RECT pos="8 17 24 3" fill="solid: ff2a6ba5" hasStroke="0"/>
  </BACKGROUND>
  <BACKGROUND backgroundColour="0" buttonState="down" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="normal on" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="over on" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="down on" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="common background" enabled="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
