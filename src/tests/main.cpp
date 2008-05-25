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

//! Contains the entry point of the test application, using the CppUnit framework.
/*!
 * \file main.cpp
 *
 * Contains the entry point of the test application, using the CppUnit framework.
 * 
 * \version    $LastChangedRevision$
 * \date       $LastChangedDate$
 * \author     $LastChangedBy$
 * 
 * $HeadURL$
*/

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cstdlib>

//! Entry point of the test application.
/*!
 * Entry point of the test application.
 * 
 * \return An error code to the application, stating whether
 * the test run was successful or not.
 */
int main()
{
    // Remove files from previous tests
    remove("test.db");
    remove("untitled.db");
    remove("whatever.rem");
    remove("untitled 4.rem");

    CppUnit::TextUi::TestRunner runner;
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    bool wasSucessful = runner.run();
    return wasSucessful ? EXIT_SUCCESS : EXIT_FAILURE;
}
