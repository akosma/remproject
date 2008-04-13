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
    Element::Element(std::string className)
    : storage::ActiveRecord<Element>(className)
    {
    }
    
    /*!
     * Element Virtual destructor.
     */
    Element::~Element()
    {
    }

    void Element::setName(std::string& name)
    {
        setStringProperty("name", name);
    }
    
    std::string Element::getName()
    {
        return getString("name");
    }
    
    void Element::createAllPropertiesForSchema()
    {
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
