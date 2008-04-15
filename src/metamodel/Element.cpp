/*!
 * \file Element.cpp
 *
 * Contains the implementation of the metamodel::Element class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/16/08
 */

#include "Element.h"

/*!
 * \namespace metamodel
 * Insert a description for the namespace here
 */
namespace metamodel
{
    /*!
     * Element Constructor.
     */
    Element::Element(std::string& className)
    : storage::ActiveRecord<Element>(className)
    {
        createSchemaStructure();
    }
    
    Element::Element(std::string& className, storage::ID id, storage::AnyPropertyMap& data)
    : storage::ActiveRecord<Element>(className, id, data)
    {
    }
    
    /*!
     * Element Virtual destructor.
     */
    Element::~Element()
    {
    }

    void Element::createSchemaStructure()
    {
        addStringProperty("class");
        addStringProperty("name");
        addIntegerProperty("x");
        addIntegerProperty("y");
        addDoubleProperty("value");
        addBooleanProperty("valid");
    }

    std::string& Element::getTableName()
    {
        static std::string tableName("elements");
        return tableName;
    }
}
