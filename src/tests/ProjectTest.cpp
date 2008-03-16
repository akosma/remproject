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

#ifndef USECASEDIAGRAM_H_
#include "../metamodel/UseCaseDiagram.h"
#endif

using namespace MetaModel;

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
        const std::string first("first");
        const std::string second("second");

        Project project;
        CPPUNIT_ASSERT(project.empty());
        
        UseCaseDiagram* firstDiagram = new UseCaseDiagram(first);
        
        project.addDiagram(firstDiagram);
        CPPUNIT_ASSERT(project.getDiagramCount() == 1);
        
        Diagram* pointer = project.getDiagram(first);
        CPPUNIT_ASSERT(firstDiagram == pointer);
        CPPUNIT_ASSERT(pointer->getName() == first);

        UseCaseDiagram* secondDiagram = new UseCaseDiagram(second);
        project.addDiagram(secondDiagram);
        CPPUNIT_ASSERT(project.getDiagramCount() == 2);

        pointer = project.getDiagram(second);
        CPPUNIT_ASSERT(secondDiagram == pointer);
        CPPUNIT_ASSERT(pointer->getName() == second);
        
        project.removeDiagram(first);
        CPPUNIT_ASSERT(project.getDiagramCount() == 1);

        project.removeDiagram(second);
        CPPUNIT_ASSERT(project.getDiagramCount() == 0);
        CPPUNIT_ASSERT(project.empty());
        
        const std::string& firstName = firstDiagram->getName();
        CPPUNIT_ASSERT(firstName == first);
        delete firstDiagram;

        const std::string& secondName = secondDiagram->getName();
        CPPUNIT_ASSERT(secondName == second);
        delete secondDiagram;
    }
}
