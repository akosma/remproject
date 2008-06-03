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

//! Contains the implementation of the tests::ElementTest class.
/*!
 * \file ElementTest.cpp
 *
 * Contains the implementation of the tests::ElementTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      5/28/08
 */

#include "ElementTest.h"

#include <string>

#ifndef ELEMENT_H_
#include "../metamodel/Element.h"
#endif

#ifndef MEMBER_H_
#include "../metamodel/Member.h"
#endif

using metamodel::Element;
using metamodel::Member;
using std::string;

namespace tests
{
    ElementTest::ElementTest()
    {
    }
    
    ElementTest::~ElementTest()
    {
    }

    void ElementTest::testElementHasManyMembers()
    {
        string first("first");
        string second("second");
        string memberClassName("field");
        string elementClassName("class");

        Element element(elementClassName);
        CPPUNIT_ASSERT(!element.hasChildren());
        
        Member* firstMember = new Member(memberClassName);
        firstMember->setName(first);
        
        element.addChild(firstMember);
        CPPUNIT_ASSERT_EQUAL(1, element.getChildrenCount());
        
        Member* pointer = element.getChild(first);
        CPPUNIT_ASSERT_EQUAL((int)firstMember, (int)pointer);
        CPPUNIT_ASSERT_EQUAL(first, pointer->getName());

        Member* secondMember = new Member(memberClassName);
        secondMember->setName(second);
        element.addChild(secondMember);
        CPPUNIT_ASSERT_EQUAL(2, element.getChildrenCount());

        pointer = element.getChild(second);
        CPPUNIT_ASSERT_EQUAL((int)secondMember, (int)pointer);
        CPPUNIT_ASSERT_EQUAL(pointer->getName(), second);
        
        element.removeChild(first);
        CPPUNIT_ASSERT_EQUAL(1, element.getChildrenCount());

        element.removeChild(second);
        CPPUNIT_ASSERT_EQUAL(0, element.getChildrenCount());
        CPPUNIT_ASSERT(!element.hasChildren());
    }
    
    void ElementTest::testCanRemoveAllMembersFromElement()
    {
        string first("first");
        string second("second");
        string memberClassName("field");
        string elementClassName("class");

        Element element(elementClassName);
        CPPUNIT_ASSERT(!element.hasChildren());
        
        Member* firstMember = new Member(memberClassName);
        firstMember->setName(first);
        
        element.addChild(firstMember);
        CPPUNIT_ASSERT_EQUAL(1, element.getChildrenCount());
        
        Member* pointer = element.getChild(first);
        CPPUNIT_ASSERT_EQUAL((int)firstMember, (int)pointer);
        CPPUNIT_ASSERT_EQUAL(first, pointer->getName());

        Member* secondMember = new Member(memberClassName);
        secondMember->setName(second);
        
        element.addChild(secondMember);
        CPPUNIT_ASSERT_EQUAL(2, element.getChildrenCount());

        element.removeAllChildren();
        CPPUNIT_ASSERT_EQUAL(0, element.getChildrenCount());
    }
    
    void ElementTest::testCanAddMembersUsingOperator()
    {
        string first("first");
        string second("second");
        string memberClassName("field");
        string elementClassName("class");

        Element element(elementClassName);
        Member* firstMember = new Member(memberClassName);
        firstMember->setName(first);
        Member* secondMember = new Member(memberClassName);
        secondMember->setName(second);
        
        element << firstMember << secondMember;
        CPPUNIT_ASSERT_EQUAL(2, element.getChildrenCount());
    }
    
    void ElementTest::testCanRetrieveMembersUsingOperator()
    {
        string first("first");
        string second("second");
        string memberClassName("field");
        string elementClassName("class");

        Element element(elementClassName);
        Member* firstMember = new Member(memberClassName);
        firstMember->setName(first);
        Member* secondMember = new Member(memberClassName);
        secondMember->setName(second);
        
        element << firstMember << secondMember;
        
        Member* pointer = element[first];
        CPPUNIT_ASSERT(pointer);
        CPPUNIT_ASSERT_EQUAL((int)pointer, (int)firstMember);
    }
}
