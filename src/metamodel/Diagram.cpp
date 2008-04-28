/*!
 * \file Diagram.cpp
 *
 * Contains the implementation of the metamodel::Diagram class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/16/08
 */

#include "Diagram.h"

#ifndef PROJECT_H_
#include "Project.h"
#endif

#ifndef ELEMENT_H_
#include "Element.h"
#endif

/*!
 * \namespace metamodel
 * Insert a description for the namespace here
 */
namespace metamodel
{
    /*!
     * Diagram Constructor.
     */
    Diagram::Diagram(std::string& className)
    : storage::ActiveRecord<Diagram>(className)
    , storage::BelongsTo<Project>()
    , storage::HasMany<Element>()
    {
        createSchemaStructure();
        addIntegerProperty(getParentColumn());
    }

    Diagram::Diagram(std::string& className, storage::ID id, storage::AnyPropertyMap& data)
    : storage::ActiveRecord<Diagram>(className, id, data)
    , storage::BelongsTo<Project>()
    , storage::HasMany<Element>()
    {
    }

    /*!
     * Diagram Virtual destructor.
     */
    Diagram::~Diagram()
    {
    }

    void Diagram::createSchemaStructure()
    {
        addStringProperty("class");
        addStringProperty("name");
        addIntegerProperty("x");
        addIntegerProperty("y");
        addDoubleProperty("value");
        addBooleanProperty("valid");
    }

    std::string& Diagram::getTableName()
    {
        static std::string tableName("diagrams");
        return tableName;
    }
}
