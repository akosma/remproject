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

//! Contains the implementation of the tests::ActiveRecordTest class.
/*!
 * \file ActiveRecordTest.cpp
 *
 * Contains the implementation of the tests::ActiveRecordTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/6/08
 */

#include "ActiveRecordTest.h"

#include <Poco/DateTime.h>
#include <Poco/Stopwatch.h>

#ifndef ELEMENT_H_
#include "../metamodel/Element.h"
#endif

#ifndef DIAGRAM_H_
#include "../metamodel/Diagram.h"
#endif

#ifndef PROJECT_H_
#include "../metamodel/Project.h"
#endif

#ifndef ANYPROPERTYMAP_H_
#include "../storage/AnyPropertyMap.h"
#endif

using metamodel::Element;
using metamodel::Diagram;
using metamodel::Project;
using storage::AnyPropertyMap;
using storage::DEFAULT_ID;

namespace tests
{
    ActiveRecordTest::ActiveRecordTest()
    {
    }

    ActiveRecordTest::~ActiveRecordTest()
    {
    }

    void ActiveRecordTest::setUp()
    {
    }

    void ActiveRecordTest::tearDown()
    {
    }

    void ActiveRecordTest::testCanSaveIndividualInstance()
    {
        std::string name1("john");
        std::string name2("johnny");
        std::string className("actor");

        Element* john = new Element(className);
        CPPUNIT_ASSERT(john->isNew());
        CPPUNIT_ASSERT_EQUAL((int)DEFAULT_ID, (int)john->getId());

        john->setName(name1);
        CPPUNIT_ASSERT_EQUAL(name1, john->getName());

        john->save();
        CPPUNIT_ASSERT(!john->isNew());
        CPPUNIT_ASSERT(!john->isDirty());
        CPPUNIT_ASSERT_EQUAL(0, (int)john->getId());

        john->setName(name2);
        CPPUNIT_ASSERT(!john->isNew());
        CPPUNIT_ASSERT(john->isDirty());
        CPPUNIT_ASSERT_EQUAL(name2, john->getName());

        john->save();
        CPPUNIT_ASSERT(!john->isNew());
        CPPUNIT_ASSERT(!john->isDirty());

        std::string name3("peter");
        std::string name4("pete");
        Element* peter = new Element(className);
        CPPUNIT_ASSERT(peter->isNew());
        CPPUNIT_ASSERT_EQUAL((int)DEFAULT_ID, (int)peter->getId());

        peter->setName(name3);
        CPPUNIT_ASSERT_EQUAL(name3, peter->getName());

        peter->save();
        CPPUNIT_ASSERT(!peter->isNew());
        CPPUNIT_ASSERT(!peter->isDirty());
        CPPUNIT_ASSERT_EQUAL(1, (int)peter->getId());

        peter->setBoolean("valid", true);
        peter->save();
        CPPUNIT_ASSERT_EQUAL(true, peter->getBoolean("valid"));
        
        delete john;
        delete peter;
    }
    
    void ActiveRecordTest::testCanRetrieveAllInstances()
    {
        std::vector<Element>* elements = ActiveRecord<Element>::findAll();
        
        CPPUNIT_ASSERT_EQUAL(2, (int)elements->size());
        Element& elem0 = elements->at(0);
        Element& elem1 = elements->at(1);

        CPPUNIT_ASSERT_EQUAL(std::string("actor"), elem0.getString("class"));
        CPPUNIT_ASSERT(!elem0.isDirty());
        CPPUNIT_ASSERT(!elem0.isNew());

        CPPUNIT_ASSERT_EQUAL(std::string("actor"), elem1.getString("class"));
        CPPUNIT_ASSERT(!elem1.isDirty());
        CPPUNIT_ASSERT(!elem1.isNew());
        
        delete elements;
    }
    
    void ActiveRecordTest::testCanRetrieveOneInstance()
    {
        Element* elem = ActiveRecord<Element>::findById(1);
        
        CPPUNIT_ASSERT_EQUAL(std::string("actor"), elem->getString("class"));
        CPPUNIT_ASSERT(!elem->isDirty());
        CPPUNIT_ASSERT(!elem->isNew());
        
        delete elem;
    }
    
