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
 * \file Main.cpp
 *
 * Contains the implementation of the ui::Main class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/11/08
 */

#include <src/juce_WithoutMacros.h>

#ifndef APPLICATION_H_
#include "Application.h"
#endif

START_JUCE_APPLICATION (ui::Application)

/*!
 * \mainpage Rem
 *
 * \author Adrian Kosmaczewski
 * \date August 28th, 2008
 *
 * The project aims to the creation of an UML tool suitable both for academia and the industry, 
 * including Ivar Jacobson's proposed extensions for Aspect-Oriented Software Development (AOSD).
 *
 * \li Creation of a cross-platform (Linux, Windows & Mac OS X) UML editor, using C++;
 * \li  Allow users to create (in its first release) use case, sequence and class diagrams;
 * \li  Include AOSD extensions to create models for aspects, pointcuts and advices;
 * \li  Provide interoperability through the export of diagrams using the XMI standard;
 * \li  Deliver a high-quality code base, thoroughly unit- and functionally tested;
 * \li  Provide a usable, standard and easy-to-use user interface.
 *
 * The name "Rem" stands for "Requirements and Entity Modeler" but is also a reference to 
 * Rem Koolhaas, one of the greatest urbanists and architects of all time. 
 * The icon of the application is a stylized representation of one of Koolhaas’ major works, 
 * the building of the Seattle Public Library. 
 *
 * \section main_index Index
 *
 * More information about Rem can be found in the following pages:
 *
 * \li \subpage pageScreenshots "Screenshots"
 * \li \subpage pageBuild "Build"
 * \li \subpage pageInstallation "Installation"
 * \li \subpage pageDocumentation "Documentation"
 */

/*!
 * \page pageScreenshots Screenshots
 *
 * To be done.
 */

/*!
 * \page pageInstallation Installation
 *
 * \section install_win Windows
 *
 * \section install_linux Linux
 *
 * \section install_mac Mac OS X (10.5, Intel or PowerPC)
 */

/*!
 * \page pageBuild Build
 *
 * \section build_win Windows
 *
 * \section build_linux Linux
 *
 * \section build_mac Mac OS X (10.5, Intel or PowerPC)
 */

/*!
 * \page pageDocumentation Documentation
 *
 * To generate the documentation, make sure that Doxygen 1.5.4 or later
 * (http://www.stack.nl/~dimitri/doxygen/) and dot (http://www.graphviz.org/) are
 * installed; type "doxygen" in the folder where the file "Doxyfile" is located.
 *
 * For Windows, the Doxyfile also assumes that the HTML Compiler (used to generate
 * this CHM file) is located in "C:\Program Files\HTML Help Workshop\hhc.exe".
 * CHM files can be viewed in the Macintosh using Chmox (http://chmox.sourceforge.net/)
 * and in Linux using GnoCHM (http://gnochm.sourceforge.net/)
 */