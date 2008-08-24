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

//! Contains the implementation of the ui::ArrowToolbarButton class.
/*!
 * \file ArrowToolbarButton.cpp
 *
 * Contains the implementation of the ui::ArrowToolbarButton class.
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 *
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      16 Aug 2008 5:12:18 pm
 */

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "ArrowToolbarButton.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#ifndef COMMANDDELEGATE_H_
#include "CommandDelegate.h"
#endif
//[/MiscUserDefs]

namespace ui
{
    ArrowToolbarButton::ArrowToolbarButton ()
        : Button (String::empty)
    {

        //[UserPreSize]
        //[/UserPreSize]

        setSize (40, 40);

        //[Constructor] You can add your own custom stuff here..
        //[/Constructor]
    }

    ArrowToolbarButton::~ArrowToolbarButton()
    {
        //[Destructor_pre]. You can add your own custom destruction code here..
        //[/Destructor_pre]



        //[Destructor]. You can add your own custom destruction code here..
        //[/Destructor]
    }

    const String ArrowToolbarButton::getTooltip()
    {
        return String("To create an arrow, select two actors.");
    }

    void ArrowToolbarButton::resized()
    {
        internalPath2.clear();
        internalPath2.startNewSubPath (24.0f, 8.0f);
        internalPath2.lineTo (32.0f, 8.0f);
        internalPath2.lineTo (32.0f, 16.0f);
        internalPath2.closeSubPath();

        internalPath3.clear();
        internalPath3.startNewSubPath (32.0f, 8.0f);
        internalPath3.lineTo (8.0f, 32.0f);
        internalPath3.closeSubPath();

        internalPath5.clear();
        internalPath5.startNewSubPath (24.0f, 8.0f);
        internalPath5.lineTo (32.0f, 8.0f);
        internalPath5.lineTo (32.0f, 16.0f);
        internalPath5.closeSubPath();

        internalPath6.clear();
        internalPath6.startNewSubPath (32.0f, 8.0f);
        internalPath6.lineTo (8.0f, 32.0f);
        internalPath6.closeSubPath();

        //[UserResized] Add your own custom resize handling here..
        //[/UserResized]
    }

    void ArrowToolbarButton::paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown)
    {
        if (isButtonDown)
        {
            GradientBrush gradient_4 (Colours::black,
                                      20.0f, 19.0f,
                                      Colours::white,
                                      20.0f, 1.0f,
                                      false);
            g.setBrush (&gradient_4);
            g.fillRoundedRectangle (1.0f, 1.0f, 38.0f, 38.0f, 6.0000f);

            g.setColour (Colours::white);
            g.drawRoundedRectangle (1.0f, 1.0f, 38.0f, 38.0f, 6.0000f, 0.6000f);

            g.setColour (Colours::white);
            g.fillPath (internalPath5);

            g.setColour (Colours::white);
            g.fillPath (internalPath6);
            g.setColour (Colours::white);
            g.strokePath (internalPath6, PathStrokeType (2.3000f));
        }
        else
        {
            GradientBrush gradient_1 (Colours::black,
                                      20.0f, 13.0f,
                                      Colours::white,
                                      20.0f, 1.0f,
                                      false);
            g.setBrush (&gradient_1);
            g.fillRoundedRectangle (1.0f, 1.0f, 38.0f, 38.0f, 6.0000f);

            g.setColour (Colours::white);
            g.drawRoundedRectangle (1.0f, 1.0f, 38.0f, 38.0f, 6.0000f, 0.6000f);

            g.setColour (Colours::white);
            g.fillPath (internalPath2);

            g.setColour (Colours::white);
            g.fillPath (internalPath3);
            g.setColour (Colours::white);
            g.strokePath (internalPath3, PathStrokeType (2.3000f));
        }
    }

    void ArrowToolbarButton::clicked()
    {
        //[UserCode_clicked] -- Add your code here...
        CommandDelegate::get().invokeDirectly(CommandDelegate::diagramAddArrow, false);
        //[/UserCode_clicked]
    }

}
//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Button" className="ArrowToolbarButton" componentName=""
                 parentClasses="public Button" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="40" initialHeight="40">
  <METHODS>
    <METHOD name="clicked()"/>
  </METHODS>
  <BACKGROUND backgroundColour="0" buttonState="normal" enabled="1">
    <ROUNDRECT pos="1 1 38 38" cornerSize="6" fill="linear: 20 13, 20 1, 0=ff000000, 1=ffffffff"
               hasStroke="1" stroke="0.600000024, mitered, butt" strokeColour="solid: ffffffff"/>
    <PATH pos="0 0 100 100" fill="solid: ffffffff" hasStroke="0" nonZeroWinding="1">s 24 8 l 32 8 l 32 16 x</PATH>
    <PATH pos="0 0 100 100" fill="solid: ffffffff" hasStroke="1" stroke="2.29999995, mitered, butt"
          strokeColour="solid: ffffffff" nonZeroWinding="1">s 32 8 l 8 32 x</PATH>
  </BACKGROUND>
  <BACKGROUND backgroundColour="0" buttonState="over" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="down" enabled="1">
    <ROUNDRECT pos="1 1 38 38" cornerSize="6" fill="linear: 20 19, 20 1, 0=ff000000, 1=ffffffff"
               hasStroke="1" stroke="0.600000024, mitered, butt" strokeColour="solid: ffffffff"/>
    <PATH pos="0 0 100 100" fill="solid: ffffffff" hasStroke="0" nonZeroWinding="1">s 24 8 l 32 8 l 32 16 x</PATH>
    <PATH pos="0 0 100 100" fill="solid: ffffffff" hasStroke="1" stroke="2.29999995, mitered, butt"
          strokeColour="solid: ffffffff" nonZeroWinding="1">s 32 8 l 8 32 x</PATH>
  </BACKGROUND>
  <BACKGROUND backgroundColour="0" buttonState="normal on" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="over on" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="down on" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="common background" enabled="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