    void ActiveRecordTest::testCanUseConditionsToFindAnItem()
    {
        std::string name("peter");
        
        AnyPropertyMap invalidConditions;
        invalidConditions.setString("name", name);
        invalidConditions.setBoolean("valid", true);
        std::vector<Element>* elements = ActiveRecord<Element>::findByCondition(invalidConditions);
        
        CPPUNIT_ASSERT_EQUAL(0, (int)elements->size());
        
        delete elements;
        
        AnyPropertyMap validConditions;
        validConditions.setString("name", name);
        elements = ActiveRecord<Element>::findByCondition(validConditions);
        
        CPPUNIT_ASSERT_EQUAL(1, (int)elements->size());        
        
        Element& elem0 = elements->at(0);

        CPPUNIT_ASSERT_EQUAL(std::string("actor"), elem0.getString("class"));
        CPPUNIT_ASSERT(!elem0.isDirty());
        CPPUNIT_ASSERT(!elem0.isNew());
        
        delete elements;
    }
    
    void ActiveRecordTest::testSearchingForInstancesNotExistingInDatabaseReturnsNull()
    {
        Element* elem = ActiveRecord<Element>::findById(15879);
        CPPUNIT_ASSERT(elem == NULL);
    }
    
    void ActiveRecordTest::testDestroyingObjectsRemovesThemFromTheDatabase()
    {
        Element* elem = ActiveRecord<Element>::findById(1);
        
        CPPUNIT_ASSERT_EQUAL(std::string("actor"), elem->getString("class"));
        CPPUNIT_ASSERT(!elem->isDirty());
        CPPUNIT_ASSERT(!elem->isNew());

        elem->destroy();
        CPPUNIT_ASSERT(elem->isDirty());
        CPPUNIT_ASSERT(elem->isNew());
        delete elem;
        
        elem = ActiveRecord<Element>::findById(1);
        CPPUNIT_ASSERT(elem == NULL);
        
        ActiveRecord<Element>::removeAll();
        
        std::vector<Element>* elements = ActiveRecord<Element>::findAll();
        CPPUNIT_ASSERT_EQUAL(0, (int)elements->size());
    }

    void ActiveRecordTest::testCanUseCopyConstructorSafely()
    {
        std::string name("john");
        std::string className("actor");
        

        Element* john = new Element(className);
        john->setName(name);

        Element* peter = new Element(*john);

        CPPUNIT_ASSERT_EQUAL(peter->getName(), john->getName());
        
        john->save();
        CPPUNIT_ASSERT(!john->isNew());
        CPPUNIT_ASSERT(!john->isDirty());

        // We saved the original, but both objects are indeed different!
        CPPUNIT_ASSERT((int)peter != (int)john);
        CPPUNIT_ASSERT(peter->isNew());
        CPPUNIT_ASSERT(peter->isDirty());

        // Add everything to a diagram now and copy the diagram
        std::string diagramClassName("diagram");
        std::string diagramName("diagramName");
        Diagram* diagram = new Diagram(diagramName);
        diagram->setName(diagramName);

        diagram->addChild(john);
        diagram->addChild(peter);

        Diagram* diagramCopy = new Diagram(*diagram);

        CPPUNIT_ASSERT_EQUAL(diagram->getName(), diagramCopy->getName());

        // The copy constructor does NOT copy the children!
        CPPUNIT_ASSERT_EQUAL(0, diagramCopy->getChildrenCount());

        delete diagram;
    }
    
    void ActiveRecordTest::testCanUseAssignmentOperatorSafely()
    {
        std::string name("john");
        std::string className("actor");

        Element* john = new Element(className);
        john->setName(name);

        Element* peter = new Element(className);

        // If we just did "peter = john" then we'd have two pointers 
        // towards the same object!
        *peter = *john;

        CPPUNIT_ASSERT_EQUAL(peter->getName(), john->getName());

        john->save();
        CPPUNIT_ASSERT(!john->isNew());
        CPPUNIT_ASSERT(!john->isDirty());

        CPPUNIT_ASSERT(peter->isNew());
        CPPUNIT_ASSERT(peter->isDirty());

        delete john;
        delete peter;
    }
    
    void ActiveRecordTest::testObjectCanSaveItsChildren()
    {
        std::string first("first");
        std::string second("second");
        std::string diagramClassName("usecase");
        std::string projectName("test");

        Project* project = new Project();
        project->setName(projectName);
        Diagram* firstDiagram = new Diagram(diagramClassName);
        firstDiagram->setName(first);
        
        // Thanks to "dynamic_cast", when adding a child, we're setting 
        // also the "parent" pointer in the child object.
        project->addChild(firstDiagram);

        Project* parent = firstDiagram->getParent();
        CPPUNIT_ASSERT_EQUAL((int)project, (int)firstDiagram->getParent());
        CPPUNIT_ASSERT_EQUAL(project->getName(), parent->getName());

        Diagram* secondDiagram = new Diagram(diagramClassName);
        secondDiagram->setName(second);
        project->addChild(secondDiagram);

        CPPUNIT_ASSERT_EQUAL(2, project->getChildrenCount());

        // The pointer to the parent is correctly set thanks to the dynamic_cast operator:
        parent = secondDiagram->getParent();
        CPPUNIT_ASSERT_EQUAL((int)project, (int)secondDiagram->getParent());
        CPPUNIT_ASSERT_EQUAL(project->getName(), parent->getName());

        project->save();
        delete project;
    }
    
