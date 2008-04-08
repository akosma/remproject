/*!
 * \file main.cpp
 *
 * Contains the entry point of the test application, using the CppUnit framework.
 * 
 * \version    $LastChangedRevision$
 * \date       $LastChangedDate$
 * \author     $LastChangedBy$
 * 
 * $HeadURL$
*/

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cstdlib>

/*!
 * Entry point of the test application.
 * 
 * \return An error code to the application, stating whether
 * the test run was successful or not.
 */
int main()
{
    remove("test.db");
    remove("untitled.db");

    CppUnit::TextUi::TestRunner runner;
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    bool wasSucessful = runner.run();
    return wasSucessful ? EXIT_SUCCESS : EXIT_FAILURE;
}
