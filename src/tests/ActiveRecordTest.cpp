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

#ifndef FINDCONDITIONS_H_
#include "../storage/FindConditions.h"
#endif

using metamodel::Element;
using metamodel::Diagram;
using metamodel::Project;
using storage::FindConditions;
using storage::DEFAULT_ID;
using Poco::DateTime;
using Poco::Stopwatch;
using std::string;
using std::vector;

namespace tests
{
    ActiveRecordTest::ActiveRecordTest()
    {
    }

    ActiveRecordTest::~ActiveRecordTest()
    {
    }

    void ActiveRecordTest::testCanSaveIndividualInstance()
    {
        const string name1("john");
        const string name2("johnny");
        const string className("actor");

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

        const string name3("peter");
        const string name4("pete");
        Element* peter = new Element(className);
        CPPUNIT_ASSERT(peter->isNew());
        CPPUNIT_ASSERT_EQUAL((int)DEFAULT_ID, (int)peter->getId());

        peter->setName(name3);
        CPPUNIT_ASSERT_EQUAL(name3, peter->getName());

        peter->save();
        CPPUNIT_ASSERT(!peter->isNew());
        CPPUNIT_ASSERT(!peter->isDirty());
        CPPUNIT_ASSERT_EQUAL(1, (int)peter->getId());

        peter->set<bool>("valid", true);
        peter->save();
        CPPUNIT_ASSERT_EQUAL(true, peter->get<bool>("valid"));
        
        delete john;
        delete peter;
    }
    
    void ActiveRecordTest::testCanRetrieveAllInstances()
    {
        vector<Element>* elements = Element::findAll();
        
        CPPUNIT_ASSERT_EQUAL(2, (int)elements->size());
        Element& elem0 = elements->at(0);
        Element& elem1 = elements->at(1);

        CPPUNIT_ASSERT_EQUAL(string("actor"), elem0.get<string>("class"));
        CPPUNIT_ASSERT(!elem0.isDirty());
        CPPUNIT_ASSERT(!elem0.isNew());

        CPPUNIT_ASSERT_EQUAL(string("actor"), elem1.get<string>("class"));
        CPPUNIT_ASSERT(!elem1.isDirty());
        CPPUNIT_ASSERT(!elem1.isNew());
        
        delete elements;
    }
    
    void ActiveRecordTest::testCanRetrieveOneInstance()
    {
        Element* elem = Element::findById(1);
        
        CPPUNIT_ASSERT(elem);
        CPPUNIT_ASSERT_EQUAL(string("actor"), elem->get<string>("class"));
        CPPUNIT_ASSERT(!elem->isDirty());
        CPPUNIT_ASSERT(!elem->isNew());
        
        delete elem;
    }
    
    void ActiveRecordTest::testCanUseConditionsToFindAnItem()
    {
        const string name("peter");
        
        FindConditions invalidConditions;
        invalidConditions.set<string>("name", name);
        invalidConditions.set<bool>("valid", true);
        vector<Element>* elements = Element::findByCondition(invalidConditions);
        
        CPPUNIT_ASSERT_EQUAL(0, (int)elements->size());
        
        delete elements;
        
        FindConditions validConditions;
        validConditions.set<string>("name", name);
        elements = Element::findByCondition(validConditions);
        
        CPPUNIT_ASSERT_EQUAL(1, (int)elements->size());        
        
        Element& elem0 = elements->at(0);

        CPPUNIT_ASSERT_EQUAL(string("actor"), elem0.get<string>("class"));
        CPPUNIT_ASSERT(!elem0.isDirty());
        CPPUNIT_ASSERT(!elem0.isNew());
        
        delete elements;
    }
    
    void ActiveRecordTest::testSearchingForInstancesNotExistingInDatabaseReturnsNull()
    {
        Element* elem = Element::findById(15879);
        CPPUNIT_ASSERT(elem == NULL);
    }
    
    void ActiveRecordTest::testDestroyingObjectsRemovesThemFromTheDatabase()
    {
        Element* elem = Element::findById(1);

        CPPUNIT_ASSERT(elem);
        CPPUNIT_ASSERT_EQUAL(string("actor"), elem->get<string>("class"));
        CPPUNIT_ASSERT(!elem->isDirty());
        CPPUNIT_ASSERT(!elem->isNew());

        elem->destroy();
        CPPUNIT_ASSERT(elem->isDirty());
        CPPUNIT_ASSERT(elem->isNew());
        delete elem;
        
        elem = Element::findById(1);
        CPPUNIT_ASSERT(elem == NULL);
        
        Element::removeAll();
        
        vector<Element>* elements = Element::findAll();
        CPPUNIT_ASSERT_EQUAL(0, (int)elements->size());
    }

