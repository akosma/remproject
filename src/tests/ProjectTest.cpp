/*!  
 * \file ProjectTest.h
 * 
 * Contains the implementation of the tests::ProjectTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      2008-03-16
 */

#include "ProjectTest.h"

#ifndef PROJECT_H_
#include "../metamodel/Project.h"
#endif

#ifndef DIAGRAM_H_
#include "../metamodel/Diagram.h"
#endif

/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    /*!
     * ProjectTest Constructor.
     */
    ProjectTest::ProjectTest()
    {
    }
    
    /*!
     * ProjectTest Virtual destructor.
     */
    ProjectTest::~ProjectTest()
    {
    }

    /*!
     * Called by CppUnit before each test.
     */
    void ProjectTest::setUp()
    {
    }
    
    /*!
     * Called by CppUnit after each test.
     */
    void ProjectTest::tearDown()
    {
    }

    /*!
     * Tests something.
     */
    void ProjectTest::testProjectHasManyDiagrams()
    {
        std::string first("first");
        std::string second("second");
        std::string diagramClassName("usecase");

        metamodel::Project project;
        CPPUNIT_ASSERT(project.empty());
        
        metamodel::Diagram* firstDiagram = new metamodel::Diagram(diagramClassName);
        firstDiagram->setName(first);
        
        project.addElement(firstDiagram);
        CPPUNIT_ASSERT_EQUAL(1, project.getCount());
        
        metamodel::Diagram* pointer = project.getElement(first);
        CPPUNIT_ASSERT_EQUAL((int)firstDiagram, (int)pointer);
        CPPUNIT_ASSERT_EQUAL(first, pointer->getName());

        metamodel::Diagram* secondDiagram = new metamodel::Diagram(diagramClassName);
        secondDiagram->setName(second);
        project.addElement(secondDiagram);
        CPPUNIT_ASSERT_EQUAL(2, project.getCount());

        pointer = project.getElement(second);
        CPPUNIT_ASSERT_EQUAL((int)secondDiagram, (int)pointer);
        CPPUNIT_ASSERT_EQUAL(pointer->getName(), second);
		
        project.removeElement(first);
        CPPUNIT_ASSERT_EQUAL(1, project.getCount());

        project.removeElement(second);
        CPPUNIT_ASSERT_EQUAL(0, project.getCount());
        CPPUNIT_ASSERT(project.empty());

        // Do not do the following:
        // delete firstDiagram;
        // delete secondDiagram;
        // This is because "project" owns the diagrams and will delete them
        // when the stack is cleared, at the end of this method.
    }
	
	void ProjectTest::testCanRemoveAllDiagramsFromProject()
	{
        std::string first("first");
        std::string second("second");
        std::string diagramClassName("usecase");

        metamodel::Project project;
        CPPUNIT_ASSERT(project.empty());
        
        metamodel::Diagram* firstDiagram = new metamodel::Diagram(diagramClassName);
        firstDiagram->setName(first);
        
        project.addElement(firstDiagram);
        CPPUNIT_ASSERT_EQUAL(1, project.getCount());
        
        metamodel::Diagram* pointer = project.getElement(first);
        CPPUNIT_ASSERT_EQUAL((int)firstDiagram, (int)pointer);
        CPPUNIT_ASSERT_EQUAL(first, pointer->getName());

        metamodel::Diagram* secondDiagram = new metamodel::Diagram(diagramClassName);
        secondDiagram->setName(second);
        
        project.addElement(secondDiagram);
        CPPUNIT_ASSERT_EQUAL(2, project.getCount());

		project.removeAllElements();
        CPPUNIT_ASSERT_EQUAL(0, project.getCount());

        // Do not do the following:
        // delete firstDiagram;
        // delete secondDiagram;
        // This is because "project" owns the diagrams and will delete them
        // when the stack is cleared, at the end of this method.
	}
}