    void ActiveRecordTest::testSavedObjectsHaveCreationAndUpdateTime()
    {
        std::string element("timedElement");
        std::string className("actor");
        
        Element* actor = new Element(className);
        actor->setName(element);

        actor->save();
        Poco::DateTime saved1 = actor->getCreationDateTime();
        Poco::DateTime updated1 = actor->getLastModificationDateTime();
        CPPUNIT_ASSERT(saved1 == updated1);
        
        // Let's wait a couple of seconds and save the actor again
        Poco::Stopwatch watch;
        watch.start();
        while (watch.elapsedSeconds() < 1) {}
        watch.stop();
        
        actor->save();
        Poco::DateTime saved2 = actor->getCreationDateTime();
        Poco::DateTime updated2 = actor->getLastModificationDateTime();
        CPPUNIT_ASSERT(saved2 < updated2);
        CPPUNIT_ASSERT(saved1 == saved2);
        
        // Let's retrieve all of this from the DB and compare
        Element* retrieved = ActiveRecord<Element>::findById(actor->getId());
        Poco::DateTime saved3 = retrieved->getCreationDateTime();
        Poco::DateTime updated3 = retrieved->getLastModificationDateTime();
        CPPUNIT_ASSERT(saved2 == saved3);
        CPPUNIT_ASSERT(updated2 == updated3);
    }
    
    void ActiveRecordTest::testSettingAChildDirtySetsTheParentDirtyToo()
    {
        std::string projectName("test");
        std::string diagramClassName("usecase");
        std::string first("first");
        std::string second("second");

        Project* project = new Project();
        project->setName(projectName);
        Diagram* diagram = new Diagram(diagramClassName);
        diagram->setName(first);
        project->addChild(diagram);

        CPPUNIT_ASSERT(project->isNew());
        CPPUNIT_ASSERT(diagram->isNew());

        project->save();
        
        CPPUNIT_ASSERT(!project->isNew());
        CPPUNIT_ASSERT(!project->isDirty());

        CPPUNIT_ASSERT(!diagram->isNew());
        CPPUNIT_ASSERT(!diagram->isDirty());

        diagram->setName(second);

        CPPUNIT_ASSERT(project->isDirty());
        CPPUNIT_ASSERT(diagram->isDirty());
        
        delete project;
        delete diagram;
    }
    
    void ActiveRecordTest::testObjectsCannotBeAttackedWithSqlInjection()
    {
        std::string projectName("Robert O'Hara");
        std::string diagramClassName("William \"Braveheart\" Gibson");
        std::string diagramName("You can't guess what users will insert in the \"database\" file");
        
        Project* project = new Project();
        project->setName(projectName);
        Diagram* diagram = new Diagram(diagramClassName);
        diagram->setName(diagramName);
        project->addChild(diagram);
        
        project->save();

        Project* retrievedProject = ActiveRecord<Project>::findById(project->getId());
        CPPUNIT_ASSERT_EQUAL(retrievedProject->getName(), project->getName());
        CPPUNIT_ASSERT_EQUAL(retrievedProject->getName(), projectName);
        
        AnyPropertyMap condition;
        condition.setInteger("project_id", project->getId());
        std::vector<Diagram>* diagrams = ActiveRecord<Diagram>::findByCondition(condition);
        CPPUNIT_ASSERT_EQUAL(1, (int)diagrams->size());

        Diagram& retrievedDiagram = diagrams->at(0);
        CPPUNIT_ASSERT_EQUAL(retrievedDiagram.getName(), diagram->getName());
        CPPUNIT_ASSERT_EQUAL(retrievedDiagram.getName(), diagramName);
        
        delete diagram;
        delete project;
        delete diagrams;
        delete retrievedProject;
    }
    
    void ActiveRecordTest::testUsesLazyLoadingToRetrieveChildren()
    {
        // At this point, the project has not loaded the diagrams
        Project* project = ActiveRecord<Project>::findById(0);
        CPPUNIT_ASSERT(!project->hasLoadedChildren());
        
        // Now the project will load its diagrams; there should be two of them
        const int count = project->getChildrenCount();
        CPPUNIT_ASSERT(project->hasLoadedChildren());
        CPPUNIT_ASSERT_EQUAL(2, count);
        delete project;
    }
}
