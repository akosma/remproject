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

//! Contains the implementation of the ui::DiagramComponent class.
/*!
 * \file DiagramComponent.cpp
 *
 * Contains the implementation of the ui::DiagramComponent class.
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 *
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      21 Jun 2008 3:27:04 pm
 */

//[Headers] You can add your own extra header files here...
#ifndef CONTENTCOMPONENT_H_
#include "ContentComponent.h"
#endif
//[/Headers]

#include "DiagramComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

namespace ui
{
    DiagramComponent::DiagramComponent ()
        : viewport (0)
    {
        addAndMakeVisible (viewport = new Viewport (T("new viewport")));


        //[UserPreSize]
        //[/UserPreSize]

        //[Constructor] You can add your own custom stuff here..
        ContentComponent* content = new ContentComponent();
        viewport->setViewedComponent(content);
        //[/Constructor]
    }

    DiagramComponent::~DiagramComponent()
    {
        //[Destructor_pre]. You can add your own custom destruction code here..
        //[/Destructor_pre]

        deleteAndZero (viewport);

        //[Destructor]. You can add your own custom destruction code here..
        //[/Destructor]
    }

    void DiagramComponent::paint (Graphics& g)
    {
        //[UserPrePaint] Add your own custom painting code here..
        //[/UserPrePaint]

        g.fillAll (Colours::white);

        //[UserPaint] Add your own custom painting code here..
        //[/UserPaint]
    }

    void DiagramComponent::resized()
    {
        viewport->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
        //[UserResized] Add your own custom resize handling here..
        //[/UserResized]
    }

}
//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="DiagramComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <VIEWPORT name="new viewport" id="599396c1b455d99a" memberName="viewport"
            virtualName="" explicitFocusOrder="0" pos="0 0 100% 100%" vscroll="1"
            hscroll="1" scrollbarThickness="18" contentType="0" jucerFile=""
            contentClass="" constructorParams=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
