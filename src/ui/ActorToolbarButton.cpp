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
 * \date      16 Aug 2008 3:51:59 pm
 */

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "ActorToolbarButton.h"

#ifndef COMMANDDELEGATE_H_
#include "CommandDelegate.h"
#endif

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

    const String ActorToolbarButton::getTooltip()
    {
        return String("Click to add an actor to the diagram.");
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
        internalPath2.clear();
        internalPath2.startNewSubPath (11.0f, 36.0f);
        internalPath2.lineTo (19.0f, 26.0f);
        internalPath2.lineTo (29.0f, 36.0f);

        internalPath3.clear();
        internalPath3.startNewSubPath (11.0f, 26.0f);
        internalPath3.lineTo (19.0f, 16.0f);
        internalPath3.lineTo (29.0f, 26.0f);

        internalPath5.clear();
        internalPath5.startNewSubPath (11.0f, 36.0f);
        internalPath5.lineTo (19.0f, 26.0f);
        internalPath5.lineTo (29.0f, 36.0f);

        internalPath6.clear();
        internalPath6.startNewSubPath (11.0f, 26.0f);
        internalPath6.lineTo (19.0f, 16.0f);
        internalPath6.lineTo (29.0f, 26.0f);

        //[UserResized] Add your own custom resize handling here..
        //[/UserResized]
    }

    void ActorToolbarButton::paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown)
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
            g.fillRect (18, 13, 3, 15);

            g.setColour (Colours::white);
            g.strokePath (internalPath5, PathStrokeType (2.9000f));

            g.setColour (Colours::white);
            g.drawEllipse (13.0f, 3.0f, 13.0f, 11.0f, 2.5000f);

            g.setColour (Colours::white);
            g.strokePath (internalPath6, PathStrokeType (2.9000f));
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
            g.fillRect (18, 13, 3, 15);

            g.setColour (Colours::white);
            g.strokePath (internalPath2, PathStrokeType (2.9000f));

            g.setColour (Colours::white);
            g.drawEllipse (13.0f, 3.0f, 13.0f, 11.0f, 2.5000f);

            g.setColour (Colours::white);
            g.strokePath (internalPath3, PathStrokeType (2.9000f));
        }
    }

    void ActorToolbarButton::clicked()
    {
        //[UserCode_clicked] -- Add your code here...
        CommandDelegate::get().invokeDirectly(CommandDelegate::diagramAddActor, false);
        //[/UserCode_clicked]
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
  <METHODS>
    <METHOD name="clicked()"/>
  </METHODS>
  <BACKGROUND backgroundColour="0" buttonState="normal" enabled="1">
    <ROUNDRECT pos="1 1 38 38" cornerSize="6" fill="linear: 20 13, 20 1, 0=ff000000, 1=ffffffff"
               hasStroke="1" stroke="0.600000024, mitered, butt" strokeColour="solid: ffffffff"/>
    <RECT pos="18 13 3 15" fill="solid: ffffffff" hasStroke="0"/>
    <PATH pos="0 0 100 100" fill="solid: ffffff" hasStroke="1" stroke="2.9000001, mitered, butt"
          strokeColour="solid: ffffffff" nonZeroWinding="1">s 11 36 l 19 26 l 29 36</PATH>
    <ELLIPSE pos="13 3 13 11" fill="solid: 0" hasStroke="1" stroke="2.5, mitered, butt"
             strokeColour="solid: ffffffff"/>
    <PATH pos="0 0 100 100" fill="solid: ffffff" hasStroke="1" stroke="2.9000001, mitered, butt"
          strokeColour="solid: ffffffff" nonZeroWinding="1">s 11 26 l 19 16 l 29 26</PATH>
  </BACKGROUND>
  <BACKGROUND backgroundColour="0" buttonState="over" enabled="0">
    <ROUNDRECT pos="1 1 38 38" cornerSize="10" fill="solid: ffffffff" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ff2a6ba5"/>
    <ELLIPSE pos="13 3 13 11" fill="solid: ff2a6ba5" hasStroke="0"/>
    <RECT pos="18 9 3 18" fill="solid: ff2a6ba5" hasStroke="0"/>
    <PATH pos="0 0 100 100" fill="solid: ffffff" hasStroke="1" stroke="2.9000001, mitered, butt"
          strokeColour="solid: ff2a6ba5" nonZeroWinding="1">s 11 35 l 19 25 l 29 35</PATH>
    <RECT pos="8 17 24 3" fill="solid: ff2a6ba5" hasStroke="0"/>
  </BACKGROUND>
  <BACKGROUND backgroundColour="0" buttonState="down" enabled="1">
    <ROUNDRECT pos="1 1 38 38" cornerSize="6" fill="linear: 20 19, 20 1, 0=ff000000, 1=ffffffff"
               hasStroke="1" stroke="0.600000024, mitered, butt" strokeColour="solid: ffffffff"/>
    <RECT pos="18 13 3 15" fill="solid: ffffffff" hasStroke="0"/>
    <PATH pos="0 0 100 100" fill="solid: ffffff" hasStroke="1" stroke="2.9000001, mitered, butt"
          strokeColour="solid: ffffffff" nonZeroWinding="1">s 11 36 l 19 26 l 29 36</PATH>
    <ELLIPSE pos="13 3 13 11" fill="solid: 0" hasStroke="1" stroke="2.5, mitered, butt"
             strokeColour="solid: ffffffff"/>
    <PATH pos="0 0 100 100" fill="solid: ffffff" hasStroke="1" stroke="2.9000001, mitered, butt"
          strokeColour="solid: ffffffff" nonZeroWinding="1">s 11 26 l 19 16 l 29 26</PATH>
  </BACKGROUND>
  <BACKGROUND backgroundColour="0" buttonState="normal on" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="over on" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="down on" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="common background" enabled="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
