/*!  
 * \file Project.cpp
 * 
 * Contains the implementation of the metamodel::Project class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      2008-03-16
 */

#include "Project.h"

/*!
 * \namespace metamodel
 * Insert a description for the namespace here
 */
namespace metamodel
{
    /*!
     * Project Constructor.
     */
    Project::Project()
    : Container<Diagram>()
//    , storage::ActiveRecord<Project>(std::string("projects"))
    {
    }
	
	Project::~Project()
	{
	}
}
