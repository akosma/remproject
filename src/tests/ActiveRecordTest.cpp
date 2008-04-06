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
        std::string name1("actor1");
        std::string name2("actor2");
		metamodel::Actor* actor = new metamodel::Actor();
		CPPUNIT_ASSERT(actor->isNew());

        actor->setName(name1);
		CPPUNIT_ASSERT_EQUAL(name1, actor->getName());

		actor->save();
		CPPUNIT_ASSERT(!actor->isNew());
		CPPUNIT_ASSERT(!actor->isDirty());

        actor->setName(name2);
		CPPUNIT_ASSERT(!actor->isNew());
		CPPUNIT_ASSERT(actor->isDirty());
		CPPUNIT_ASSERT_EQUAL(name2, actor->getName());

		actor->save();
		CPPUNIT_ASSERT(!actor->isNew());
		CPPUNIT_ASSERT(!actor->isDirty());
    }
    
    void ActiveRecordTest::testRetrieveAllInstances()
    {
        
    }
}
