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

		metamodel::Element* john = new metamodel::Element(className);
		CPPUNIT_ASSERT(john->isNew());
		CPPUNIT_ASSERT_EQUAL((int)storage::DEFAULT_ID, (int)john->getId());

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
		metamodel::Element* peter = new metamodel::Element(className);
		CPPUNIT_ASSERT(peter->isNew());
		CPPUNIT_ASSERT_EQUAL((int)storage::DEFAULT_ID, (int)peter->getId());

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
        std::vector<metamodel::Element>* elements = storage::ActiveRecord<metamodel::Element>::findAll();
        
        CPPUNIT_ASSERT_EQUAL(2, (int)elements->size());
        metamodel::Element& elem0 = elements->at(0);
        metamodel::Element& elem1 = elements->at(1);

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
        metamodel::Element* elem = storage::ActiveRecord<metamodel::Element>::findById(1);
        
        CPPUNIT_ASSERT(elem->getBoolean("valid"));
        CPPUNIT_ASSERT_EQUAL(std::string("actor"), elem->getString("class"));
        CPPUNIT_ASSERT(!elem->isDirty());
        CPPUNIT_ASSERT(!elem->isNew());
        
        delete elem;
    }
    
    void ActiveRecordTest::testSearchingForInstancesNotExistingInDatabaseReturnsNull()
    {
        metamodel::Element* elem = storage::ActiveRecord<metamodel::Element>::findById(15879);
        CPPUNIT_ASSERT(elem == NULL);
    }
    
    void ActiveRecordTest::testDestroyingObjectsRemovesThemFromTheDatabase()
    {
        metamodel::Element* elem = storage::ActiveRecord<metamodel::Element>::findById(1);
        
        CPPUNIT_ASSERT(elem->getBoolean("valid"));
        CPPUNIT_ASSERT_EQUAL(std::string("actor"), elem->getString("class"));
        CPPUNIT_ASSERT(!elem->isDirty());
        CPPUNIT_ASSERT(!elem->isNew());

        elem->destroy();
        CPPUNIT_ASSERT(elem->isDirty());
        CPPUNIT_ASSERT(elem->isNew());
        delete elem;
        
        elem = storage::ActiveRecord<metamodel::Element>::findById(1);
        CPPUNIT_ASSERT(elem == NULL);
        
        storage::ActiveRecord<metamodel::Element>::removeAll();
        
        std::vector<metamodel::Element>* elements = storage::ActiveRecord<metamodel::Element>::findAll();
        CPPUNIT_ASSERT_EQUAL(0, (int)elements->size());
    }

    void ActiveRecordTest::testCanUseCopyConstructorSafely()
    {
        std::string name("john");
        std::string className("actor");

		metamodel::Element* john = new metamodel::Element(className);
        john->setName(name);

		metamodel::Element* peter = new metamodel::Element(*john);

		CPPUNIT_ASSERT_EQUAL(peter->getName(), john->getName());

		john->save();
		CPPUNIT_ASSERT(!john->isNew());
		CPPUNIT_ASSERT(!john->isDirty());

        // We saved the original, but both objects are indeed different!
		CPPUNIT_ASSERT(peter->isNew());
		CPPUNIT_ASSERT(peter->isDirty());

        delete john;
        delete peter;
    }
    
    void ActiveRecordTest::testCanUseAssignmentOperatorSafely()
    {
        std::string name("john");
        std::string className("actor");

		metamodel::Element* john = new metamodel::Element(className);
        john->setName(name);

		metamodel::Element* peter = new metamodel::Element(className);

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
}
