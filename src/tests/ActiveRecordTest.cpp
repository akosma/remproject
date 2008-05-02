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

using namespace metamodel;
using namespace storage;

/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    /*!
     * ActiveRecordTest Constructor.
     */
    ActiveRecordTest::ActiveRecordTest()
    {
    }
    
    /*!
     * ActiveRecordTest Virtual destructor.
     */
    ActiveRecordTest::~ActiveRecordTest()
    {
    }

    /*!
     * Called by CppUnit before each test.
     */
    void ActiveRecordTest::setUp()
    {
    }
    
    /*!
     * Called by CppUnit after each test.
     */
    void ActiveRecordTest::tearDown()
    {
    }

    /*!
     * Tests something.
     */
    
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

        peter->setBooleanProperty("valid", true);
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

        CPPUNIT_ASSERT(!elem0.getBoolean("valid"));
        CPPUNIT_ASSERT_EQUAL(std::string("actor"), elem0.getString("class"));
        CPPUNIT_ASSERT(!elem0.isDirty());
        CPPUNIT_ASSERT(!elem0.isNew());

        CPPUNIT_ASSERT(elem1.getBoolean("valid"));
        CPPUNIT_ASSERT_EQUAL(std::string("actor"), elem1.getString("class"));
        CPPUNIT_ASSERT(!elem1.isDirty());
        CPPUNIT_ASSERT(!elem1.isNew());
        
        delete elements;
    }
    
    void ActiveRecordTest::testCanRetrieveOneInstance()
    {
        Element* elem = ActiveRecord<Element>::findById(1);
        
        CPPUNIT_ASSERT(elem->getBoolean("valid"));
        CPPUNIT_ASSERT_EQUAL(std::string("actor"), elem->getString("class"));
        CPPUNIT_ASSERT(!elem->isDirty());
        CPPUNIT_ASSERT(!elem->isNew());
        
        delete elem;
    }
    
    void ActiveRecordTest::testCanUseConditionsToFindAnItem()
    {
        std::string name("peter");
        AnyPropertyMap conditions;
        conditions.setStringProperty("name", name);
        conditions.setBooleanProperty("valid", true);
        std::vector<Element>* elements = ActiveRecord<Element>::findByCondition(conditions);
        
        CPPUNIT_ASSERT_EQUAL(1, (int)elements->size());
        Element& elem0 = elements->at(0);

        CPPUNIT_ASSERT(elem0.getBoolean("valid"));
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
        
        CPPUNIT_ASSERT(elem->getBoolean("valid"));
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
}
