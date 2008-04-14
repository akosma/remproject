/*!  
 * \file DiagramTest.h
 * 
 * Contains the implementation of the tests::DiagramTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      2008-03-16
 */

#include "DiagramTest.h"

#ifndef DIAGRAM_H_
#include "../metamodel/Diagram.h"
#endif

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
     * DiagramTest Constructor.
     */
    DiagramTest::DiagramTest()
    {
    }
    
    /*!
     * DiagramTest Virtual destructor.
     */
    DiagramTest::~DiagramTest()
    {
    }

    /*!
     * Called by CppUnit before each test.
     */
    void DiagramTest::setUp()
    {
    }
    
    /*!
     * Called by CppUnit after each test.
     */
    void DiagramTest::tearDown()
    {
    }

    /*!
     * Tests something.
     */
    void DiagramTest::testDiagramCanHaveSeveralElements()
    {
		std::string actor1Name("actor1");
		std::string diagramName("diagramName");
        std::string className("actor");
        std::string diagramClassName("usecase");

		metamodel::Diagram diagram(diagramClassName, diagramName);
		CPPUNIT_ASSERT_EQUAL(diagramName, diagram.getName());
        CPPUNIT_ASSERT(diagram.empty());
        CPPUNIT_ASSERT_EQUAL(0, diagram.getCount());
        
        metamodel::Element* actor1 = new metamodel::Element(className);
        actor1->setName(actor1Name);
        CPPUNIT_ASSERT_EQUAL(actor1Name, actor1->getName());

        diagram.addElement(actor1);
        CPPUNIT_ASSERT_EQUAL(1, diagram.getCount());
        
        metamodel::Element* element = diagram.getElement(actor1Name);
        CPPUNIT_ASSERT_EQUAL((int)element, (int)actor1);
    }
}
