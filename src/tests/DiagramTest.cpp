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
    void DiagramTest::testWhatever()
    {
        bool ok = true;
        CPPUNIT_ASSERT(ok);
    }
}