    void ActiveRecordTest::testCanUseCopyConstructorSafely()
    {
        const string name("john");
        const string className("actor");
        
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
        string diagramClassName("diagram");
        string diagramName("diagramName");
        Diagram* diagram = new Diagram(diagramName);
        diagram->setName(diagramName);

        diagram->addChild(john);
        diagram->addChild(peter);

        Diagram* diagramCopy = new Diagram(*diagram);

        CPPUNIT_ASSERT_EQUAL(diagram->getName(), diagramCopy->getName());

        // The copy constructor does NOT copy the children!
        CPPUNIT_ASSERT_EQUAL(0, diagramCopy->getChildrenCount());

        delete diagram;
        delete diagramCopy;
        delete peter;
        delete john;
    }
    
    void ActiveRecordTest::testCanUseAssignmentOperatorSafely()
    {
        const string name("john");
        const string className("actor");

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
        const string first("first");
        const string second("second");
        const string diagramClassName("usecase");
        const string projectName("test");

        Project* project = new Project();
        project->setName(projectName);
        Diagram* firstDiagram = new Diagram(diagramClassName);
        firstDiagram->setName(first);
        project->addChild(firstDiagram);

        Project* parent = firstDiagram->getCastParent();
        CPPUNIT_ASSERT_EQUAL((int)project, (int)parent);
        CPPUNIT_ASSERT_EQUAL(project->getName(), parent->getName());

        Diagram* secondDiagram = new Diagram(diagramClassName);
        secondDiagram->setName(second);
        project->addChild(secondDiagram);

        CPPUNIT_ASSERT_EQUAL(2, project->getChildrenCount());

        parent = secondDiagram->getCastParent();
        CPPUNIT_ASSERT_EQUAL((int)project, (int)parent);
        CPPUNIT_ASSERT_EQUAL(project->getName(), parent->getName());

        project->save();
        delete project;
        delete firstDiagram;
        delete secondDiagram;
    }
    
    void ActiveRecordTest::testSavedObjectsHaveCreationAndUpdateTime()
    {
        const string element("timedElement");
        const string className("actor");
        
        Element* actor = new Element(className);
        actor->setName(element);

        actor->save();
        const DateTime saved1 = actor->getCreationDateTime();
        const DateTime updated1 = actor->getLastModificationDateTime();
        CPPUNIT_ASSERT(saved1 == updated1);
        
        // Let's wait a couple of seconds and save the actor again
        Stopwatch watch;
        watch.start();
        while (watch.elapsedSeconds() < 1) {}
        watch.stop();
        
        actor->save();
        const DateTime saved2 = actor->getCreationDateTime();
        const DateTime updated2 = actor->getLastModificationDateTime();
        CPPUNIT_ASSERT(saved1 == saved2);
        CPPUNIT_ASSERT(saved2 < updated2);
        CPPUNIT_ASSERT(updated1 < updated2);
        
        // Let's retrieve all of this from the DB and compare
        Element* retrieved = Element::findById(actor->getId());
        CPPUNIT_ASSERT(retrieved);
        const DateTime saved3 = retrieved->getCreationDateTime();
        const DateTime updated3 = retrieved->getLastModificationDateTime();
        CPPUNIT_ASSERT(saved2 == saved3);
        CPPUNIT_ASSERT(updated2 == updated3);
    }
    
    void ActiveRecordTest::testSettingAChildDirtySetsTheParentDirtyToo()
    {
        const string projectName("test");
        const string diagramClassName("usecase");
        const string first("first");
        const string second("second");

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
        const string projectName("Robert O'Hara");
        const string diagramClassName("William \"Braveheart\" Gibson");
        const string diagramName("You can't guess what users will insert in the \"database\" file");
        
        Project* project = new Project();
        project->setName(projectName);
        Diagram* diagram = new Diagram(diagramClassName);
        diagram->setName(diagramName);
        project->addChild(diagram);
        
        project->save();

        Project* retrievedProject = Project::findById(project->getId());
        CPPUNIT_ASSERT(retrievedProject);
        CPPUNIT_ASSERT_EQUAL(retrievedProject->getName(), project->getName());
        CPPUNIT_ASSERT_EQUAL(retrievedProject->getName(), projectName);
        
        FindConditions condition;
        condition.set<int>("project_id", project->getId());
        vector<Diagram>* diagrams = Diagram::findByCondition(condition);
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
        // Create a project with two diagrams inside
        const string first("first");
        const string second("second");
        const string diagramClassName("usecase");
        const string projectName("test");

        Project* project = new Project();
        project->setName(projectName);

        Diagram* firstDiagram = new Diagram(diagramClassName);
        firstDiagram->setName(first);
        project->addChild(firstDiagram);

        Diagram* secondDiagram = new Diagram(diagramClassName);
        secondDiagram->setName(second);
        project->addChild(secondDiagram);

        project->save();
        
        const storage::ID id = project->getId();
        delete project;

        // At this point, the project has not loaded the diagrams
        project = Project::findById(id);
        CPPUNIT_ASSERT(project);
        CPPUNIT_ASSERT(!project->hasLoadedChildren());
        
        // Now the project will load its diagrams; there should be two of them
        const int count = project->getChildrenCount();
        CPPUNIT_ASSERT(project->hasLoadedChildren());
        CPPUNIT_ASSERT_EQUAL(2, count);
        delete project;
    }
}
