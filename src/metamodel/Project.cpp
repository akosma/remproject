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
    : metamodel::Container<Diagram>()
    , storage::ActiveRecord<Project>(std::string("project"))
    {
        createSchemaStructure();
    }

    Project::Project(std::string& className, storage::ID id, storage::AnyPropertyMap& data)
    : storage::ActiveRecord<Project>(className, id, data)
    {
    }
    
    /*!
     * Project Virtual destructor.
     */
    Project::~Project()
    {
    }

    void Project::createSchemaStructure()
    {
        addStringProperty("class");
        addStringProperty("author");
        addIntegerProperty("created_on");
        addIntegerProperty("modified_on");
        addDoubleProperty("version");
        addBooleanProperty("valid");
    }

    std::string& Project::getTableName()
    {
        static std::string tableName("projects");
        return tableName;
    }
}
