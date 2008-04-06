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

#ifndef ACTOR_H_
#include "../metamodel/Actor.h"
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
    void ActiveRecordTest::testSaveIndividualInstance()
    {
        std::string name1("john");
        std::string name2("johnny");
		metamodel::Actor* john = new metamodel::Actor();
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
		metamodel::Actor* peter = new metamodel::Actor();
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
    }
    
    void ActiveRecordTest::testRetrieveAllInstances()
    {
        
    }
}
